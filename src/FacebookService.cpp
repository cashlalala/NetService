#include "StdAfx.h"
#include "FacebookService.h"
#include "MapHelper.h"
#include "FBPhotoModel.h"
#include "FBErrorModel.h"
#include "FBVideoModel.h"
#include "FBUserModel.h"
#include "DataMgrFactory.h"
#include "NetServiceErr.h"
#include "UrlHelper.h"
#include "FBFields.h"

#include "StringHelper.h"
#include "LoggerMgr.h"

#include <cassert>
#include <sstream>

using systypes::EnCategory;
using systypes::EnHttpMethod;
using util::CMapHelper;
using std::stringstream;
using namespace model;


const string CFacebookService::S_STR_URL_PREFIX = "https://";

const SysMaps::EnCat2Str 
CFacebookService::S_MAP_CATEGORY = CMapHelper::CreateCategoryMap();

const ServerInfo CFacebookService::S_SERVER_INFO = {"graph.facebook.com","","80","443"};

CFacebookService::CFacebookService(void):
m_pIDataMgr(NULL),
m_pILogger(NULL)
{
	m_pIDataMgr = util::CDataMgrFactory::GetInstance(util::JsonCpp);
	m_pILogger = util::CLoggerMgr::GetLogger(util::Log4Cxx,"CFacebookService");
}

CFacebookService::~CFacebookService(void)
{
	//util::CDataMgrFactory::DeleteInstance(m_pIDataMgr);
	delete m_pIDataMgr;
}

void CFacebookService::SetConnectionInfo( IConnectionInfo& cConectInfoVO )
{
	m_cConnectInfo = *(dynamic_cast<CFBConnectionInfo*>(&cConectInfoVO));
}

int CFacebookService::CallGraphAPI(HttpRespValObj& cHttpRespVO, string szId /*= "me"*/, EnCategory enCatogory /*= None*/, SysMaps::Str2Str mapParams /*= SysMaps::Str2Str()*/, EnHttpMethod enMethod /*= Get*/, bool bCheckError /*= true*/ )
{
	if (mapParams["access_token"]=="")
		mapParams["access_token"] = m_cConnectInfo.szAccessToken;
	
	//[prefix] [    server name       ]     [    szId      ]     [categ]     [   params     ]
	//https://  graph.facebook.com   /  724760664  /  photos  ?  fields=id,name
	string szComposedUrl = 
		CFacebookService::S_STR_URL_PREFIX 
		+	S_SERVER_INFO.szServerName
		+ "/"
		+ ((szId=="")? "me": szId)
		+ "/"
		+ CMapHelper::GetValue(S_MAP_CATEGORY,enCatogory)
		+ (mapParams.empty()? "" :"?"+ CMapHelper::ToParamString(mapParams));
	
	int nResult = OpenUrl(cHttpRespVO, szComposedUrl);

	return nResult;

}

int CFacebookService::GetLoginURL( string& szLoginUrl, const string& szAppId, const string& szAppSecret, IError& iErr, string szScope /*= "read_stream,publish_stream,user_photos,friends_photos,user_videos,friends_videos,offline_access"*/ )
{
	string szUrl = "https://www.facebook.com/dialog/oauth?";
	szUrl	 += "&client_id=" + szAppId;
	szUrl += "&redirect_uri=http://www.facebook.com/connect/login_success.html" ;
	szUrl += "&display=popup";
	szUrl += "&scope=" + szScope;
	szUrl += "&response_type=token";
	szLoginUrl = util::CUrlHelper::EncodeUrl(szUrl);
	return S_OK;
}

int CFacebookService::GetPhotos(  IPhotoList& iPhotoLst, IError& iErr, string szId, SysMaps::Str2Str& mapQryCriteria)
{
	int nResult = E_FAIL;
	model::CFBPhotoList listPhoto;
	HttpRespValObj cHttpResp;
	do 
	{
		nResult = CallGraphAPI(cHttpResp, szId, Photo,mapQryCriteria);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParsePhotoList(iPhotoLst,cHttpResp.szResp,iErr);
		EXCEPTION_BREAK(nResult)

		CrackParamsForPagination(iPhotoLst);
	} while (false);
	
	//Error Handling
	ExceptionHandler(nResult, cHttpResp, iErr);
	
	return nResult;
}

int CFacebookService::GetUsersInfo( IUserList& iUserLst, IError& iErr, SysList::StrList& listUid, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	for (SysList::StrList::iterator it = listUid.begin();it!=listUid.end();++it)
	{
		HttpRespValObj cHttpResp;
		CFBUser* cFbUsr = new CFBUser();
		do 
		{	
			nResult = this->CallGraphAPI(cHttpResp,*it,None,mapQryCriteria);
			EXCEPTION_BREAK(nResult)

			nResult = m_pIDataMgr->ParseUser(*cFbUsr,cHttpResp.szResp,iErr);
			EXCEPTION_BREAK(nResult)

			iUserLst.items.push_back(cFbUsr);
			nResult = S_OK;
		} while (false);

		//Error Handling
		if (!SUCCEEDED(nResult))
		{
			if (nResult == NS_E_INET_CONNECT_FAIL_API_RETURN_ERROR ||
				nResult == NS_E_INET_CONNECT_FAIL_HTTP_STATUS_ERROR)
			{
				stringstream ss;
				ss << "API return Code: [" << cHttpResp.dwError << "] Http Status: [" << cHttpResp.dwStatusCode << "] Response Msg:[" << cHttpResp.szResp <<"]";
				iErr.szMsg = ss.str() ;
			}

			SAFE_DELETE_OBJECT(cFbUsr);
			break;
		}
	}
	return nResult;
}

int CFacebookService::GetUserInfo( IUser& iUser, IError& iErr, string szUid/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpResp;
	do 
	{	
		nResult = this->CallGraphAPI(cHttpResp,szUid,None,mapQryCriteria);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParseUser( iUser,cHttpResp.szResp,iErr);
		EXCEPTION_BREAK(nResult)

		nResult = S_OK;
	} while (false);

	//Error Handling
	ExceptionHandler(nResult, cHttpResp, iErr);

	return nResult;
}

int CFacebookService::GetFriends( IUserList& iUserLst, IError& iErr, string szUid/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpResp;

	do 
	{
		nResult = CallGraphAPI(cHttpResp,szUid, Friend, mapQryCriteria,Get);
		EXCEPTION_BREAK(nResult);

		nResult = m_pIDataMgr->ParseFriendList(iUserLst,cHttpResp.szResp,iErr);
		EXCEPTION_BREAK(nResult)

		CrackParamsForPagination(iUserLst);
	} while (false);

	//Error Handling
	ExceptionHandler(nResult, cHttpResp, iErr);

	return nResult;
	
}

void CFacebookService::ExceptionHandler( int nResult, HttpRespValObj &cHttpResp, IError &iErr )
{
	if (!SUCCEEDED(nResult))
	{
		if (nResult == NS_E_INET_CONNECT_FAIL_API_RETURN_ERROR ||
			nResult == NS_E_INET_CONNECT_FAIL_HTTP_STATUS_ERROR)
		{
			stringstream ss;
			ss << "API return Code: [" << cHttpResp.dwError << "] Http Status: [" << cHttpResp.dwStatusCode << "] Response Msg:[" << cHttpResp.szResp <<"]";
			iErr.szMsg = ss.str() ;
		}
	}
}

int CFacebookService::GetVideos( IVideoList& iVideoList, IError& iErr, string szId/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpResp;
	do 
	{
		nResult = CallGraphAPI(cHttpResp, szId, Video,mapQryCriteria);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParseVideoList(iVideoList,cHttpResp.szResp, util::Facebook, iErr);
		EXCEPTION_BREAK(nResult)

		CrackParamsForPagination(iVideoList);
	} while (false);

	//Error Handling
	ExceptionHandler(nResult, cHttpResp, iErr);

	return nResult;
}

int CFacebookService::GetAlbums( IAlbumList& iAlbumLst, IError& iErr, string szUid/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpResp;
	do 
	{
		nResult = CallGraphAPI(cHttpResp, szUid, Album,mapQryCriteria);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParseAlbumList(iAlbumLst,cHttpResp.szResp,iErr);
		EXCEPTION_BREAK(nResult)

		//The following is a workaround for get thumbnails...
		string szAlbumThumbNailQry = util::CStringHelper::Format(
									"SELECT album_object_id , src_small_height, src_small_width, src_small from photo where object_id in (select cover_object_id from album where owner = %s )",
									(szUid=="me")?"me()": (szUid=="")?"me()": szUid.c_str());
		nResult = CallFQLQuery(cHttpResp,szAlbumThumbNailQry);
		EXCEPTION_BREAK(nResult)
	
		SysList::Str2StrMapList listMap;
		util::IDataMgrFBOnly* pIFbDataMgr = dynamic_cast<util::IDataMgrFBOnly*>(m_pIDataMgr);
		nResult = pIFbDataMgr->ParseFBSrouceSmall(listMap,cHttpResp.szResp,iErr);
		EXCEPTION_BREAK(nResult)
		
		for(list<IAlbum*>::iterator itAlb = iAlbumLst.items.begin();itAlb!=iAlbumLst.items.end();++itAlb)
		{
			for (SysList::Str2StrMapList::iterator itMap = listMap.begin();itMap != listMap.end();++itMap)
			{
				LOGGER_TRACE(m_pILogger,"Album id: [%s] <-->[%s]",(*itAlb)->szId.c_str(),(*itMap)
					[FB_ALBUM_OBJECT_ID].c_str())
				if ((*itAlb)->szId==(*itMap)[FB_ALBUM_OBJECT_ID] && !(*itAlb)->szCoverPhotoId.empty())
				{
					(*itAlb)->szThumbNail = (*itMap)[FB_IMAGE_SOURCE_SMALL];
					break;
				}
			}
		}
		//finish the workaround

		CrackParamsForPagination(iAlbumLst);
	} while (false);

	//Error Handling
	ExceptionHandler(nResult, cHttpResp, iErr);

	return nResult;
}

int CFacebookService::GetProfile( IProfile& iProfile, IError& iErr, string szId/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpResp;
	do 
	{
		char lpszFql[500];
		memset(lpszFql,0x0,500);
		sprintf_s(lpszFql,"select pic, pic_big, pic_small, pic_square from profile where id = %s",
			(szId=="me")?"me()":szId.c_str()
			);

		nResult = CallFQLQuery(cHttpResp, lpszFql);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParseProfile(iProfile,cHttpResp.szResp, util::Facebook,iErr);
	} while (false);

	//Error Handling
	ExceptionHandler(nResult, cHttpResp, iErr);

	return nResult;
}

int CFacebookService::CallFQLQuery(HttpRespValObj& cHttpRespVO,  string szQry )
{
	//https://  graph.facebook.com   /  fql ? q = xxxx & access_token=xxx
	string szComposedUrl = 
		CFacebookService::S_STR_URL_PREFIX 
		+	S_SERVER_INFO.szServerName
		+ "/fql?q=" + szQry
		+ "&access_token=" + m_cConnectInfo.szAccessToken;

	int nResult = OpenUrl(cHttpRespVO, szComposedUrl);
	return nResult;
}

IConnectionInfo* CFacebookService::GetConnectionInfo()
{
	return &m_cConnectInfo;
}

void CFacebookService::CrackParamsForPagination( IPage& iPhotoLst )
{
	iPhotoLst.mapNextPageParams = util::CUrlHelper::ToParamMap(iPhotoLst.szNextPageUrl);
	iPhotoLst.mapPrevPageParams = util::CUrlHelper::ToParamMap(iPhotoLst.szPreviousPageUrl);
}

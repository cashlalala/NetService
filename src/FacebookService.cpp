#include "StdAfx.h"
#include "FacebookService.h"
#include "MapHelper.h"
#include "FBPhotoModel.h"
#include "FBErrorModel.h"
#include "FBVideoModel.h"
#include "DataMgrFactory.h"
#include "NetServiceErr.h"
#include "UrlHelper.h"
#include "FBUserModel.h"
//#include "..\..\Utility\Debug.h"

#include <cassert>
#include <sstream>

using systypes::EnCategory;
using systypes::EnHttpMethod;
using util::CMapHelper;
using std::stringstream;
using namespace model;

const string CFacebookService::S_STR_URL_PREFIX = "https://";

const SysMaps::EnSvrInfo2Str
CFacebookService::S_MAP_SERVER_INFO = CMapHelper::CreateServerInfoMap();


const SysMaps::EnCat2Str 
CFacebookService::S_MAP_CATEGORY = CMapHelper::CreateCategoryMap();

CFacebookService::CFacebookService(void):
m_pIDataMgr(NULL)
{
	m_pIDataMgr = util::CDataMgrFactory::GetInstance(util::JsonCpp);
}

CFacebookService::~CFacebookService(void)
{
	util::CDataMgrFactory::DeleteInstance(m_pIDataMgr);
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
		+	CMapHelper::GetValue(S_MAP_SERVER_INFO,systypes::ServerName)
		+ "/"
		+ ((szId=="")? (m_cConnectInfo.szUid=="")? "me": m_cConnectInfo.szUid : szId)
		+ "/"
		+ CMapHelper::GetValue(S_MAP_CATEGORY,enCatogory)
		+ (mapParams.empty()? "" :"?"+ CMapHelper::ToParamString(mapParams));

	//dprintf("Composed Url is [%s]",szComposedUrl.c_str());
	
	int nResult = OpenUrl(cHttpRespVO, szComposedUrl);

	return nResult;

}

string CFacebookService::GetLoginURL( string szAppId, string szScope /*= "read_stream,publish_stream,user_photos,friends_photos,user_videos,friends_videos,offline_access"*/ )
{
	string szUrl = "https://www.facebook.com/dialog/oauth?";
	szUrl	 += "&client_id=" + szAppId;
	szUrl += "&redirect_uri=http://www.facebook.com/connect/login_success.html" ;
	szUrl += "&display=popup";
	szUrl += "&scope=" + szScope;
	return util::CUrlHelper::EncodeUrl(szUrl);
}

int CFacebookService::GetPhotos(  IPhotoList& iPhotoLst, IError& iErr, string szId, SysMaps::Str2Str& mapQryCriteria)
{
	int nResult = E_FAIL;
	model::CFBPhotoList listPhoto;
	HttpRespValObj cHttpResp;
	CFBError* cFBErr = dynamic_cast<CFBError*>(&iErr);
	do 
	{
		nResult = CallGraphAPI(cHttpResp, szId, Photo,mapQryCriteria);
		EXCEPTION_HANDLING(nResult)

		nResult = m_pIDataMgr->ParsePhotoList(iPhotoLst,cHttpResp.szResp,util::Facebook,*cFBErr);
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
			EXCEPTION_HANDLING(nResult)

			nResult = m_pIDataMgr->ParseUser(*cFbUsr,cHttpResp.szResp,util::Facebook,iErr);
			EXCEPTION_HANDLING(nResult)

			iUserLst.listUser.push_back(cFbUsr);
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
			SAFE_DELETE_LIST(list<IUser*>,iUserLst.listUser);

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
		EXCEPTION_HANDLING(nResult)

		nResult = m_pIDataMgr->ParseUser( iUser,cHttpResp.szResp,util::Facebook,iErr);
		EXCEPTION_HANDLING(nResult)

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
		EXCEPTION_HANDLING(nResult);

		m_pIDataMgr->ParseFriendList(iUserLst,cHttpResp.szResp,util::Facebook,iErr);
		nResult = S_OK;
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
		EXCEPTION_HANDLING(nResult)

		nResult = m_pIDataMgr->ParseVideoList(iVideoList,cHttpResp.szResp, util::Facebook, iErr);
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
		EXCEPTION_HANDLING(nResult)

		nResult = m_pIDataMgr->ParseAlbumList(iAlbumLst,cHttpResp.szResp,util::Facebook,iErr);
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
		EXCEPTION_HANDLING(nResult)

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
		+	CMapHelper::GetValue(S_MAP_SERVER_INFO,systypes::ServerName)
		+ "/fql?q=" + szQry
		+ "&access_token=" + m_cConnectInfo.szAccessToken;

	int nResult = OpenUrl(cHttpRespVO, szComposedUrl);
	return nResult;
}

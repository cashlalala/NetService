#include "StdAfx.h"
#include "FacebookService.h"
#include "MapHelper.h"
#include "FacebookPhotoModel.h"
#include "DataMgrFactory.h"
#include "NetServiceErr.h"
#include "UrlHelper.h"
#include "FBUserModel.h"
#include "..\..\Utility\Debug.h"

#include <cassert>
#include <sstream>

using systypes::EnCategory;
using systypes::EnHttpMethod;
using util::CMapHelper;
using std::stringstream;

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

SysMaps::Str2Str CFacebookService::PrepareParams( string szMethod, SysMaps::Str2Str& params, bool bSignature )
{
	throw std::exception("The method or operation is not implemented.");
}

void CFacebookService::CheckError( string szRootNode )
{
	throw std::exception("The method or operation is not implemented.");
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

	dprintf("Composed Url is [%s]",szComposedUrl.c_str());
	
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
	return CUrlHelper::EncodeUrl(szUrl);
}

int CFacebookService::GetPhotos(  IPhotoList& iPhotoLst, IError& iErr, string szId, SysMaps::Str2Str& mapQryCriteria)
{
	int nResult = E_FAIL;
	model::CFacebookPhotoList listPhoto;
	HttpRespValObj cHttpResp;
	model::CFBError* cFBErr = dynamic_cast<model::CFBError*>(&iErr);
	do 
	{
		nResult = CallGraphAPI(cHttpResp, szId, Photo,mapQryCriteria);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParsePhotoList(iPhotoLst,cHttpResp.szResp,util::Facebook,*cFBErr);
	} while (false);
	
	//Error Handling
	if (nResult == NS_E_INET_CONNECT_FAIL_API_RETURN_ERROR ||
		nResult == NS_E_INET_CONNECT_FAIL_HTTP_STATUS_ERROR)
	{	
		stringstream ss;
		ss << "API return Code: [" << cHttpResp.dwError << "] Http Status: [" << cHttpResp.dwStatusCode << "] Response Msg:[" << cHttpResp.szResp <<"]";
		iErr.szMsg = ss.str() ;
	}
	
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

			nResult = m_pIDataMgr->ParseUser(cHttpResp.szResp,*cFbUsr,util::Facebook,iErr);
			EXCEPTION_BREAK(nResult)

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

			NETSERV_SAFE_DELETE(cFbUsr);
			NETSERV_LIST_SAFE_DELETE(list<IUser*>,iUserLst.listUser);

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

		nResult = m_pIDataMgr->ParseUser(cHttpResp.szResp, iUser,util::Facebook,iErr);
		EXCEPTION_BREAK(nResult)

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
	}

	return nResult;
}

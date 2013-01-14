#include "StdAfx.h"
#include "FlickrService.h"
#include "FlickrFields.h"
#include "MapHelper.h"
#include "NetServiceErr.h"
#include "CodecHelper.h"
#include "OAuthHelper.h"
#include "UrlHelper.h"
#include "DataMgrFactory.h"
#include "LoggerMgr.h"
#include "FkRErrorModel.h"
#include "FkRPhotoModel.h"
#include "StringHelper.h"

#include <sstream>
#include <assert.h>

using std::stringstream;

#define MAP_STRING_WITH_CONDITION(targetMap,condition,key,val) 	\
	if (targetMap[key]==condition) targetMap[key] = val;

const string CFlickrService::S_STR_URL_PREFIX = "http://";

const string CFlickrService::S_OATUH_AUTHORIZE_URL = "http://www.flickr.com/services/oauth/authorize";

const string CFlickrService::S_OAUTH_RQSTTOKEN_URL = "http://www.flickr.com/services/oauth/request_token";

const string CFlickrService::S_OAUTH_CALLBACK_URL = "http://www.flickr.com";

const ServerInfo CFlickrService::S_SERVER_INFO = {"api.flickr.com","/services/rest/?","80","443"};

string CFlickrService::S_FROB;


CFlickrService::CFlickrService(void)
{
	m_pIDataMgr = util::CDataMgrFactory::GetInstance(util::JsonCpp);
	m_pILogger = util::CLoggerMgr::GetLogger(util::Log4Cxx,"CFlickrService");
}


CFlickrService::~CFlickrService(void)
{
	//util::CDataMgrFactory::DeleteInstance(m_pIDataMgr);
	delete m_pIDataMgr;
}

void CFlickrService::SetConnectionInfo( IConnectionInfo& cConectInfoVO )
{
	m_cConnectInfo = *(dynamic_cast<CFlickrConnectionInfo*>(&cConectInfoVO));
	m_cConnectInfo.szFrob = S_FROB;
}

int CFlickrService::GetPhotos( IPhotoList& iPhotoLst, IError& iErr, string szId /*= "me"*/, SysMaps::Str2Str& mapQryCriteria/*=SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpResp;
	if (!szId.empty() && mapQryCriteria[FLICK_PARAM_USER_ID].empty()) 
		mapQryCriteria[FLICK_PARAM_USER_ID] = szId;
	mapQryCriteria[FLICK_PARAM_METHOD] = FLICK_METHOD_PHOTO_SEARCH;
	mapQryCriteria[FLICK_FIELD_EXTRA] = util::CStringHelper::Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
																			FLICK_PHOTO_URL_C,FLICK_PHOTO_URL_O,
																			FLICK_PHOTO_URL_T,FLICK_PHOTO_URL_L,
																			FLICK_PHOTO_URL_M,FLICK_PHOTO_URL_Q,
																			FLICK_PHOTO_URL_S,FLICK_PHOTO_URL_SQ,
																			FLICK_PHOTO_URL_N,FLICK_PHOTO_ORIGINAL_FORMAT,
																			FLICK_PHOTO_MEDIA);
	do 
	{
		nResult = CallApi(cHttpResp,iErr, mapQryCriteria);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParsePhotoList(iPhotoLst,ExtractJsonStrFromReply(cHttpResp.szResp),util::Flickr,iErr);
		EXCEPTION_BREAK(nResult)

		ComposePagingUrl(iPhotoLst,mapQryCriteria);
	} while (false);
	return nResult;
}

int CFlickrService::CallApi( HttpRespValObj& cHttpRespVO, IError& iErr, SysMaps::Str2Str& mapParams /*= SysMaps::Str2Str()*/, EnHttpMethod enMethod /*= systypes::Get*/ )
{
	int nResult = E_FAIL;

	nResult = PreCallApi(iErr, mapParams);
	if (!SUCCEEDED(nResult)) return nResult;

		//http:// api.flickr.com/services/rest/?method=flickr.people.getInfo&api_key=29ad045368681f23ec8bba5b2ac99a07&user_id=91328748%40N02&format=rest&auth_token=72157632466031231-b19acae054059fc1&api_sig=c9719ae3bd5191234082488a9f371ad6
	string szComposedUrl = ComposeUrl(mapParams);
	nResult = OpenUrl(cHttpRespVO,szComposedUrl);
	ExceptionHandler(nResult,cHttpRespVO,iErr);

	return nResult;
}

int CFlickrService::GetLoginURL(string& szLoginUrl, const string& szAppId, const string& szAppSecret, IError& iErr, string szScope /*= "write" */ )
{
	int nResult = E_FAIL;
	model::CFkrError cFkrErr;
	do 
	{
		//Normally, there are only two scenarios when you need to get url. First, you don't have the auth token; Second, you need refresh the token
		m_cConnectInfo.szAuthToken = "";
		S_FROB = "";
		nResult = GetFlickrAuthFrob(S_FROB, szAppId, szAppSecret, cFkrErr);
		EXCEPTION_BREAK(nResult);

		SysMaps::Str2Str mapParams;
		mapParams[FLICK_PARAM_API_KEY] = szAppId;
		mapParams[FLICK_PARAM_PERMISSION] = szScope;
		mapParams[FLICK_PARAM_FROB] = S_FROB;
		mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->ToMD5(mapParams,szAppSecret.c_str());

		szLoginUrl = "http://www.flickr.com/services/auth/?"  + util::CMapHelper::ToParamString(mapParams);
		m_pILogger->Debug("Get Login Url :[%s]",szLoginUrl.c_str());
	} while (false);

	return nResult;
}

int CFlickrService::GetVideos( IVideoList& iVideoList, IError& iErr, string szId/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	return 0;
}

int CFlickrService::GetUsersInfo( IUserList& iUserLst, IError& iErr, SysList::StrList& listUid, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	return 0;
}

int CFlickrService::GetUserInfo( IUser& iUser, IError& iErr, string szUid/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	return 0;
}

int CFlickrService::GetFriends( IUserList& iUserLst, IError& iErr, string szUid/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	return 0;
}

int CFlickrService::GetAlbums( IAlbumList& iAlbumLst, IError& iErr, string szUid/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	return 0;
}

int CFlickrService::GetProfile( IProfile& iProfile, IError& iErr, string szId/*="me"*/, SysMaps::Str2Str& mapQryCriteria /*= SysMaps::Str2Str()*/ )
{
	return 0;
}

int CFlickrService::GetFlickrAuthFrob( std::string& szFrob, const std::string& szAppId, const string& szAppSecret, IError& iErr )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpRespVO;

	SysMaps::Str2Str mapParams;
	mapParams[FLICK_PARAM_API_KEY] = szAppId;
	mapParams[FLICK_PARAM_METHOD] = FLICK_METHOD_AUTH_GETFROB;
	mapParams[FLICK_PARAM_FORMAT] = FLICK_FORMAT_JSON;
	mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->ToMD5(mapParams,szAppSecret.c_str());

	string szComposedUrl = ComposeUrl(mapParams);
	do 
	{
		nResult = OpenUrl(cHttpRespVO,szComposedUrl);
		EXCEPTION_BREAK(nResult)

		nResult = m_pIDataMgr->ParseFkrFrob(szFrob,ExtractJsonStrFromReply(cHttpRespVO.szResp),iErr);
	} while (false);

	ExceptionHandler(nResult, cHttpRespVO, iErr);

	return nResult;
}

//This api can't be tested alone
int CFlickrService::GetFlickrAuthToken( string& szAuthTok, IError& iErr )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpRespVO;
	do 
	{	
		SysMaps::Str2Str mapParams;
		mapParams[FLICK_PARAM_API_KEY] = m_cConnectInfo.lpcszApiKey;
		mapParams[FLICK_PARAM_METHOD] = FLICK_METHOD_AUTH_GETTOKEN;
		mapParams[FLICK_PARAM_FROB] = m_cConnectInfo.szFrob; //the user must be loged in and authorizing the app to get frob
		mapParams[FLICK_PARAM_FORMAT] = FLICK_FORMAT_JSON;
		mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->ToMD5(mapParams,m_cConnectInfo.szAppSecret.c_str());
		
		string szComposedUrl = ComposeUrl(mapParams);

		nResult = OpenUrl(cHttpRespVO,szComposedUrl);
		EXCEPTION_BREAK(nResult);

		nResult = m_pIDataMgr->ParseFkrAuthToken(szAuthTok,ExtractJsonStrFromReply(cHttpRespVO.szResp),iErr);
	} while (false);

	ExceptionHandler(nResult, cHttpRespVO, iErr);

	return nResult;
}

string CFlickrService::ComposeUrl( SysMaps::Str2Str& mapParams )
{
	return S_STR_URL_PREFIX
		+ S_SERVER_INFO.szServerName
		+ S_SERVER_INFO.szServerURL 
		+ util::CMapHelper::ToParamString(mapParams);
}


SysMaps::Str2Str CFlickrService::CreateApiSignatureHMACSHA1( const systypes::SysMaps::Str2Str& param, const string& serviceSharedSecret, const string& apiKey, const string& oauthToken, const string& tokenSecret /*= ""*/, const string& httpMethod /*= "GET"*/, const string& url /*= ""*/, bool bReturnOAuthParam /*= false*/ )
{
	assert(serviceSharedSecret.length() > 0);
	assert(apiKey.length() > 0);
	//assert(oauthToken.length() > 0);

	string timestamp = util::COAuthHelper::CreateTimestamp();
	string nonce = util::COAuthHelper::CreateNonce();

	systypes::SysMaps::Str2Str oauthParameters;

	oauthParameters["oauth_timestamp"] = timestamp;
	oauthParameters["oauth_nonce"] = nonce;
	oauthParameters["oauth_version"] = "1.0";
	oauthParameters["oauth_signature_method"] = "HMAC-SHA1";
	oauthParameters["oauth_consumer_key"] = apiKey;

	if (!oauthToken.empty())
	{
		oauthParameters["oauth_token"] = oauthToken;
	}

	systypes::SysMaps::Str2Str allParameters = oauthParameters;

	allParameters.insert(param.begin(), param.end());

	string normalUrl = util::COAuthHelper::NormalizeUrl(url);
	//allParameters[FLICK_OAUTH_CALLBACK] = util::COAuthHelper::NormalizeUrl(allParameters[FLICK_OAUTH_CALLBACK]);
	string normalizedParameters = util::COAuthHelper::NormalizeRequestParameters(allParameters);
	string signatureBase = util::COAuthHelper::ConcatenateRequestElements(httpMethod, normalUrl, normalizedParameters);

	string signature = util::COAuthHelper::CreateSignature(signatureBase, serviceSharedSecret, tokenSecret);
	allParameters["oauth_signature"] = signature;
	oauthParameters["oauth_signature"] = signature;

	if(bReturnOAuthParam)
	{
		return oauthParameters;
	}
	else
	{
		return allParameters;
	}
}

int CFlickrService::GetOAuthRqstToken( string& szOAuthRqstToken, string& szOAuthRqstTokenSecret, IError& iErr )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpRespVO;

	SysMaps::Str2Str mapParams;
	//mapParams[FLICK_OAUTH_CALLBACK] = "http%3A%2F%2Fwww.flickr.com";
	mapParams = CreateApiSignatureHMACSHA1(mapParams,m_cConnectInfo.szAppSecret,m_cConnectInfo.lpcszApiKey,"","","GET",S_OAUTH_RQSTTOKEN_URL);

	string szComposedUrl = S_OAUTH_RQSTTOKEN_URL  + "?" + util::CMapHelper::ToParamString(mapParams);

	nResult = OpenUrl(cHttpRespVO,szComposedUrl);
	szOAuthRqstToken = cHttpRespVO.szResp;
	szOAuthRqstTokenSecret= cHttpRespVO.szResp;
	return nResult;
}

int CFlickrService::GetOAuthAuthorizeToken( string& szOAuthAuthorizeToken, IError& iErr )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpRespVO;

	do 
	{
		string szOAuthRqstToken;
		string szOAuthRqstTokenSecret;
		nResult = GetOAuthRqstToken(szOAuthRqstToken, szOAuthRqstTokenSecret, iErr);
		EXCEPTION_BREAK(nResult);

		SysMaps::Str2Str mapParams;
		mapParams[FLICK_PARAM_PERMISSION] = "write";
		mapParams = CreateApiSignatureHMACSHA1(mapParams,m_cConnectInfo.szAppSecret,m_cConnectInfo.lpcszApiKey,szOAuthRqstToken,szOAuthRqstTokenSecret,"GET",S_OAUTH_RQSTTOKEN_URL);
		string szComposedUrl = ComposeUrl(mapParams);

		nResult = OpenUrl(cHttpRespVO,szComposedUrl);
	} while (false);

	return nResult;
}

string CFlickrService::ExtractJsonStrFromReply( const string& szReply )
{
	if (szReply.find("jsonFlickrApi")!=string::npos)
	{
		size_t nObjBegin = szReply.find_first_of("{");
		size_t nObjEnd = szReply.find_last_of(")");
		return szReply.substr(nObjBegin,nObjEnd-nObjBegin);
	}
	return szReply;
}

void CFlickrService::ComposePagingUrl( IPhotoList& iPhotoLst, const SysMaps::Str2Str& mapParams )
{
	model::CFkrPhotoList* cFkrPhotoLst = dynamic_cast<model::CFkrPhotoList*>( &iPhotoLst);
	SysMaps::Str2Str mapCpy(mapParams);
	SysMaps::Str2Str::const_iterator cit;
	if (cFkrPhotoLst->nPage<cFkrPhotoLst->nPages/*next page*/)
	{
		mapCpy[FLICK_PHOTOS_PAGE] = util::CStringHelper::Format("%d",  cFkrPhotoLst->nPage+1);
		cit = mapCpy.find(FLICK_PARAM_API_SIG);
		mapCpy.erase(cit);
		mapCpy[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->ToMD5(mapCpy,m_cConnectInfo.szAppSecret.c_str());
		iPhotoLst.szNext = ComposeUrl(mapCpy);
	}
	if (cFkrPhotoLst->nPage>1 /*prev page*/)
	{
		mapCpy[FLICK_PHOTOS_PAGE] = util::CStringHelper::Format("%d",  cFkrPhotoLst->nPage-1);
		cit = mapCpy.find(FLICK_PARAM_API_SIG);
		mapCpy.erase(cit);
		mapCpy[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->ToMD5(mapCpy,m_cConnectInfo.szAppSecret.c_str());
		iPhotoLst.szPrevious = ComposeUrl(mapCpy);	
	}
}

int CFlickrService::PreCallApi( IError& iErr, SysMaps::Str2Str &mapParams )
{
	int nResult = E_FAIL;

	do 
	{
		if (mapParams[FLICK_PARAM_METHOD]=="")
		{
			nResult = NS_E_SN_FLICKR_NO_METHOD;
			EXCEPTION_BREAK(nResult)
		}
		if (mapParams[FLICK_PARAM_AUTH_TOKEN].empty())
		{
			if (m_cConnectInfo.szAuthToken.empty())
			{
				
				nResult = GetFlickrAuthToken(m_cConnectInfo.szAuthToken,iErr);
				m_pILogger->Trace("Get Auth Token: [%s]",m_cConnectInfo.szAuthToken.c_str());
				EXCEPTION_BREAK(nResult)
			}
			mapParams[FLICK_PARAM_AUTH_TOKEN] = m_cConnectInfo.szAuthToken;
		}
		MAP_STRING_WITH_CONDITION(mapParams,"",FLICK_PARAM_API_KEY,m_cConnectInfo.lpcszApiKey)
		MAP_STRING_WITH_CONDITION(mapParams,"",FLICK_PARAM_FORMAT,FLICK_FORMAT_JSON)
		mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->ToMD5(mapParams,m_cConnectInfo.szAppSecret.c_str());
	} while (false);

	return nResult;
}

IConnectionInfo* CFlickrService::GetConnectionInfo()
{
	return &m_cConnectInfo;
}

void CFlickrService::ExceptionHandler( int nResult, HttpRespValObj &cHttpRespVO, IError &iErr )
{
	if (!SUCCEEDED(nResult))
	{
		if (nResult == NS_E_INET_CONNECT_FAIL_API_RETURN_ERROR ||
			nResult == NS_E_INET_CONNECT_FAIL_HTTP_STATUS_ERROR)
		{
			stringstream ss;
			ss << "API return Code: [" << cHttpRespVO.dwError << "] Http Status: [" << cHttpRespVO.dwStatusCode << "] Response Msg:[" << cHttpRespVO.szResp <<"]";
			iErr.szMsg = ss.str() ;
		}
	}
}

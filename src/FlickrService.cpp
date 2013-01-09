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

#include <assert.h>


#define MAP_STRING_WITH_CONDITION(targetMap,condition,key,val) 	\
	if (targetMap[key]==condition) targetMap[key] = val;

const string CFlickrService::S_STR_URL_PREFIX = "http://";

const string CFlickrService::S_OATUH_AUTHORIZE_URL = "http://www.flickr.com/services/oauth/authorize";

const string CFlickrService::S_OAUTH_RQSTTOKEN_URL = "http://www.flickr.com/services/oauth/request_token";

const string CFlickrService::S_OAUTH_CALLBACK_URL = "http://www.flickr.com";

const ServerInfo CFlickrService::S_SERVER_INFO = {"api.flickr.com","/services/rest/?","80","443"};


CFlickrService::CFlickrService(void)
{
	m_pIDataMgr = util::CDataMgrFactory::GetInstance(util::JsonCpp);
	m_pILogger = util::CLoggerMgr::GetLogger(util::Log4Cxx,"CFlickrService");
}


CFlickrService::~CFlickrService(void)
{
	util::CDataMgrFactory::DeleteInstance(m_pIDataMgr);
}

void CFlickrService::SetConnectionInfo( IConnectionInfo& cConectInfoVO )
{
	m_cConnectInfo = *(dynamic_cast<CFlickrConnectionInfo*>(&cConectInfoVO));
}

int CFlickrService::GetPhotos( IPhotoList& iPhotoLst, IError& iErr, string szId /*= "me"*/, SysMaps::Str2Str& mapQryCriteria/*=SysMaps::Str2Str()*/ )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpResp;
	if (!szId.empty() && mapQryCriteria[FLICK_PARAM_USER_ID].empty()) 
		mapQryCriteria[FLICK_PARAM_USER_ID] = szId;
	mapQryCriteria[FLICK_PARAM_METHOD] = FLICK_METHOD_PHOTO_SEARCH;
	nResult = CallApi(cHttpResp,mapQryCriteria);
	return nResult;
}

int CFlickrService::CallApi( HttpRespValObj& cHttpRespVO, SysMaps::Str2Str& mapParams /*= SysMaps::Str2Str()*/, EnHttpMethod enMethod /*= Get*/ )
{
	if (mapParams[FLICK_PARAM_METHOD]=="")
		return NS_E_SN_FLICKR_NO_METHOD;
	MAP_STRING_WITH_CONDITION(mapParams,"",FLICK_PARAM_AUTH_TOKEN,m_cConnectInfo.szAuthToken)
	MAP_STRING_WITH_CONDITION(mapParams,"",FLICK_PARAM_API_KEY,m_cConnectInfo.lpcszApiKey)
	mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->CreateApiSignature(mapParams,m_cConnectInfo.szAppSecret.c_str());

	//http:// api.flickr.com/services/rest/?method=flickr.people.getInfo&api_key=29ad045368681f23ec8bba5b2ac99a07&user_id=91328748%40N02&format=rest&auth_token=72157632466031231-b19acae054059fc1&api_sig=c9719ae3bd5191234082488a9f371ad6
	string szComposedUrl = ComposeUrl(mapParams);
	int nResult = OpenUrl(cHttpRespVO,szComposedUrl);
	return nResult;
}

string CFlickrService::GetLoginURL( string szAppId, string szScope /*= "write" */ )
{
	int nResult = E_FAIL;
	model::CFkRError cFkrErr;
	string szUrl ;
	do 
	{
		if (m_cConnectInfo.szFrob.empty())
		{
			nResult = GetFrob(m_cConnectInfo.szFrob,cFkrErr);
			EXCEPTION_HANDLING(nResult);
		}

		SysMaps::Str2Str mapParams;
		mapParams[FLICK_PARAM_API_KEY] = szAppId;
		mapParams[FLICK_PARAM_PERMISSION] = szScope;
		mapParams[FLICK_PARAM_FROB] = m_cConnectInfo.szFrob;
		mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->CreateApiSignature(mapParams,m_cConnectInfo.szAppSecret.c_str());

		szUrl = "http://flickr.com/services/auth/?"  + util::CMapHelper::ToParamString(mapParams);
		m_pILogger->Debug("Get Login Url :[%s]",szUrl.c_str());
	} while (false);

	return szUrl;
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

int CFlickrService::GetFrob( std::string& szFrob, IError& iErr )
{
	int nResult = E_FAIL;
	HttpRespValObj cHttpRespVO;

	SysMaps::Str2Str mapParams;
	mapParams[FLICK_PARAM_API_KEY] = m_cConnectInfo.lpcszApiKey;
	mapParams[FLICK_PARAM_METHOD] = FLICK_METHOD_AUTH_GETFROB;
	mapParams[FLICK_PARAM_FORMAT] = FLICK_FORMAT_JSON;
	mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->CreateApiSignature(mapParams,m_cConnectInfo.szAppSecret.c_str());

	string szComposedUrl = ComposeUrl(mapParams);
	do 
	{
		nResult = OpenUrl(cHttpRespVO,szComposedUrl);
		EXCEPTION_HANDLING(nResult)

		nResult = m_pIDataMgr->ParseFkrFrob(szFrob,ExtractJsonStrFromReply(cHttpRespVO.szResp),iErr);
	} while (false);

	return nResult;
}

//This api can't be tested alone
int CFlickrService::GetFlickRAuthToken( string& szAuthTok, IError& iErr )
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
		mapParams[FLICK_PARAM_API_SIG] = util::CCodecHelper::GetInstance()->CreateApiSignature(mapParams,m_cConnectInfo.szAppSecret.c_str());
		
		string szComposedUrl = ComposeUrl(mapParams);

		nResult = OpenUrl(cHttpRespVO,szComposedUrl);
		EXCEPTION_HANDLING(nResult);

		nResult = m_pIDataMgr->ParseFkrAuthToken(szAuthTok,ExtractJsonStrFromReply(cHttpRespVO.szResp),iErr);
	} while (false);

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
		EXCEPTION_HANDLING(nResult);

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
	size_t nObjBegin = szReply.find_first_of("{");
	size_t nObjEnd = szReply.find_last_of(")");
	return szReply.substr(nObjBegin,nObjEnd-nObjBegin);
}

#pragma once

#include "baseservice.h"
#include "IDataManager.h"

using systypes::SysMaps;
using systypes::EnCategory;
using systypes::EnHttpMethod;

class CFlickrService :
	public CBaseSocialService
{
public:
	CFlickrService(void);
	virtual ~CFlickrService(void);

	virtual void SetConnectionInfo(IConnectionInfo& cConectInfoVO);

	virtual string GetLoginURL( string szAppId, string szScope = "write" );

	virtual int GetPhotos(  IPhotoList& iPhotoLst, IError& iErr, string szId = "me", SysMaps::Str2Str& mapQryCriteria=SysMaps::Str2Str());

	virtual int GetVideos(IVideoList& iVideoList, IError& iErr, string szId="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) ;

	virtual int GetUsersInfo(IUserList& iUserLst, IError& iErr, SysList::StrList& listUid, SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetUserInfo(IUser& iUser, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetFriends(IUserList& iUserLst, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) ;

	virtual int GetAlbums(IAlbumList& iAlbumLst, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetProfile(IProfile& iProfile, IError& iErr, string szId="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

private:
	static const string S_STR_URL_PREFIX;
	static const string S_OAUTH_RQSTTOKEN_URL;
	static const string S_OATUH_AUTHORIZE_URL;
	static const string S_OAUTH_CALLBACK_URL;
	static const ServerInfo S_SERVER_INFO;

	CFlickrConnectionInfo m_cConnectInfo;
	util::IDataManager* m_pIDataMgr;
	util::ILogger* m_pILogger;

	string ExtractJsonStrFromReply(const string& szReply);
public:
	int CallApi(HttpRespValObj& cHttpRespVO, SysMaps::Str2Str& mapParams = SysMaps::Str2Str(), EnHttpMethod enMethod = systypes::Get);

	string ComposeUrl( SysMaps::Str2Str& mapParams );

	//For flickr authorization
	int GetFrob(std::string& szFrob, IError& iErr);

	int GetFlickRAuthToken(string& szAuthTok, IError& iErr );

	//For flickr OAuth 1.0
	int GetOAuthRqstToken(string& szOAuthRqstToken, string& szOAuthRqstTokenSecret, IError& iErr);

	int GetOAuthAuthorizeToken(string& szOAuthAuthorizeToken, IError& iErr);


	SysMaps::Str2Str CreateApiSignatureHMACSHA1( const SysMaps::Str2Str& param, 
																					const string& serviceSharedSecret, 
																					const string& apiKey, 
																					const string& oauthToken,
																					const string& tokenSecret = "", 
																					const string& httpMethod = "GET", 
																					const string& url = "", 
																					bool bReturnOAuthParam = false );

};


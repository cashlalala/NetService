#pragma once
#include "baseservice.h"
#include "IDataManager.h"

using systypes::SysMaps;
using systypes::EnCategory;
using systypes::EnHttpMethod;

class CFacebookService :
	public CBaseSocialService
{
public:
	CFacebookService(void);
	virtual ~CFacebookService(void);

	virtual void SetConnectionInfo(IConnectionInfo& cConectInfoVO);

	virtual int GetLoginURL(string& szLoginUrl, const string& szAppId, IError& iErr, string szScope = "read_stream,publish_stream,user_photos,friends_photos,user_videos,friends_videos,offline_access");

	virtual int GetPhotos(  IPhotoList& iPhotoLst, IError& iErr, string szId = "me", SysMaps::Str2Str& mapQryCriteria=SysMaps::Str2Str());

	virtual int GetVideos(IVideoList& iVideoList, IError& iErr, string szId="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) ;

	virtual int GetUsersInfo(IUserList& iUserLst, IError& iErr, SysList::StrList& listUid, SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetUserInfo(IUser& iUser, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetFriends(IUserList& iUserLst, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) ;

	virtual int GetAlbums(IAlbumList& iAlbumLst, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetProfile(IProfile& iProfile, IError& iErr, string szId="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

private:

	static const SysMaps::EnCat2Str S_MAP_CATEGORY;
	static const string S_STR_URL_PREFIX;

	static const ServerInfo S_SERVER_INFO;

	CFBConnectionInfo m_cConnectInfo;
	util::IDataManager* m_pIDataMgr;

private:
	int CallGraphAPI(HttpRespValObj& cHttpRespVO,
									string szId = "me", 
									EnCategory enCatogory = systypes::None, 
									SysMaps::Str2Str mapParams = SysMaps::Str2Str(),
									EnHttpMethod enMethod = systypes::Get,
									bool bCheckError =  true);

	int CallFQLQuery(HttpRespValObj& cHttpRespVO, string szQry);

	void ExceptionHandler( int nResult, HttpRespValObj &cHttpResp, IError &iErr );

};

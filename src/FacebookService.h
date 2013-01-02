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

	virtual string GetLoginURL( string szAppId, string szScope = "read_stream,publish_stream,user_photos,friends_photos,user_videos,friends_videos,offline_access" );

	virtual int GetPhotos(  IPhotoList& iPhotoLst, IError& iErr, string szId = "me", SysMaps::Str2Str& mapQryCriteria=SysMaps::Str2Str());

	virtual int GetVideos(IVideoList& iVideoList, IError& iErr, string szId="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) ;

	virtual int GetUsersInfo(IUserList& iUserLst, IError& iErr, SysList::StrList& listUid, SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetUserInfo(IUser& iUser, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str());

	virtual int GetFriends(IUserList& iUserLst, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) ;

private:

	static const SysMaps::EnCat2Str S_MAP_CATEGORY;
	static const SysMaps::EnSvrInfo2Str S_MAP_SERVER_INFO;
	static const string S_STR_URL_PREFIX;

	CFBConnectionInfo m_cConnectInfo;
	util::IDataManager* m_pIDataMgr;

private:
	int CallGraphAPI(HttpRespValObj& cHttpRespVO,
									string szId = "me", 
									EnCategory enCatogory = systypes::None, 
									SysMaps::Str2Str mapParams = SysMaps::Str2Str(),
									EnHttpMethod enMethod = systypes::Get,
									bool bCheckError =  true);

	void ErrorHandler( int nResult, HttpRespValObj &cHttpResp, IError &iErr );

};

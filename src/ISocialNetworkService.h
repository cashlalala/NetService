#pragma once
#include "SysTypes.h"
#include "IConnectionInfo.h"
#include "IPhotoModel.h"
#include "IUserModel.h"
#include "IErrorModel.h"
#include "IVideoModel.h"
#include "IAlbumModel.h"

#include <string>

using systypes::SysMaps;
using systypes::SysList;
using std::string;
using model::IPhoto;
using model::IPhotoList;
using model::IUserList;
using model::IError;
using model::IUser;
using model::IVideoList;
using model::IAlbumList;
using model::IProfile;

typedef enum {
	FACEBOOK = 0,
	FLICKR = 1
} EnServiceType;

struct ISocialNetworkService
{	
	virtual ~ISocialNetworkService() = 0;


	virtual void SetConnectionInfo(IConnectionInfo& cConectInfoVO) = 0;

	/*
	* ----------------Mighty Functions----------------
	*/
	//virtual string ServiceApi(string szInput) = 0;

	/*
	* ----------------Logging Functions----------------
	*/
	virtual string GetLoginURL(string szAppId, string szScope = "read_stream,publish_stream,user_photos,friends_photos,user_videos,friends_videos,offline_access") = 0;

	/*
	* ----------------Media getter Functions----------------
	*/
	//for facebook : the id can be user id, album id, ... etc., and other ids who have photos
	//for flickr: the id only means user id. If you want to specify other ids, put them into parameters map
	virtual int GetPhotos( IPhotoList& iPhotoLst, IError& iErr, string szId = "me", SysMaps::Str2Str& mapQryCriteria=SysMaps::Str2Str()) = 0;

	virtual int GetVideos(IVideoList& iVideoList, IError& iErr, string szId="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

	/*
	* ----------------User Info Functions----------------
	*/

	virtual int GetUsersInfo(IUserList& iUserLst, IError& iErr, SysList::StrList& listUid, SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

	virtual int GetUserInfo(IUser& iUser, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

	virtual int GetFriends(IUserList& iUserLst, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

	virtual int GetAlbums(IAlbumList& iAlbumLst, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

	/*
	* ----------------Profile Functions----------------
	*/
	virtual int GetProfile(IProfile& iProfile, IError& iErr, string szId="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

	
	/*
	* ----------------Exported types----------------
	*/
	typedef ISocialNetworkService* (__cdecl *PFNGETINSTANCE)(EnServiceType);
	typedef void (__cdecl *PFNDELINSTANCE)(ISocialNetworkService*);

};

inline ISocialNetworkService::~ISocialNetworkService(){};
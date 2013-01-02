#pragma once
#include "SysTypes.h"
#include "IConnectionInfo.h"
#include "IPhotoModel.h"
#include "IUserModel.h"
#include "IErrorModel.h"

#include <string>

using systypes::SysMaps;
using systypes::SysList;
using std::string;
using model::IPhoto;
using model::IPhotoList;
using model::IUserList;
using model::IError;
using model::IUser;



struct ISocialNetworkService
{	
	virtual ~ISocialNetworkService() = 0;


	virtual void SetConnectionInfo(IConnectionInfo& cConectInfoVO) = 0;

	/*
	* ----------------Logging Functions----------------
	*/
	virtual string GetLoginURL(string szAppId, string szScope = "read_stream,publish_stream,user_photos,friends_photos,user_videos,friends_videos,offline_access") = 0;

	/*
	* ----------------Data getter Functions----------------
	*/
	virtual int GetPhotos( IPhotoList& iPhotoLst, IError& iErr, string szId = "me", SysMaps::Str2Str& mapQryCriteria=SysMaps::Str2Str()) = 0;

	virtual int GetUsersInfo(IUserList& iUserLst, IError& iErr, SysList::StrList& listUid, SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

	virtual int GetUserInfo(IUser& iUser, IError& iErr, string szUid="me", SysMaps::Str2Str& mapQryCriteria = SysMaps::Str2Str()) = 0;

};

inline ISocialNetworkService::~ISocialNetworkService(){};
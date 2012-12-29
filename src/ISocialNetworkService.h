#pragma once
#include "SysTypes.h"
#include "IPhotoModel.h"
#include <map>
#include <string>

using systypes::SysMaps;
using std::map;
using std::string;
using model::IPhoto;
using model::IPhotoList;


struct ConnectionInfoValueObject
{
	string szUid;
	string szAccessToken;
};

struct ISocialNetworkService
{	
	virtual ~ISocialNetworkService() = 0;

	virtual SysMaps::Str2Str 
		PrepareParams(string szMethod, SysMaps::Str2Str params, bool bSignature) = 0;

	virtual void CheckError(string szRootNode) = 0;

	/*
	* ----------------Logging Functions----------------
	*/
	virtual string GetLoginURL(string params = "") = 0;

	/*
	* ----------------Data getter Functions----------------
	*/
	virtual IPhotoList GetPhotos( SysMaps::Str2Str mapQryCriteria=SysMaps::Str2Str(), string szId = "me") = 0;

};

inline ISocialNetworkService::~ISocialNetworkService(){};
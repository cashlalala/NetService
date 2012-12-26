#pragma once
#include "SysTypes.h"
#include <map>
#include <string>

using systypes::SysMaps;
using std::map;
using std::string;


struct ConnectionInfoValueObject
{
	string szUid;
	string szAccessToken;
};

struct ISocialNetworkService
{	

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
	virtual SysMaps::Str2Str GetPhotos(SysMaps::Str2Str mapQryCriteria) = 0;

};
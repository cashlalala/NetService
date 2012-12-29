#pragma once
#include "baseservice.h"

using systypes::SysMaps;
using systypes::EnCategory;
using systypes::EnHttpMethod;

class CFacebookService :
	public CBaseSocialService
{
public:
	CFacebookService(void);
	virtual ~CFacebookService(void);

	virtual SysMaps::Str2Str PrepareParams( string szMethod, SysMaps::Str2Str& params, bool bSignature );

	virtual void CheckError( string szRootNode );

	virtual string GetLoginURL( string params = "" );

	virtual IPhotoList GetPhotos( SysMaps::Str2Str& mapQryCriteria=SysMaps::Str2Str(), string szId = "me");

private:

	static const SysMaps::EnCat2Str S_MAP_CATEGORY;
	static const SysMaps::EnSvrInfo2Str S_MAP_SERVER_INFO;
	static const string S_STR_URL_PREFIX;
public:
	string CallGraphAPI(string szId = "me", 
									EnCategory enCatogory = systypes::None, 
									SysMaps::Str2Str mapParams = SysMaps::Str2Str(),
									EnHttpMethod enMethod = systypes::Get,
									bool bCheckError =  true);

};

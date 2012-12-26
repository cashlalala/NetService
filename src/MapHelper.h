#pragma once

#include "SysTypes.h"

using namespace systypes;

class CMapHelper
{
public:
	static SysMaps::HttpMethod2Str CreateHttpMethodMap();
	static SysMaps::EnCat2Str CreateCategoryMap();
	static SysMaps::EnSvrInfo2Str CreateServerInfoMap();
	static SysMaps::Str2Str CreateStringMap();

	static string GetValue(const SysMaps::HttpMethod2Str& map, EnHttpMethod enMethod);
	static string GetValue(const SysMaps::EnSvrInfo2Str& map, EnServerInfo enSvrInfo);
	static string GetValue(const SysMaps::EnCat2Str& map, EnCategory enCat);
};

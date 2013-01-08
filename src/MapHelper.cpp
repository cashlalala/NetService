#include "StdAfx.h"
#include "MapHelper.h"
#include "SysTypes.h"

using namespace util;

SysMaps::HttpMethod2Str CMapHelper::CreateHttpMethodMap()
{
	SysMaps::HttpMethod2Str mapHttpMethod;
	mapHttpMethod[Get] = "GET";
	mapHttpMethod[Post] = "POST";
	mapHttpMethod[Delete] = "DELETE";
	return mapHttpMethod;
}

SysMaps::EnCat2Str CMapHelper::CreateCategoryMap()
{
	SysMaps::EnCat2Str mapEnCat;
	mapEnCat[Photo] = "photos";
	mapEnCat[Video] = "videos";
	mapEnCat[Search] = "search";
	mapEnCat[None] = "";
	mapEnCat[Picture] = "picture";
	mapEnCat[Friend] = "friends";
	mapEnCat[Album] = "albums";
	return mapEnCat;
}

SysMaps::Str2Str CMapHelper::CreateStringMap()
{
	SysMaps::Str2Str mapStr;
	return mapStr;
}

string CMapHelper::GetValue( const SysMaps::HttpMethod2Str& map, EnHttpMethod enMethod )
{
	SysMaps::HttpMethod2Str::const_iterator cIt = map.find(enMethod);
	return (cIt != map.end())? cIt->second : "";
}


string CMapHelper::GetValue( const SysMaps::EnCat2Str& map, EnCategory enCat )
{
	SysMaps::EnCat2Str::const_iterator cIt = map.find(enCat);
	return (cIt != map.end())? cIt->second : "";
}

string CMapHelper::ToParamString( const SysMaps::Str2Str& map)
{
	string szParams;
	for (SysMaps::Str2Str::const_iterator cIt = map.begin();cIt!=map.end();++cIt)
		if (!cIt->second.empty())
			szParams += cIt->first + "="  + cIt->second + "&";
	return szParams.substr(0,(szParams.length()!=0)? szParams.length()-1:0);
}

#pragma once

#include "SysTypes.h"

using namespace systypes;

namespace util
{
	class CMapHelper
	{
	public:
		//static SysMaps::HttpMethod2Str CreateHttpMethodMap();
		//static SysMaps::EnCat2Str CreateCategoryMap();
		//static SysMaps::EnSvrInfo2Str CreateServerInfoMap();
		//static SysMaps::Str2Str CreateStringMap();

		static SysMaps::HttpMethod2Str CreateHttpMethodMap()
		{
			SysMaps::HttpMethod2Str mapHttpMethod;
			mapHttpMethod[Get] = "GET";
			mapHttpMethod[Post] = "POST";
			mapHttpMethod[Delete] = "DELETE";
			return mapHttpMethod;
		}

		static SysMaps::EnCat2Str CreateCategoryMap()
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

		static SysMaps::EnSvrInfo2Str CreateServerInfoMap()
		{
			SysMaps::EnSvrInfo2Str mapEnSvrInfo;
			mapEnSvrInfo[ServerName] = "graph.facebook.com";
			mapEnSvrInfo[ServerUrI] = "";
			mapEnSvrInfo[Port] = "80";
			mapEnSvrInfo[SecurityPort] = "443";
			return mapEnSvrInfo;
		}

		static SysMaps::Str2Str CreateStringMap()
		{
			SysMaps::Str2Str mapStr;
			return mapStr;
		}

		static string GetValue( const SysMaps::HttpMethod2Str& map, EnHttpMethod enMethod )
		{
			SysMaps::HttpMethod2Str::const_iterator cIt = map.find(enMethod);
			return (cIt != map.end())? cIt->second : "";
		}

		static string GetValue( const SysMaps::EnSvrInfo2Str& map, EnServerInfo enSvrInfo )
		{
			SysMaps::EnSvrInfo2Str::const_iterator cIt = map.find(enSvrInfo);
			return (cIt != map.end())? cIt->second : "";
		}

		static string GetValue( const SysMaps::EnCat2Str& map, EnCategory enCat )
		{
			SysMaps::EnCat2Str::const_iterator cIt = map.find(enCat);
			return (cIt != map.end())? cIt->second : "";
		}

		static string ToParamString( const SysMaps::Str2Str& map)
		{
			string szParams;
			for (SysMaps::Str2Str::const_iterator cIt = map.begin();cIt!=map.end();++cIt)
				szParams += cIt->first + "="  + cIt->second + "&";
			return szParams.substr(0,(szParams.length()!=0)? szParams.length()-1:0);
		}

	};

}

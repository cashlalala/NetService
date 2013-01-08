#pragma once

#include "SysTypes.h"

using namespace systypes;

namespace util
{
	class CMapHelper
	{
	public:
		static SysMaps::HttpMethod2Str CreateHttpMethodMap();
		static SysMaps::EnCat2Str CreateCategoryMap();
		static SysMaps::Str2Str CreateStringMap();
		static string GetValue( const SysMaps::HttpMethod2Str& map, EnHttpMethod enMethod );
		static string GetValue( const SysMaps::EnCat2Str& map, EnCategory enCat );
		static string ToParamString( const SysMaps::Str2Str& map);

	};

}

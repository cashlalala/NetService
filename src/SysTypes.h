#pragma once

#include <map>
#include <string>
#include <list>

using std::string;
using std::map;
using std::list;

namespace systypes
{
	typedef enum{
		Get,
		Post,
		Delete
	}EnHttpMethod;

	typedef enum {
		None,
		Picture,
		Photo,
		Album,
		Video,
		Friend,
		Search
	}EnCategory;


	struct SysMaps
	{
		typedef map<string,string> Str2Str;
		typedef map<EnHttpMethod,string> HttpMethod2Str;
		typedef map<EnCategory,string> EnCat2Str;
	};

	struct SysList
	{
		typedef list<string> StrList;
	};

}


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
		ServerName,
		ServerUrI,
		Port,
		SecurityPort
	} EnServerInfo;

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
		typedef map<EnServerInfo,string> EnSvrInfo2Str ;
	};

	struct SysList
	{
		typedef list<string> StrList;
	};

}


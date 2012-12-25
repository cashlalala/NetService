#pragma once
#include <map>
#include <string>

using std::map;
using std::string;

struct ISocialNetworkService
{
	virtual map<string,string> PrepareParams(string szMethod, map<string,string> params, bool bSignature) = 0;

	virtual void CheckError(string szRootNode) = 0;

	/*
	* ----------------Logging Functions----------------
	*/
	virtual string GetLoginURL(string params = "") = 0;

	/*
	* ----------------Data getter Functions----------------
	*/
	virtual map<string,string> GetMediaData(map<string,string> mapMedia) = 0;
	

};
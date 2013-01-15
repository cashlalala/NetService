#pragma once

struct IConnectionInfo
{
	virtual ~IConnectionInfo() =0 ;
	string lpcszApiKey;//must
	string szAppSecret; //must
};

inline IConnectionInfo::~IConnectionInfo(){};

struct CFBConnectionInfo : IConnectionInfo
{
	virtual ~CFBConnectionInfo() {};
	string szAccessToken; //must
	string szNamespace; //netservice internal use
	string szSanboxMode;//netservice internal use
};

struct CFlickrConnectionInfo : IConnectionInfo
{
	virtual ~CFlickrConnectionInfo() {};
	string szAuthToken; //netservice internal use
	string szFrob;//netservice internal use
};
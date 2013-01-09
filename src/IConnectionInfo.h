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
	string szNamespace;
	string szSanboxMode;
};

struct CFlickrConnectionInfo : IConnectionInfo
{
	virtual ~CFlickrConnectionInfo() {};
	string szAuthToken; 
	string szFrob;
};
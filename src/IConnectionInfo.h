#pragma once

struct IConnectionInfo
{
	virtual ~IConnectionInfo() =0 ;
	string szApiKey;//must
	string szAppSecret; //must
	string szUid; //option
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
	string szApiSig;
	string szFrob;
	string szAuthToken; //must
};
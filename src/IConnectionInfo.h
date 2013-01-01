#pragma once

struct IConnectionInfo
{
	virtual ~IConnectionInfo() =0 ;
	string szApiKey;//must
	string szAccessToken; //must
	string szUid; //option
};

inline IConnectionInfo::~IConnectionInfo(){};

struct CFBConnectionInfo : IConnectionInfo
{
	virtual ~CFBConnectionInfo() {};
	string szClientAppId;
};

struct CFlickrConnectionInfo : IConnectionInfo
{
	virtual ~CFlickrConnectionInfo() {};
	string szSharedSecret;
};
#pragma once

#include <string>
#include <list>
#include <memory>

#include "NetKernelLoader.h"
#include "..\..\NetKernel\Src\INetKernel.h"
#include "ILogger.h"

using std::list;
using std::string;
using std::wstring;

class CInternetConnectService
{
public:
	CInternetConnectService(void);
	virtual ~CInternetConnectService(void);

public:
	void SetProxyDetectUrl(string szUrl);
	void ForceStopNetKernel(void);
	bool DetectProxy(void);
	int OpenUrl(HttpRespValObj& cHttpRespVO, string szUrl, string szHttpMethod = HTTP_METHOD_GET, wstring wszCookieFilePath = L"", void* pfnCallBack = NULL);

	int DeleteUrlCache(int type,  const string& szCookieName);

private:
	string m_szServerAddr;
	string m_szApName;
	bool m_bIsProxyDetectSucc;
	string m_szProxyDetectUrl;
	list<INetKernel*> m_listINetKernel;
	NetKernelLoader m_cNetKernelLoader;
	util::ILogger* S_LOGGER;

};

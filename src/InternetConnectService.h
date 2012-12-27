#pragma once

#include <string>
#include <list>
#include <memory>

#include "NetKernelLoader.h"
#include "..\..\NetKernel\Src\INetKernel.h"

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
	string OpenUrl(string szUrl, string szHttpMethod = HTTP_METHOD_GET, wstring wszCookieFilePath = L"", void* pfnCallBack = NULL);


private:
	string m_szServerAddr;
	string m_szApName;
	bool m_bIsProxyDetectSucc;
	string m_szProxyDetectUrl;
	list<INetKernel*> m_listINetKernel;
	NetKernelLoader m_cNetKernelLoader;

};

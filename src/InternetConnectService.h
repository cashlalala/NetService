#pragma once

#include <string>
#include <list>
#include <memory>
#include "NetKernelLoader.h"
#include "..\..\NetKernel\Src\INetKernel.h"

using std::list;
using std::string;
using std::auto_ptr;

class CInternetConnectService
{
public:
	CInternetConnectService(void);
	~CInternetConnectService(void);

public:
	void SetProxyDetectUrl(string szUrl);
	void ForceStopNetKernel(void);
	bool DetectProxy(void);


private:
	string m_szServerAddr;
	string m_szApName;
	bool m_bIsProxyDetectSucc;
	string m_szProxyDetectUrl;
	list<INetKernel*> m_listINetKernel;
	NetKernelLoader m_cNetKernelLoader;

};

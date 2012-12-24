#include "StdAfx.h"
#include "..\..\Utility\Debug.h"
#include "InternetConnectService.h"

CInternetConnectService::CInternetConnectService(void)
: m_bIsProxyDetectSucc(false),
m_cNetKernelLoader()
{
	m_szServerAddr = "";
	m_szApName = "";
	m_szProxyDetectUrl = "";
	m_listINetKernel.clear();
}

CInternetConnectService::~CInternetConnectService(void)
{
}

void CInternetConnectService::SetProxyDetectUrl(string szUrl)
{
	this->m_szProxyDetectUrl = szUrl;
}

void CInternetConnectService::ForceStopNetKernel(void)
{
	OutputDebugString(TEXT("Force Stop NetKernel"));

	if (this->m_listINetKernel.size()==0)
		return;

	for (list<INetKernel*>::iterator it=m_listINetKernel.begin(); it!=m_listINetKernel.end();++it)
	{
		(*it)->ForceStop();
		m_listINetKernel.erase(it);
		delete (*it);
	}
}

bool CInternetConnectService::DetectProxy(void)
{
	if (this->m_bIsProxyDetectSucc)
		return true;

	auto_ptr<INetKernel> pINetKernel (m_cNetKernelLoader.GetInstance());

	HttpResponseValueObject cHttpRespVO;
	pINetKernel->OpenUrl(cHttpRespVO,m_szProxyDetectUrl.c_str());

	if (cHttpRespVO.dwError || cHttpRespVO.dwStatusCode == 407)
	{
		dprintf("error link is \'%s\' , returned error is \'%d\'",m_szProxyDetectUrl, cHttpRespVO.dwError);
		m_bIsProxyDetectSucc = false;
	}
	else
		m_bIsProxyDetectSucc = true;

	return m_bIsProxyDetectSucc;
}

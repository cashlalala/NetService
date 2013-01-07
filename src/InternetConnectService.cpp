#include "stdafx.h"
#include "InternetConnectService.h"
#include "UrlHelper.h"
#include "NetServiceErr.h"
#include "LoggerMgr.h"

#include <algorithm>
#include <ctype.h>
#include <typeinfo>

//util::ILogger* CInternetConnectService::S_LOGGER = util::CLoggerMgr::GetLogger(util::Log4Cxx,typeid(CInternetConnectService).name());

CInternetConnectService::CInternetConnectService(void)
: m_bIsProxyDetectSucc(false),
m_cNetKernelLoader()
{
	m_szServerAddr = "";
	m_szApName = "";
	m_szProxyDetectUrl = "";
	S_LOGGER = util::CLoggerMgr::GetLogger(util::Log4Cxx,typeid(CInternetConnectService).name());
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

	INetKernel* pINetKernel  = m_cNetKernelLoader.GetInstance();

	HttpRespValObj cHttpRespVO;
	pINetKernel->OpenUrl(cHttpRespVO,m_szProxyDetectUrl.c_str());

	if (cHttpRespVO.dwError || cHttpRespVO.dwStatusCode == 407)
	{
		//dprintf("error link is \'%s\' , returned error is \'%d\'",m_szProxyDetectUrl, cHttpRespVO.dwError);
		m_bIsProxyDetectSucc = false;
	}
	else
		m_bIsProxyDetectSucc = true;

	m_cNetKernelLoader.DelInstance(pINetKernel);

	return m_bIsProxyDetectSucc;
}

int CInternetConnectService::OpenUrl( HttpRespValObj& cHttpRespVO, string szUrl, string szHttpMethod /*= HTTP_METHOD_GET*/, wstring wszCookieFilePath /*= L""*/, void* pfnCallBack /*= NULL*/ )
{
	S_LOGGER->Debug("Input URL: [ " + szUrl +" ]");

	int nResult = E_FAIL;
	INetKernel* pINetKernel = m_cNetKernelLoader.GetInstance();
	m_listINetKernel.push_back(pINetKernel);

	// reserved
	//if (pfnCallBack)
	//	pINetKernel->SetCallBack(pfnCallBack);

	string szExt;
	szExt.resize(szUrl.size());
	std::transform(szUrl.rbegin(),szUrl.rbegin()+4,szExt.begin(),tolower);
	if (szExt.compare(0,4,"gpj.")==0)
		pINetKernel->SetDownloadCache(TRUE);

	//HttpResponseValueObject cHttpRespVO;
	string szEncodedUrl = util::CUrlHelper::EncodeUrl(szUrl);
	pINetKernel->OpenUrl(cHttpRespVO,szEncodedUrl.c_str(),szHttpMethod.c_str(), 
										NULL,NULL,wszCookieFilePath.c_str());

	list<INetKernel*>::iterator it = std::find(m_listINetKernel.begin(),m_listINetKernel.end(),pINetKernel);
	if (it != m_listINetKernel.end())
	{
		m_cNetKernelLoader.DelInstance(pINetKernel);
	}

	if (cHttpRespVO.dwError!=0)
	{
		nResult = NS_E_INET_CONNECT_FAIL_API_RETURN_ERROR;
		char* lpsz = (char*) calloc(100,sizeof(char));
		sprintf_s(lpsz,99,"Error Code[%d] : NS_E_INET_CONNECT_FAIL_API_RETURN_ERROR",nResult);
		S_LOGGER->Error(lpsz);
		free(lpsz);
		lpsz = NULL;
	}
	//else if (cHttpRespVO.dwStatusCode!=200)
	//{
	//	nResult = NS_E_INET_CONNECT_FAIL_HTTP_STATUS_ERROR;
	//}
	else
	{
		S_LOGGER->Debug("Response: [ " + cHttpRespVO.szResp +" ]");
		nResult = S_OK;
	}

	return nResult;
}

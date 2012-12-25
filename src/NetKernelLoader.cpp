#include "StdAfx.h"
#include <Shlwapi.h>
#include <tchar.h>
#include "NetKernelLoader.h"
#include "..\..\Utility\Debug.h"

NetKernelLoader::NetKernelLoader(void)
{
	LoadDll();
}


NetKernelLoader::~NetKernelLoader(void)
{
	FreeLibrary(m_hNetKernel);
	m_hNetKernel = NULL;
}


BOOL NetKernelLoader::LoadDll( void )
{
	TCHAR szExePath[_MAX_PATH];
	GetModuleFileName(NULL, szExePath, _MAX_PATH);
	PathRemoveFileSpec(szExePath);
	PathAddBackslash(szExePath);
	_tcscat_s(szExePath, TEXT("NetKernel.dll"));
	m_hNetKernel = LoadLibrary(szExePath);

	if (!m_hNetKernel)
	{
		dprintf(L"[PyOnlineMgr] LoadDLL(): The OnlineMgr DLL object load failed! Error code: %d", GetLastError());
		return FALSE;
	}

	return TRUE;
}


INetKernel* NetKernelLoader::GetInstance( void )
{
	//PFNGETINSTANCE pFn = (PFNGETINSTANCE) GetProcAddress(m_hNetKernel,"_GetNetKernelInstance@0");
	INetKernel::PFNGETINSTANCE pFn = (INetKernel::PFNGETINSTANCE) GetProcAddress(m_hNetKernel,"GetInstance");
	return pFn();
}


void NetKernelLoader::DelInstance( INetKernel* pInst )
{
	INetKernel::PFNDELINSTANCE pFn = (INetKernel::PFNDELINSTANCE) GetProcAddress(m_hNetKernel,"DeleteInstance");
	pFn(pInst);
}

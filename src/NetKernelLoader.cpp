#include "stdafx.h"
#include <Shlwapi.h>
#include <tchar.h>
#include "NetKernelLoader.h"
//#include "..\..\Utility\Debug.h"

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
	//TCHAR szExePath[_MAX_PATH];
	//GetModuleFileName(NULL, szExePath, _MAX_PATH);
	//PathRemoveFileSpec(szExePath);
	//PathAddBackslash(szExePath);
	//_tcscat_s(szExePath, TEXT("NetKernel.dll"));
	//m_hNetKernel = LoadLibrary(szExePath);
	m_hNetKernel = LoadLibrary(TEXT("NetKernel.dll"));

	LPVOID lpMsgBuf;
	if (!m_hNetKernel)
	{
		DWORD  dwErr = GetLastError();
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwErr, 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL);
		//dprintf(L"[PyOnlineMgr] LoadDLL(): The OnlineMgr DLL object load failed! Error code: [%d], Msg:[%s]", dwErr, (LPTSTR)&lpMsgBuf);
		LocalFree( lpMsgBuf );		
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

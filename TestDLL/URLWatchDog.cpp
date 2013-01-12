#include "stdafx.h"
#include "URLWatchDog.h"
#include <process.h>
#include <iostream>

std::string g_szToken;

HANDLE g_hThread = NULL;

bool g_bFkrAuthFlow1stStep = false;

int nCountDown = DEFAULT_COUNT_DOWN;

unsigned int __stdcall Monitoring(void * pParm = NULL);

void BeginMonitorUrlThread(ThreadParams& params)
{
	g_szToken.clear();
	g_bFkrAuthFlow1stStep = false;
	g_hThread = (HANDLE) _beginthreadex(NULL,0,Monitoring,(void*)&params,0,NULL);
}

/*
* This watch dog is just a workaround for unit tests for the purpose of fully automatically testing with chrome.
* You should figure out how to get the redirected url parameters and pass to net service by yourself.
*/
unsigned int __stdcall Monitoring(void * pParm)
{
	while(true)
	{
		if (nCountDown==0) return 1;
		HWND hDeskTop = GetDesktopWindow();
		HWND hWndChrome = FindWindowExA(hDeskTop, 0, "Chrome_WidgetWin_1", NULL);
		HWND hWndWeb = FindWindowExA(hDeskTop, hWndChrome, "Chrome_WidgetWin_1", NULL);
		HWND hWndUrl = FindWindowExA(hWndWeb, 0, "Chrome_OmniboxView",NULL);
		if (hWndUrl)
		{
			ThreadParams* pParams = (ThreadParams*) pParm;
			char lpszText[1000];
			memset(lpszText,0x0,1000);
			SendMessageA(hWndUrl,WM_GETTEXT,999,(long)lpszText);
			switch (pParams->enService)
			{
			case testutil::FB:
				{
					char* lpszBegin = strstr(lpszText,"#access_token=");
					if (lpszBegin)
					{
						char* lpszTokenBegin = lpszBegin + strlen("#access_token=");
						char* lpszEnd = strstr(lpszText,"&expires_in=");
						char szToken[300];
						memset(szToken,0x0,300);
						strncpy_s(szToken,299,lpszTokenBegin,lpszEnd-lpszTokenBegin);
						g_szToken = szToken;
						return 0;
					}
				}
				break;
			case testutil::Fkr:
				{
					if (!g_bFkrAuthFlow1stStep &&
						strcmp(pParams->szLoginUrl.c_str(),lpszText)==0)
						g_bFkrAuthFlow1stStep = true;
					if (g_bFkrAuthFlow1stStep && 
						strcmp(pParams->szLoginUrl.c_str(),"http://www.flickr.com/services/auth/")==0)
						return 0;
				}
				break;
			default:
				break;
			}
		}
		Sleep(500);
	}
}

void WaitForAuthorization()
{
	std::cout << "Please authorize the app as soon as possible in " << nCountDown 
		<< " seconds!!!" << std::endl;
	while(WAIT_TIMEOUT == WaitForSingleObject(g_hThread,1000))
	{
		std::cout << "Counting Down ... " << nCountDown-- << std::endl;
	}
	nCountDown = DEFAULT_COUNT_DOWN;
	CloseHandle(g_hThread);
}

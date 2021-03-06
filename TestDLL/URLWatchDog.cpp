#include "stdafx.h"
#include "URLWatchDog.h"
#include <process.h>
#include <iostream>

std::string g_szToken;

HANDLE g_hThread = NULL;

bool g_bFkrAuthFlow1stStep = false;

bool g_bIsAuthFlowDone = false;

const int nDefaultCountDown = GetPrivateProfileIntA("URLWatchDog","SecondsForWaitingAuth",0,"..\\TestData\\TestConfig.ini");

int nCountDown = nDefaultCountDown;

unsigned int __stdcall Monitoring(void * pParm = NULL);

void BeginMonitorUrlThread(ThreadParams& params)
{
	g_szToken.clear();
	g_bFkrAuthFlow1stStep = false;
	g_bIsAuthFlowDone = false;
	g_hThread = (HANDLE) _beginthreadex(NULL,0,Monitoring,(void*)&params,0,NULL);
}

/*
* This watch dog is just a workaround for unit tests for the purpose of fully automatically testing with chrome.
* You should figure out how to get the redirected url parameters and pass to net service by yourself.
*/
unsigned int __stdcall Monitoring(void * pParm)
{
	ThreadParams* pParams = (ThreadParams*) pParm;
	HWND hWndUrl = NULL;
	while(true)
	{
		if (nCountDown==0) return 1;
		
		int nDefault = 0;
		nDefault = GetPrivateProfileIntA("URLWatchDog","DefaultBrowser",nDefault,"..\\TestData\\TestConfig.ini");

		if (nDefault == 1)//(pParams->szBrowser=="chrome") 
		{
			HWND hDeskTop = GetDesktopWindow();
			HWND hWndChrome = FindWindowExA(hDeskTop, 0, "Chrome_WidgetWin_1", NULL);
			hWndUrl = FindWindowExA(hWndChrome, 0, "Chrome_OmniboxView",NULL);
			if (!hWndUrl) // support nested chrome ... for 2 layer...
			{
				HWND hWndWeb = FindWindowExA(hDeskTop, hWndChrome, "Chrome_WidgetWin_1", NULL);
				hWndUrl = FindWindowExA(hWndWeb, 0, "Chrome_OmniboxView",NULL);
			}
		}
		else if (nDefault == 2) //(pParams->szBrowser=="IE")
		{
			HWND hDeskTop = GetDesktopWindow();
			HWND hIE = FindWindowExA(hDeskTop, 0, "IEFrame", NULL);
			HWND hWorker = FindWindowExA(hIE, 0, "WorkerW", NULL);
			HWND hReBar = FindWindowExA(hWorker, 0, "ReBarWindow32", NULL);
			HWND hAddressBand = FindWindowExA(hReBar, 0, "Address Band Root", NULL);
			hWndUrl = FindWindowExA(hAddressBand, 0, "Edit",NULL);
		}
		else  //get from config
		{
			return 0;
		}

		if (hWndUrl)
		{	
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
						g_bIsAuthFlowDone = true;
						return 0;
					}
				}
				break;
			case testutil::Fkr:
				{
					std::string szUrl = "http://" + std::string(lpszText);
					if (!g_bFkrAuthFlow1stStep &&
						pParams->szLoginUrl == szUrl)
						g_bFkrAuthFlow1stStep = true;
					if (g_bFkrAuthFlow1stStep && 
						szUrl == "http://www.flickr.com/services/auth/")
					{
						g_bIsAuthFlowDone = true;
						return 0;
					}
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
	nCountDown = nDefaultCountDown;
	CloseHandle(g_hThread);
}

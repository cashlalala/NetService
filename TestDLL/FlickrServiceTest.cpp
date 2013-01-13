#include "StdAfx.h"
#include "FlickrServiceTest.h"
#include "URLWatchDog.h"

#include <SysTypes.h>
#include <FkRErrorModel.h>
#include <FkRPhotoModel.h>
#include <FlickrFields.h>
#include <iostream>

using namespace systypes;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( CFlickrServiceTest );


CFlickrServiceTest::CFlickrServiceTest(void)
{
	pSocialService = NULL;
}


CFlickrServiceTest::~CFlickrServiceTest(void)
{
}

void CFlickrServiceTest::setUp()
{
	ISocialNetworkService::PFNGETINSTANCE pfn = (ISocialNetworkService::PFNGETINSTANCE) GetProcAddress(g_hNerServ,"GetInstance");
	pSocialService = pfn(FLICKR);


		char lpszTmp[1025];
		memset(lpszTmp,0x0,1025);
		GetPrivateProfileStringA("FlickRService","api_key",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
		cCnctInfoVO.lpcszApiKey = string(lpszTmp);
		cout << "Get APP id: " << cCnctInfoVO.lpcszApiKey << endl;

		memset(lpszTmp,0x0,1025);
		GetPrivateProfileStringA("FlickRService","shared_secret",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
		cCnctInfoVO.szAppSecret = string(lpszTmp);
		cout << "Get secret : " << cCnctInfoVO.szAppSecret << endl;

		if (!g_bIsAuthFlowDone)
			pSocialService->SetConnectionInfo(cCnctInfoVO);
}

void CFlickrServiceTest::tearDown()
{
	//ISocialNetworkService::PFNDELINSTANCE pfn = (ISocialNetworkService::PFNDELINSTANCE) GetProcAddress(g_hNerServ,"DelInstance");
	//pfn(pSocialService);
}

void CFlickrServiceTest::testFkrGetProfile()
{

}

void CFlickrServiceTest::testFkrGetAlbumList()
{

}

void CFlickrServiceTest::testFkrGetUser()
{

}

void CFlickrServiceTest::testFkrGetPhotos()
{
	model::CFkrPhotoList cFBPhotoList;
	model::CFkrError cFbErr;
	SysMaps::Str2Str mapQryParams;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "3";
	int nResult = pSocialService->GetPhotos(cFBPhotoList,cFbErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickrServiceTest::testGetFriends()
{

}

void CFlickrServiceTest::testFkrGetLoginUrl()
{
	string szLoginUrl ;
	model::CFkrError cFkErr;
	int nResult = pSocialService->GetLoginURL(szLoginUrl, cCnctInfoVO.lpcszApiKey, cCnctInfoVO.szAppSecret, cFkErr,"write");
	ShellExecuteA(NULL, "open", (szLoginUrl + "\r\n").c_str(), NULL, NULL, SW_SHOW);
	
	ThreadParams cThreadParams;
	cThreadParams.enService = testutil::Fkr;
	cThreadParams.szLoginUrl = szLoginUrl;
	BeginMonitorUrlThread(cThreadParams);
	WaitForAuthorization();

	CPPUNIT_ASSERT_MESSAGE(cFkErr.szMsg.c_str(),nResult==S_OK && g_bIsAuthFlowDone);
}

void CFlickrServiceTest::terminate()
{
	g_bIsAuthFlowDone = false;
}

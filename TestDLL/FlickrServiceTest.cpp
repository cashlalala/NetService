#include "StdAfx.h"
#include "FlickrServiceTest.h"
#include <SysTypes.h>
#include <FkRErrorModel.h>
#include <FkRPhotoModel.h>
#include <FlickrFields.h>
#include <iostream>

using namespace systypes;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( CFlickrServiceTest );

static bool bIsConfiged= false;

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
	CFlickrConnectionInfo cCnctInfoVO;

	if (!bIsConfiged)
	{

	char lpszTmp[1025];
	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FlickRService","api_key",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	cCnctInfoVO.lpcszApiKey = string(lpszTmp);
	cout << "Get APP id: " << cCnctInfoVO.lpcszApiKey << endl;

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FlickRService","shared_secret",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	cCnctInfoVO.szAppSecret = string(lpszTmp);
	cout << "Get secret : " << cCnctInfoVO.szAppSecret << endl;

	pSocialService->SetConnectionInfo(cCnctInfoVO);

	string szLoginUrl ;
	model::CFkRError cFkErr;
	int nResult = pSocialService->GetLoginURL(szLoginUrl, cCnctInfoVO.lpcszApiKey, cFkErr,"write");
	ShellExecuteA(NULL, "open", szLoginUrl.c_str(), NULL, NULL, SW_SHOW);
	MessageBoxA(NULL,"Please authorize the login request in your web browse.\n\nAfter authorizing it, click OK to continue.","Authorize Login Request", MB_OK);
	bIsConfiged = true;
	}
}

void CFlickrServiceTest::tearDown()
{
	ISocialNetworkService::PFNDELINSTANCE pfn = (ISocialNetworkService::PFNDELINSTANCE) GetProcAddress(g_hNerServ,"DelInstance");
	pfn(pSocialService);
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
	model::CFkRPhotoList cFBPhotoList;
	model::CFkRError cFbErr;
	SysMaps::Str2Str mapQryParams;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "3";
	int nResult = pSocialService->GetPhotos(cFBPhotoList,cFbErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickrServiceTest::testGetFriends()
{

}

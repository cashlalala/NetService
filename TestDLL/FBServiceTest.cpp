#include "StdAfx.h"
#include "FBServiceTest.h"
#include "URLWatchDog.h"

#include <IConnectionInfo.h>
#include <FBUserModel.h>
#include <FBErrorModel.h>
#include <FBAlbumModel.h>
#include <FBPhotoModel.h>
#include <FBFields.h>
#include <SysTypes.h>

#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( CFBServiceTest );

CFBServiceTest::CFBServiceTest(void)
{
	pSocialService = NULL;
}

CFBServiceTest::~CFBServiceTest(void)
{
}

void CFBServiceTest::testGetFriends()
{
	model::CFBUserList cFbUsrLst;
	model::CFBError cFbErr;
	SysMaps::Str2Str mapMy;

	char lpszTmp[20];
	memset(lpszTmp,0x0,20);
	sprintf(lpszTmp,"%s,%s",FB_USER_PICTURE,FB_USER_NAME);

	mapMy[FB_FIELDS]= lpszTmp;
	int nResult = pSocialService->GetFriends(cFbUsrLst,cFbErr,"me",mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFBServiceTest::testFBGetPhotos()
{
	model::CFBPhotoList cFBPhotoList;
	model::CFBError cFbErr;
	int nResult = pSocialService->GetPhotos(cFBPhotoList,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}


void CFBServiceTest::testFBGetUser()
{
	model::CFBUser cFbUsr;
	model::CFBError cFbErr;

	int nResult = pSocialService->GetUserInfo(cFbUsr,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFBServiceTest::testFBGetProfile()
{
	model::CFBProfile cFbProfile;
	model::CFBError cFbErr;

	int nResult = pSocialService->GetProfile(cFbProfile,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFBServiceTest::testFBGetAlbumList()
{
	model::CFBAlbumList cFbAlbumList;
	model::CFBError cFbErr;

	int nResult = pSocialService->GetAlbums(cFbAlbumList,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFBServiceTest::setUp()
{
	ISocialNetworkService::PFNGETINSTANCE pfn = (ISocialNetworkService::PFNGETINSTANCE) GetProcAddress(g_hNerServ,"GetInstance");
	pSocialService = pfn(FACEBOOK);
}

void CFBServiceTest::tearDown()
{
	//ISocialNetworkService::PFNDELINSTANCE pfn = (ISocialNetworkService::PFNDELINSTANCE) GetProcAddress(g_hNerServ,"DelInstance");
	//pfn(pSocialService);
}


/*
* This must be the first function to test, because it get the auth token for the consequent tests
*/
void CFBServiceTest::testFBGetLoginURL()
{

	char lpszTmp[1025];

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","api_key",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.lpcszApiKey = string(lpszTmp);

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","app_secret",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.szAppSecret = string(lpszTmp);

	string szLoginUrl ;
	model::CFBError cFbErr;
	int nResult = pSocialService->GetLoginURL(szLoginUrl, m_cCnctInfoVO.lpcszApiKey, m_cCnctInfoVO.szAppSecret, cFbErr,"user_photos");
	ShellExecuteA(NULL, "open", (szLoginUrl + "\r\n").c_str(), NULL, NULL, SW_SHOW);

	/*
	* This watch dog is just a workaround for unit tests for the purpose of fully automatically testing with chrome.
	* You should figure out how to get the redirected url parameters and pass to net service by yourself.
	*/
	ThreadParams cThreadParam;
	cThreadParam.enService =  testutil::FB;
	BeginMonitorUrlThread(cThreadParam);

	WaitForAuthorization();

	m_cCnctInfoVO.szAccessToken = g_szToken;
	//for a single instance, you just need to set connection info only once
	pSocialService->SetConnectionInfo(m_cCnctInfoVO);

	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK && !g_szToken.empty() && g_bIsAuthFlowDone);
}

void CFBServiceTest::terminate()
{
	g_bIsAuthFlowDone = false;
	g_szToken = "";
}

CFBConnectionInfo CFBServiceTest::m_cCnctInfoVO;

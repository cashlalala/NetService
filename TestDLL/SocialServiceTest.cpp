#include "StdAfx.h"
#include "SocialServiceTest.h"

#include <IConnectionInfo.h>
#include <FBUserModel.h>
#include <FBErrorModel.h>
#include <FBAlbumModel.h>
#include <FBPhotoModel.h>
#include <FBFields.h>
#include <SysTypes.h>

#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( CSocialServiceTest );

CSocialServiceTest::CSocialServiceTest(void)
{
	pSocialService = NULL;
}

CSocialServiceTest::~CSocialServiceTest(void)
{
}

void CSocialServiceTest::testGetFriends()
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

void CSocialServiceTest::testFBGetPhotos()
{
	model::CFBPhotoList cFBPhotoList;
	model::CFBError cFbErr;
	int nResult = pSocialService->GetPhotos(cFBPhotoList,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}


void CSocialServiceTest::testFBGetUser()
{
	model::CFBUser cFbUsr;
	model::CFBError cFbErr;

	int nResult = pSocialService->GetUserInfo(cFbUsr,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CSocialServiceTest::testFBGetProfile()
{
	model::CFBProfile cFbProfile;
	model::CFBError cFbErr;

	int nResult = pSocialService->GetProfile(cFbProfile,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CSocialServiceTest::testFBGetAlbumList()
{
	model::CFBAlbumList cFbAlbumList;
	model::CFBError cFbErr;

	int nResult = pSocialService->GetAlbums(cFbAlbumList,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CSocialServiceTest::setUp()
{
	ISocialNetworkService::PFNGETINSTANCE pfn = (ISocialNetworkService::PFNGETINSTANCE) GetProcAddress(g_hNerServ,"GetInstance");
	pSocialService = pfn(FACEBOOK);
	CFBConnectionInfo cCnctInfoVO;

	char lpszTmp[1025];
	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","access_token",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	cCnctInfoVO.szAccessToken = string(lpszTmp);
	cout << "Get Access Token: " << cCnctInfoVO.szAccessToken << endl;

	pSocialService->SetConnectionInfo(cCnctInfoVO);
}

void CSocialServiceTest::tearDown()
{
	ISocialNetworkService::PFNDELINSTANCE pfn = (ISocialNetworkService::PFNDELINSTANCE) GetProcAddress(g_hNerServ,"DelInstance");
	pfn(pSocialService);
}

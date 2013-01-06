#include "StdAfx.h"
#include "SocialServiceTest.h"

#include <IConnectionInfo.h>
#include <FBUserModel.h>
#include <FBErrorModel.h>

CPPUNIT_TEST_SUITE_REGISTRATION( CSocialServiceTest );

CSocialServiceTest::CSocialServiceTest(void)
{
	pSocialService = NULL;
}

CSocialServiceTest::~CSocialServiceTest(void)
{
}

void CSocialServiceTest::testFBGetProfile()
{
	model::CFBProfile cFbProfile;
	model::CFBError cFbErr;

	int nResult = pSocialService->GetProfile(cFbProfile,cFbErr);
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

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","uid",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	cCnctInfoVO.szUid = string(lpszTmp);

	pSocialService->SetConnectionInfo(cCnctInfoVO);
}

void CSocialServiceTest::tearDown()
{
	delete pSocialService;
}

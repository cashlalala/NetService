#include "FlickRServiceTest.h"
#include <FkRErrorModel.h>
#include <FkRPhotoModel.h>
#include <NetServiceErr.h>
#include <WinBase.h>
#include <WinUser.h>
#include <SysTypes.h>
#include <FlickrFields.h>
#include "shellapi.h"

using namespace systypes;
static CFlickrConnectionInfo m_cCnctInfoVO;
static bool bIsConfiged = false;

CPPUNIT_TEST_SUITE_REGISTRATION( CFlickRServiceTest );

CFlickRServiceTest::CFlickRServiceTest(void)
{
}

CFlickRServiceTest::~CFlickRServiceTest(void)
{
}

void CFlickRServiceTest::setUp()
{
	m_pFlickrService = new CFlickrService();
	//CFlickrConnectionInfo cCnctInfoVO;
	if (!bIsConfiged)
	{
		char* lpszTmp = new char[1025];

		memset(lpszTmp,0x0,1025);
		GetPrivateProfileStringA("FlickRService","api_key",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
		m_cCnctInfoVO.lpcszApiKey = string(lpszTmp);

		memset(lpszTmp,0x0,1025);
		GetPrivateProfileStringA("FlickRService","shared_secret",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
		m_cCnctInfoVO.szAppSecret = string(lpszTmp);

		delete[] lpszTmp;

		m_pFlickrService->SetConnectionInfo(m_cCnctInfoVO);

		CFkrError cFkrErr;
		string szLoginUrl ;
		int nResult	= m_pFlickrService->GetLoginURL(szLoginUrl ,m_cCnctInfoVO.lpcszApiKey,cFkrErr,"write");
		ShellExecuteA(NULL, "open", szLoginUrl.c_str(), NULL, NULL, SW_SHOW);
		MessageBoxA(NULL,"Please authorize the login request in your web browse.\n\nAfter authorizing it, click OK to continue.","Authorize Login Request", MB_OK);
		bIsConfiged = true;
	}
}

void CFlickRServiceTest::tearDown()
{
		delete m_pFlickrService;
}

void CFlickRServiceTest::testGetPhotos()
{
	model::CFkrPhotoList cFBPhotoList;
	model::CFkrError cFbErr;
	SysMaps::Str2Str mapQryParams;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "3";
	int nResult = m_pFlickrService->GetPhotos(cFBPhotoList,cFbErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}
//
//void CFlickRServiceTest::testGetForb()
//{
//	model::CFkrError cFkrErr;
//	string szFrob;
//	m_pFlickrService->SetConnectionInfo(m_cCnctInfoVO);
//	int nResult = m_pFlickrService->GetFlickrAuthFrob(szFrob,cFkrErr);
//	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg,nResult==S_OK);
//}
//
//void CFlickRServiceTest::testGetToken()
//{
//	model::CFkrError cFkrErr;
//	string szRqstToken;
//	string szUrl;
//	m_pFlickrService->SetConnectionInfo(m_cCnctInfoVO);
//	int nResult = m_pFlickrService->GetFlickrAuthToken(m_cCnctInfoVO.szAuthToken, cFkrErr);
//	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg,nResult==S_OK);
//}

void CFlickRServiceTest::testGetOAuthRqstToken()
{
	model::CFkrError cFkrErr;
	string szRqstToken;
	string szRqstTokenSecret;
	int nResult = m_pFlickrService->GetOAuthRqstToken(szRqstToken,szRqstTokenSecret,cFkrErr);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg,nResult==S_OK);
}

#include "FlickRServiceTest.h"
#include <FkRErrorModel.h>
#include <FkRPhotoModel.h>
#include <NetServiceErr.h>
#include <WinBase.h>
#include <WinUser.h>
#include "shellapi.h"

static string g_szAuthTokenBuf ;

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
	char* lpszTmp = new char[1025];

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FlickRService","api_key",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.lpcszApiKey = string(lpszTmp);

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FlickRService","shared_secret",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.szAppSecret = string(lpszTmp);

	delete[] lpszTmp;

	m_pFlickrService->SetConnectionInfo(m_cCnctInfoVO);
}

void CFlickRServiceTest::tearDown()
{
		delete m_pFlickrService;
}

void CFlickRServiceTest::testGetPhotos()
{
	model::CFkRPhotoList cFBPhotoList;
	model::CFkRError cFbErr;
	m_cCnctInfoVO.szAuthToken = g_szAuthTokenBuf;
	m_pFlickrService->SetConnectionInfo(m_cCnctInfoVO);
	int nResult = m_pFlickrService->GetPhotos(cFBPhotoList,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}
//
void CFlickRServiceTest::testGetForb()
{
	model::CFkRError cFkrErr;
	string szFrob;
	int nResult = m_pFlickrService->GetFrob(szFrob,cFkrErr);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg,nResult==S_OK);
}

void CFlickRServiceTest::testGetToken()
{
	model::CFkRError cFkrErr;
	string szRqstToken;
	string szUrl;
	szUrl = m_pFlickrService->GetLoginURL(m_cCnctInfoVO.lpcszApiKey,"write");
	ShellExecuteA(NULL, "open", szUrl.c_str(), NULL, NULL, SW_SHOW);
	MessageBoxA(NULL,"Please authorize the login request in your web browse.\n\nAfter authorizing it, click OK to continue.","Authorize Login Request", MB_OK);
	int nResult = m_pFlickrService->GetFlickRAuthToken(m_cCnctInfoVO.szAuthToken, cFkrErr);

	g_szAuthTokenBuf = m_cCnctInfoVO.szAuthToken;

	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg,nResult==S_OK);
}

void CFlickRServiceTest::testGetOAuthRqstToken()
{
	model::CFkRError cFkrErr;
	string szRqstToken;
	string szRqstTokenSecret;
	int nResult = m_pFlickrService->GetOAuthRqstToken(szRqstToken,szRqstTokenSecret,cFkrErr);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg,nResult==S_OK);
}

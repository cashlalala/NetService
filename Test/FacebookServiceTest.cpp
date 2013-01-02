#include "FacebookServiceTest.h"
#include <UrlHelper.h>
#include <NetServiceErr.h>
#include <iostream>
#include <string>
#include <list>
#include <WinBase.h>
#include <FacebookPhotoModel.h>
#include <FBUserModel.h>

using std::string;
using std::list;
using std::cout;
using std::endl;

CPPUNIT_TEST_SUITE_REGISTRATION( CFacebookServiceTest );

CFacebookServiceTest::CFacebookServiceTest(void)
{
	m_pFacebookService= NULL;
}

CFacebookServiceTest::~CFacebookServiceTest(void)
{
}

void CFacebookServiceTest::setUp()
{
	m_pFacebookService = new CFacebookService();
	CFBConnectionInfo cCnctInfoVO;
	char* lpszTmp = new char[1025];
	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","access_token",NULL,lpszTmp,1024,"TestData\\TestConfig.ini");
	cCnctInfoVO.szAccessToken = string(lpszTmp);

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","uid",NULL,lpszTmp,1024,"TestData\\TestConfig.ini");
	cCnctInfoVO.szUid = string(lpszTmp);

	delete[] lpszTmp;

	m_pFacebookService->SetConnectionInfo(cCnctInfoVO);
}

void CFacebookServiceTest::tearDown()
{
	delete m_pFacebookService;
}

void CFacebookServiceTest::testCallGraphApi()
{
	//std::string reslut = m_pFacebookService->CallGraphAPI();
	//std::cout << reslut << std::endl;
	//CPPUNIT_ASSERT(!reslut.empty());
}

void CFacebookServiceTest::testGetLoginUrl()
{
	string szLoginUrl = m_pFacebookService->GetLoginURL("215921841875602","read_stream ");
	string szExpectLoginUrl = "https://www.facebook.com/dialog/oauth?client_id=215921841875602&redirect_uri=http://www.facebook.com/connect/login_success.html&response_type=token&display=popup&scope=read_stream%20";
	string szRes = CUrlHelper::EncodeUrl(szExpectLoginUrl);
	cout << endl << szLoginUrl << endl;
	cout << endl << szRes << endl;
	CPPUNIT_ASSERT(szExpectLoginUrl==szRes);
}

void CFacebookServiceTest::testGetUserInfo()
{
	CFBUserList temp;
	list<string> listUsr;
	listUsr.push_back("me");
	listUsr.push_back("726727685");
	listUsr.push_back("508872928");
	
	CFBError cfbErr ;
	int nResult = m_pFacebookService->GetUsersInfo(temp,cfbErr,listUsr);
	CPPUNIT_ASSERT_MESSAGE(cfbErr.szMsg.c_str(),nResult==S_OK);
}

void CFacebookServiceTest::testGetPhotos()
{
	
	model::CFacebookPhotoList cFBPhotoList;
	CFBError cFbErr;
	int nResult = m_pFacebookService->GetPhotos(cFBPhotoList,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

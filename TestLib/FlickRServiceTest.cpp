#include "FlickRServiceTest.h"
#include <FkRErrorModel.h>
#include <FkRPhotoModel.h>
#include <FkrAlbumModel.h>
#include <FkrUserModel.h>
#include <NetServiceErr.h>
#include <WinBase.h>
#include <WinUser.h>
#include <SysTypes.h>
#include <FlickrFields.h>
#include "..\TestDLL\URLWatchDog.h"
#include "shellapi.h"
#include <iostream>

using namespace std;
using namespace systypes;

CPPUNIT_TEST_SUITE_REGISTRATION( CFlickRServiceTest );

CFlickRServiceTest::CFlickRServiceTest(void)
{
	m_pFlickrService = NULL;
}

CFlickRServiceTest::~CFlickRServiceTest(void)
{
}

void CFlickRServiceTest::setUp()
{
	m_pFlickrService = new CFlickrService();

	m_pFlickrService->SetConnectionInfo(m_cCnctInfoVO);
}

void CFlickRServiceTest::tearDown()
{
	//If you call the "GetLoginURL" from dll interface, there is no need to write the following two lines.
	//The only one thing you need to do is set the connection info which contains app id and secret to the service
	CFlickrConnectionInfo* pIConInfo = dynamic_cast<CFlickrConnectionInfo*>(m_pFlickrService->GetConnectionInfo());
	m_cCnctInfoVO = *pIConInfo;
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

void CFlickRServiceTest::terminate()
{
	g_bIsAuthFlowDone = false;
	g_szToken = "";
}

void CFlickRServiceTest::tetGetLoginUrl()
{

	char lpszTmp[1025];
	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FlickRService","api_key",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.lpcszApiKey = string(lpszTmp);
	cout << "Get APP id: " << m_cCnctInfoVO.lpcszApiKey << endl;

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FlickRService","shared_secret",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.szAppSecret = string(lpszTmp);
	cout << "Get secret : " << m_cCnctInfoVO.szAppSecret << endl;

	string szLoginUrl ;
	model::CFkrError cFkErr;
	int nResult = m_pFlickrService->GetLoginURL(szLoginUrl, m_cCnctInfoVO.lpcszApiKey, m_cCnctInfoVO.szAppSecret, cFkErr,"write");

	ShellExecuteA(NULL, "open", (szLoginUrl + "\r\n").c_str(), NULL, NULL, SW_SHOW);
	ThreadParams cThreadParams;
	cThreadParams.enService = testutil::Fkr;
	cThreadParams.szLoginUrl = szLoginUrl;
	BeginMonitorUrlThread(cThreadParams);
	WaitForAuthorization();

	//If you call the "GetLoginURL" from dll interface, there is no need to write the following two lines.
	//The only one thing you need to do is set the connection info which contains app id and secret to the service
	CFlickrConnectionInfo* pIConInfo = dynamic_cast<CFlickrConnectionInfo*>(m_pFlickrService->GetConnectionInfo());
	m_cCnctInfoVO.szFrob = pIConInfo->szFrob;
	m_pFlickrService->SetConnectionInfo(m_cCnctInfoVO);

	CPPUNIT_ASSERT_MESSAGE(cFkErr.szMsg.c_str(),nResult==S_OK && g_bIsAuthFlowDone);
}

void CFlickRServiceTest::testGetAlbums()
{
	model::CFkrAlbumList cFkrAlbumList;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "2";
	int nResult = m_pFlickrService->GetAlbums(cFkrAlbumList,cFkrErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickRServiceTest::testGetFriends()
{
	model::CFkrUserList cFkrUsrList;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "2";
	int nResult = m_pFlickrService->GetFriends(cFkrUsrList,cFkrErr,"70735667@N03",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickRServiceTest::testGetUserInfo()
{
	model::CFkrUser cFkrUsr;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	int nResult = m_pFlickrService->GetUserInfo(cFkrUsr,cFkrErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickRServiceTest::testGetUsersInfo()
{
	model::CFkrUserList cFkrUsrLst;
	model::CFkrError cFkrErr;
	SysList::StrList listUid;
	listUid.push_back("92188701@N07");
	listUid.push_back("70735667@N03");
	listUid.push_back("91786782@N02");
	SysMaps::Str2Str mapQryParams;
	int nResult = m_pFlickrService->GetUsersInfo(cFkrUsrLst,cFkrErr,listUid,mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickRServiceTest::testGetProfile()
{
	model::CFkrProfile cFkrProfile;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	int nResult = m_pFlickrService->GetProfile(cFkrProfile,cFkrErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickRServiceTest::testGetFriendsPhotosInAlbumWithPhotosAndAlbumPaging()
{
	string szCertainFriend ="70735667@N03";

	model::CFkrUserList cFkrUsrList;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;	
	int nResult = m_pFlickrService->GetFriends(cFkrUsrList,cFkrErr);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);

	string szTargetFriendId;
	for (list<IUser*>::iterator it = cFkrUsrList.listOfItem.begin();it != cFkrUsrList.listOfItem.end(); ++it)
	{
		cout << (*it)->szId << endl;
		if ((*it)->szId == szCertainFriend)
		{
			szTargetFriendId = (*it)->szId;
			cout << "Gotten!! Break!" << endl;
			break;
		}
	}

	model::CFkrAlbumList cFkrAlbumList;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "2";
	nResult = m_pFlickrService->GetAlbums(cFkrAlbumList,cFkrErr,szTargetFriendId,mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK && cFkrAlbumList.listOfItem.size()==1);
	mapQryParams.clear();

	model::CFkrPhotoList cFBPhotoList;
	mapQryParams[FLICK_PARAM_PERPAGE] = "5";
	mapQryParams[FLICK_PARAM_PAGE] = "2";
	string szTargetAlbumId = cFkrAlbumList.listOfItem.front()->szId;
	nResult = m_pFlickrService->GetPhotos(cFBPhotoList,cFkrErr,szTargetAlbumId,mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK && cFBPhotoList.listOfItem.size()==5 
		&& !cFBPhotoList.szNextPageUrl.empty() && !cFBPhotoList.szPreviousPageUrl.empty());
	
}

CFlickrConnectionInfo CFlickRServiceTest::m_cCnctInfoVO;

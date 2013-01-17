#include "StdAfx.h"
#include "FlickrServiceTest.h"
#include "URLWatchDog.h"

#include <SysTypes.h>
#include <FkRErrorModel.h>
#include <FkRPhotoModel.h>
#include <FkrUserModel.h>
#include <FkrAlbumModel.h>
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
}

void CFlickrServiceTest::tearDown()
{
	//ISocialNetworkService::PFNDELINSTANCE pfn = (ISocialNetworkService::PFNDELINSTANCE) GetProcAddress(g_hNerServ,"DelInstance");
	//pfn(pSocialService);
}

void CFlickrServiceTest::testFkrGetProfile()
{
	model::CFkrProfile cFkrProfile;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	int nResult = pSocialService->GetProfile(cFkrProfile,cFkrErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickrServiceTest::testFkrGetAlbumList()
{
	model::CFkrAlbumList cFkrAlbumList;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "2";
	int nResult = pSocialService->GetAlbums(cFkrAlbumList,cFkrErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickrServiceTest::testFkrGetUser()
{
	model::CFkrUser cFkrUsr;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	int nResult = pSocialService->GetUserInfo(cFkrUsr,cFkrErr,"me",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
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
	model::CFkrUserList cFkrUsrList;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;
	mapQryParams[FLICK_PARAM_PERPAGE] = "1";
	mapQryParams[FLICK_PARAM_PAGE] = "2";
	int nResult = pSocialService->GetFriends(cFkrUsrList,cFkrErr,"70735667@N03",mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK);
}

void CFlickrServiceTest::testFkrGetLoginUrl()
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

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FlickRService","scope",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	string szScope = string(lpszTmp);
	cout << "Get scope : " << szScope << endl;

	string szLoginUrl ;
	model::CFkrError cFkErr;
	int nResult = pSocialService->GetLoginURL(szLoginUrl, m_cCnctInfoVO.lpcszApiKey, m_cCnctInfoVO.szAppSecret, cFkErr,szScope);
	ShellExecuteA(NULL, "open", (szLoginUrl + "\r\n").c_str(), NULL, NULL, SW_SHOW);
	
	ThreadParams cThreadParams;
	cThreadParams.enService = testutil::Fkr;
	cThreadParams.szLoginUrl = szLoginUrl;
	BeginMonitorUrlThread(cThreadParams);
	WaitForAuthorization();
	//for a single instance, you just need to set connection info only once
	pSocialService->SetConnectionInfo(m_cCnctInfoVO);

	CPPUNIT_ASSERT_MESSAGE(cFkErr.szMsg.c_str(),nResult==S_OK && g_bIsAuthFlowDone);
}

void CFlickrServiceTest::testGetFriendsPhotosInAlbumWithPhotosAndAlbumPaging()
{
	string szCertainFriend ="70735667@N03";

	model::CFkrUserList cFkrUsrList;
	model::CFkrError cFkrErr;
	SysMaps::Str2Str mapQryParams;	
	int nResult = pSocialService->GetFriends(cFkrUsrList,cFkrErr);
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
	nResult = pSocialService->GetAlbums(cFkrAlbumList,cFkrErr,szTargetFriendId,mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK && cFkrAlbumList.listOfItem.size()==1);
	mapQryParams.clear();

	model::CFkrPhotoList cFBPhotoList;
	mapQryParams[FLICK_PARAM_PERPAGE] = "5";
	mapQryParams[FLICK_PARAM_PAGE] = "2";
	string szTargetAlbumId = cFkrAlbumList.listOfItem.front()->szId;
	nResult = pSocialService->GetPhotos(cFBPhotoList,cFkrErr,szTargetAlbumId,mapQryParams);
	CPPUNIT_ASSERT_MESSAGE(cFkrErr.szMsg.c_str(),nResult==S_OK && cFBPhotoList.listOfItem.size()==5 
		&& !cFBPhotoList.szNextPageUrl.empty() && !cFBPhotoList.szPreviousPageUrl.empty());

}


void CFlickrServiceTest::terminate()
{
	g_bIsAuthFlowDone = false;
	g_szToken = "";
}

CFlickrConnectionInfo CFlickrServiceTest::m_cCnctInfoVO;

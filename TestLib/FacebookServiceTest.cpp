#include "FacebookServiceTest.h"
#include "..\TestDLL\URLWatchDog.h"
#include <Shellapi.h>
#include <UrlHelper.h>
#include <NetServiceErr.h>
#include <iostream>
#include <string>
#include <list>
#include <WinBase.h>
#include <FBPhotoModel.h>
#include <FBUserModel.h>
#include <FBErrorModel.h>
#include <FBVideoModel.h>
#include <FBAlbumModel.h>
#include <FBFields.h>

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

	m_pFacebookService->SetConnectionInfo(m_cCnctInfoVO);
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

	char lpszTmp[1025];

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","api_key",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.lpcszApiKey = string(lpszTmp);

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","app_secret",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_cCnctInfoVO.szAppSecret = string(lpszTmp);

	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("FBService","scope",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	string szScope = string(lpszTmp);

	string szLoginUrl ;
	CFBError cFkErr;
	int nResult = m_pFacebookService->GetLoginURL(szLoginUrl, m_cCnctInfoVO.lpcszApiKey, m_cCnctInfoVO.szAppSecret, cFkErr,szScope);
	
	ShellExecuteA(NULL, "open", (szLoginUrl +"\r\n").c_str(), NULL, NULL, SW_SHOW);
	ThreadParams cThreadParam;
	cThreadParam.enService =  testutil::FB;
	BeginMonitorUrlThread(cThreadParam);
	WaitForAuthorization();
	//This is a workaround for ut, you should figure out your way to get the access_token in url and set to connection info.
	//In the future, this will be done by netservice.
	m_cCnctInfoVO.szAccessToken = g_szToken;

	CPPUNIT_ASSERT(nResult==S_OK && !g_szToken.empty() && g_bIsAuthFlowDone);
}

void CFacebookServiceTest::testGetUserInfo()
{
	CFBUserList temp;
	list<string> listUsr;
	//listUsr.push_back("me");
	listUsr.push_back("726727685");
	listUsr.push_back("508872928");
	
	model::CFBError cfbErr ;
	int nResult = m_pFacebookService->GetUsersInfo(temp,cfbErr,listUsr);
	CPPUNIT_ASSERT_MESSAGE(cfbErr.szMsg.c_str(),nResult==S_OK);
}

std::wstring CFacebookServiceTest::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void CFacebookServiceTest::testGetPhotos()
{	
	model::CFBPhotoList cFBPhotoList;
	CFBError cFbErr;
	int nResult = m_pFacebookService->GetPhotos(cFBPhotoList,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFacebookServiceTest::testGetFriends()
{
	model::CFBUserList cFbUsrLst;
	CFBError cFbErr;
	SysMaps::Str2Str mapMy;

	char lpszTmp[20];
	memset(lpszTmp,0x0,20);
	sprintf(lpszTmp,"%s,%s",FB_USER_PICTURE,FB_USER_NAME);

	mapMy[FB_FIELDS]= lpszTmp;
	int nResult = m_pFacebookService->GetFriends(cFbUsrLst,cFbErr,"me",mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFacebookServiceTest::testGetVideos()
{
	model::CFBVideoList cFbVideoLst;
	CFBError cFbErr;
	SysMaps::Str2Str mapMy;
	int nResult = m_pFacebookService->GetVideos(cFbVideoLst,cFbErr,"me",mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFacebookServiceTest::testGetAlbums()
{
	model::CFBAlbumList cFbAlbumLst;
	CFBError cFbErr;

	int nResult = m_pFacebookService->GetAlbums(cFbAlbumLst,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}

void CFacebookServiceTest::testGetProfile()
{
	model::CFBProfile cFbVideoLst;
	CFBError cFbErr;

	int nResult = m_pFacebookService->GetProfile(cFbVideoLst,cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK);
}


void CFacebookServiceTest::testGetUserAndUsersInfoWithTumbNail()
{
	model::CFBUserList cFbUsrLst ;
	model::CFBError cFbErr;
	SysMaps::Str2Str mapMy;
	mapMy[FB_FIELDS] = FB_USER_PICTURE;
	list<string> listUsr;
	listUsr.push_back("726727685");
	listUsr.push_back("508872928");
	int nResult = m_pFacebookService->GetUsersInfo(cFbUsrLst,cFbErr,listUsr,mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),SUCCEEDED(nResult));

	bool bIsThumbNailExist = true;
	for (list<IUser*>::iterator it = cFbUsrLst.items.begin();it!=cFbUsrLst.items.end();++it)
	{
		if (!(*it)->pProfile || (*it)->pProfile->szThumNail.empty())
		{
			bIsThumbNailExist =false;
			break;
		}
	}

	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),
		nResult==S_OK && cFbUsrLst.items.size()==2 && bIsThumbNailExist);
}

void CFacebookServiceTest::testGetFriendsInfoWithThumbNailAndPaging()
{
	//your friends suppose to be greater than 12
	model::CFBUserList cFbUsrLst ;
	model::CFBError cFbErr;
	SysMaps::Str2Str mapMy;
	mapMy[FB_FIELDS] = FB_USER_PICTURE;
	mapMy[FB_LIMIT] = "10"; //10 users perpage;
	mapMy[FB_OFFSET] = "2"; // 3rd user
	int nResult = m_pFacebookService->GetFriends(cFbUsrLst,cFbErr,"me",mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),
		nResult==S_OK && cFbUsrLst.items.size()== 10 && !cFbUsrLst.szNextPageUrl.empty() && !cFbUsrLst.szPreviousPageUrl.empty());
}

void CFacebookServiceTest::testGetPhotosInAlbumWithPhotosAndAlbumPaging()
{
	model::CFBAlbumList cFbAlbumList;
	model::CFBError cFbErr;
	SysMaps::Str2Str mapMy;
	mapMy[FB_LIMIT] = "1"; //1 albums perpage;
	mapMy[FB_OFFSET] = "5"; //6th album;
	int nResult = m_pFacebookService->GetAlbums(cFbAlbumList,cFbErr,"me",mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK && cFbAlbumList.items.size()==1 && !cFbAlbumList.szNextPageUrl.empty() );
	//!cFbAlbumList.szPrevious.empty() is removed because of Cursor-based Pagination. 
	//The first time you queried the pagination the before & after index won't be generated by server

	model::IAlbum* pIAlbum  = cFbAlbumList.items.front();	
	model::CFBPhotoList cFbPhotoLst;
	mapMy.clear();
	mapMy[FB_LIMIT] = "3"; //3 photos perpage;
	mapMy[FB_OFFSET] = "2"; //start from 3rd phots;

	int nPerpage = atoi(mapMy[FB_LIMIT].c_str());
	int nOffset = atoi(mapMy[FB_OFFSET].c_str());

	nResult = m_pFacebookService->GetPhotos(cFbPhotoLst,cFbErr,pIAlbum->szId,mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK && cFbPhotoLst.items.size()==nPerpage && !cFbPhotoLst.szNextPageUrl.empty()); 
	//For this assertion, your photos in this album must be at least 5.
	//!cFbPhotoLst.szPrevious.empty() is removed because of Cursor-based Pagination. 
	//The first time you queried the pagination the "before" index won't be generated by server

	int nPrevSize = cFbPhotoLst.items.size();
	mapMy = cFbPhotoLst.mapNextPageParams;
	mapMy.erase(mapMy.find(FB_OFFSET));
	while(!cFbPhotoLst.szNextPageUrl.empty()) //pumping pages to your container
	{
		nResult = m_pFacebookService->GetPhotos(cFbPhotoLst,cFbErr,pIAlbum->szId,mapMy);	
		CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK && cFbPhotoLst.items.size()>=nPrevSize && !cFbPhotoLst.szPreviousPageUrl.empty());
		mapMy = cFbPhotoLst.mapNextPageParams;
		nPrevSize  = cFbPhotoLst.items.size();
	}

	CPPUNIT_ASSERT_MESSAGE("The count of left photos is wrong.",nResult==S_OK && cFbPhotoLst.items.size()==(pIAlbum->nCount-nOffset));

}

void CFacebookServiceTest::terminate()
{
	g_bIsAuthFlowDone = false;
	g_szToken = "";
}

void CFacebookServiceTest::testGetFriendsPhotosInHisAlbum()
{
	model::CFBUserList cFbUsrLst ;
	model::CFBError cFbErr;
	SysMaps::Str2Str mapMy;
	mapMy[FB_FIELDS] = FB_USER_PICTURE;
	mapMy[FB_LIMIT] = "1"; //1 users perpage;
	mapMy[FB_OFFSET] = "2"; // 3rd user
	int nResult = m_pFacebookService->GetFriends(cFbUsrLst,cFbErr,"me",mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),
		nResult==S_OK && cFbUsrLst.items.size()== 1 && !cFbUsrLst.szNextPageUrl.empty() );
	mapMy.clear();

	model::CFBAlbumList cFbAlbumList;
	string szFriendId = cFbUsrLst.items.front()->szId;
	mapMy[FB_LIMIT] = "1"; //1 album perpage
	mapMy[FB_OFFSET] = "1"; // 2nd album
	nResult = m_pFacebookService->GetAlbums(cFbAlbumList,cFbErr,szFriendId,mapMy);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK && cFbAlbumList.items.size()==1
		&& !cFbAlbumList.szNextPageUrl.empty());

	model::IAlbum* pIAlbum  = cFbAlbumList.items.front();	
	model::CFBPhotoList cFbPhotoLst;

	nResult = m_pFacebookService->GetPhotos(cFbPhotoLst,cFbErr,pIAlbum->szId);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==S_OK); 

}

CFBConnectionInfo CFacebookServiceTest::m_cCnctInfoVO;


#pragma once
#include <FacebookService.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class CFacebookServiceTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFacebookServiceTest );
	/*
	* testFBGetLoginURL must be the first function to test, 
	* because it gets the auth token for the consequent tests.
	* Further, it's the simulation of ui flow, so the ut of this function 
	* contains some unnecessary code like the value settings.
	* Do not alter the order of testGetLoginUrl
	* °ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı
	*/
	CPPUNIT_TEST( testGetLoginUrl );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıBasic testing 
	CPPUNIT_TEST( testCallGraphApi );
	CPPUNIT_TEST( testGetUserInfo );
	CPPUNIT_TEST( testGetPhotos );
	CPPUNIT_TEST( testGetFriends );
	CPPUNIT_TEST( testGetVideos );
	CPPUNIT_TEST( testGetAlbums );
	CPPUNIT_TEST( testGetProfile );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙBasic testing 

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıIntegration and Advance testing 
	CPPUNIT_TEST( testGetUserAndUsersInfoWithTumbNail );
	CPPUNIT_TEST( testGetFriendsInfoWithThumbNailAndPaging );
	CPPUNIT_TEST( testGetPhotosInAlbumWithPhotosAndAlbumPaging );
	CPPUNIT_TEST( testGetFriendsPhotosInHisAlbum );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙIntegration and Advance testing 

	CPPUNIT_TEST( terminate );
	CPPUNIT_TEST_SUITE_END();

private:
	CFacebookService* m_pFacebookService;
	static CFBConnectionInfo m_cCnctInfoVO;
	std::wstring s2ws(const std::string& s);

public:
	CFacebookServiceTest(void);
	~CFacebookServiceTest(void);

	void setUp();
	void tearDown();
	void testCallGraphApi();
	void testGetLoginUrl();
	void testGetUserInfo();
	void testGetPhotos();
	void testGetFriends();
	void testGetVideos();
	void testGetAlbums();
	void testGetProfile();

	void testGetUserAndUsersInfoWithTumbNail();
	void testGetFriendsInfoWithThumbNailAndPaging();
	void testGetPhotosInAlbumWithPhotosAndAlbumPaging();
	void testGetFriendsPhotosInHisAlbum();

	void terminate();

};

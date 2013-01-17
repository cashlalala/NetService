#pragma once
#include <FlickrService.h>
#include <IConnectionInfo.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class CFlickRServiceTest
	: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFlickRServiceTest );
	/*
	* testFBGetLoginURL must be the first function to test, 
	* because it gets the auth token for the consequent tests.
	* Further, it's the simulation of ui flow, so the ut of this function 
	* contains some unnecessary code like the value settings.
	* Do not alter the order of testGetLoginUrl
	* °ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı
	*/
	CPPUNIT_TEST( tetGetLoginUrl );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıBasic testing 
	CPPUNIT_TEST( testGetPhotos );
	CPPUNIT_TEST( testGetAlbums );
	CPPUNIT_TEST( testGetFriends );
	CPPUNIT_TEST( testGetUserInfo );
	CPPUNIT_TEST( testGetUsersInfo );
	CPPUNIT_TEST( testGetProfile );
	//CPPUNIT_TEST( testGetForb ); //only for development testing
	//CPPUNIT_TEST( testGetToken ); //only for development testing
	//CPPUNIT_TEST( testGetOAuthRqstToken ); //only for development testing
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙBasic testing 

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıIntegration and Advance testing 
	CPPUNIT_TEST( testGetFriendsPhotosInAlbumWithPhotosAndAlbumPaging );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙIntegration and Advance testing 

	/*
	* Do not move the order these two functions, they should be 
	* always the last two test to be run for the purpose of ui flow simulation
	* °ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı
	*/
	CPPUNIT_TEST( terminate );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù
	CPPUNIT_TEST_SUITE_END();

public:

	CFlickRServiceTest(void);
	~CFlickRServiceTest(void);

	void setUp();
	void tearDown();

	void tetGetLoginUrl();
	void testGetPhotos();
	void testGetAlbums();
	void testGetFriends();
	void testGetUserInfo();
	void testGetUsersInfo();
	void testGetProfile();

	void testGetForb();
	void testGetOAuthRqstToken();
	void testGetToken();

	void testGetFriendsPhotosInAlbumWithPhotosAndAlbumPaging();

	void terminate();

private:
	CFlickrService* m_pFlickrService;
	static CFlickrConnectionInfo m_cCnctInfoVO;
};


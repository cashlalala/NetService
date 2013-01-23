#pragma once


#include <ISocialNetworkService.h>
#include <cppunit/extensions/HelperMacros.h>

class CFlickrServiceTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFlickrServiceTest );	
		/*
	* testFBGetLoginURL must be the first function to test, 
	* because it gets the auth token for the consequent tests.
	* Further, it's the simulation of ui flow, so the ut of this function 
	* contains some unnecessary code like the value settings.
	* Do not alter the order of testGetLoginUrl
	* °ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı
	*/
	CPPUNIT_TEST( testFkrGetLoginUrl );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıBasic testing 
	CPPUNIT_TEST( testFkrGetProfile );
	CPPUNIT_TEST( testFkrGetAlbumList );
	CPPUNIT_TEST( testFkrGetUser );
	CPPUNIT_TEST( testFkrGetUsers );
	CPPUNIT_TEST( testFkrGetPhotos );
	CPPUNIT_TEST( testGetFriends );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙBasic testing 

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıIntegration and Advance testing 
	CPPUNIT_TEST( testGetFriendsPhotosInAlbumWithPhotosAndAlbumPaging );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙIntegration and Advance testing 

	CPPUNIT_TEST( terminate );
	CPPUNIT_TEST_SUITE_END();
public:
	CFlickrServiceTest(void);
	~CFlickrServiceTest(void);
	void setUp();
	void tearDown();

	void testFkrGetLoginUrl();
	void testFkrGetProfile();
	void testFkrGetAlbumList();
	void testFkrGetUser();
	void testFkrGetUsers();
	void testFkrGetPhotos();
	void testGetFriends();

	void testGetFriendsPhotosInAlbumWithPhotosAndAlbumPaging();

	void terminate();
private:
	ISocialNetworkService* pSocialService;
	static CFlickrConnectionInfo m_cCnctInfoVO;
};


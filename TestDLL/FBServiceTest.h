#pragma once

#include <ISocialNetworkService.h>
#include <cppunit/extensions/HelperMacros.h>

class CFBServiceTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFBServiceTest );
	/*
	* testFBGetLoginURL must be the first function to test, 
	* because it gets the auth token for the consequent tests.
	* Further, it's the simulation of ui flow, so the ut of this function 
	* contains some unnecessary code like the value settings.
	* Do not alter the order of testGetLoginUrl
	* °ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı
	*/
	CPPUNIT_TEST( testFBGetLoginURL );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıBasic testing 
	CPPUNIT_TEST( testFBGetProfile );
	CPPUNIT_TEST( testFBGetAlbumList );
	CPPUNIT_TEST( testFBGetUser );
	CPPUNIT_TEST( testFBGetPhotos );
	CPPUNIT_TEST( testGetFriends );
	CPPUNIT_TEST( testGetVideos );
	CPPUNIT_TEST( testGetUsersInfo );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙBasic testing 

	//°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ı°ıIntegration and Advance testing 
	CPPUNIT_TEST( testGetUserAndUsersInfoWithTumbNail );
	// °Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°Ù°ÙIntegration and Advance testing 

	CPPUNIT_TEST( terminate );
	CPPUNIT_TEST_SUITE_END();

public:
	CFBServiceTest(void);
	~CFBServiceTest(void);
	void setUp();
	void tearDown();

	void testFBGetLoginURL();
	void testFBGetProfile();
	void testFBGetAlbumList();
	void testFBGetUser();
	void testFBGetPhotos();
	void testGetFriends();
	void testGetVideos();
	void testGetUsersInfo();

	void testGetUserAndUsersInfoWithTumbNail();

	void terminate();
private:
	ISocialNetworkService* pSocialService;
	static CFBConnectionInfo m_cCnctInfoVO;
};

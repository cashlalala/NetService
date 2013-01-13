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
	* ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ
	*/
	CPPUNIT_TEST( testFBGetLoginURL );
	// ¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô
	CPPUNIT_TEST( testFBGetProfile );
	CPPUNIT_TEST( testFBGetAlbumList );
	CPPUNIT_TEST( testFBGetUser );
	CPPUNIT_TEST( testFBGetPhotos );
	CPPUNIT_TEST( testGetFriends );
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

	void terminate();
private:
	ISocialNetworkService* pSocialService;
	static CFBConnectionInfo m_cCnctInfoVO;
};

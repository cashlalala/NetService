#pragma once

#include <ISocialNetworkService.h>
#include <cppunit/extensions/HelperMacros.h>

class CFBServiceTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFBServiceTest );
	/*
	* testFBGetLoginURL must be the first function to test, 
	* because it get the auth token for the consequent tests
	* Do not alter the order of testFBGetLoginURL
	* ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ
	*/
	CPPUNIT_TEST( testFBGetLoginURL );
	// ¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô
	CPPUNIT_TEST( testFBGetProfile );
	CPPUNIT_TEST( testFBGetAlbumList );
	CPPUNIT_TEST( testFBGetUser );
	CPPUNIT_TEST( testFBGetPhotos );
	CPPUNIT_TEST( testGetFriends );
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
private:
	ISocialNetworkService* pSocialService;
	CFBConnectionInfo m_cCnctInfoVO;
};

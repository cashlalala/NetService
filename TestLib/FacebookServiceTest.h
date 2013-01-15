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
	* ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ
	*/
	CPPUNIT_TEST( testGetLoginUrl );
	// ¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô
	CPPUNIT_TEST( testCallGraphApi );
	CPPUNIT_TEST( testGetUserInfo );
	CPPUNIT_TEST( testGetPhotos );
	CPPUNIT_TEST( testGetFriends );
	CPPUNIT_TEST( testGetVideos );
	CPPUNIT_TEST( testGetAlbums );
	CPPUNIT_TEST( testGetProfile );
	/*
	* Do not move the order these two functions, they should be 
	* always the last two test to be run for the purpose of ui flow simulation
	* ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ¡õ
	*/
	CPPUNIT_TEST( testGetLogoutUrl );
	CPPUNIT_TEST( terminate );
	// ¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô¡ô
	CPPUNIT_TEST_SUITE_END();

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
	void testGetLogoutUrl();

	void terminate();
private:
	CFacebookService* m_pFacebookService;
	static CFBConnectionInfo m_cCnctInfoVO;
	std::wstring s2ws(const std::string& s);
};

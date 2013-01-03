#pragma once
#include <FacebookService.h>
#include <cppunit/extensions/HelperMacros.h>

class CFacebookServiceTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFacebookServiceTest );
	CPPUNIT_TEST( testCallGraphApi );
	CPPUNIT_TEST( testGetLoginUrl );
	CPPUNIT_TEST( testGetUserInfo );
	CPPUNIT_TEST( testGetPhotos );
	CPPUNIT_TEST( testGetFriends );
	CPPUNIT_TEST( testGetVideos );
	CPPUNIT_TEST( testGetAlbums );
	CPPUNIT_TEST( testGetProfile );
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

private:
	CFacebookService* m_pFacebookService;
};

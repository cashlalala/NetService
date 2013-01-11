#pragma once


#include <ISocialNetworkService.h>
#include <cppunit/extensions/HelperMacros.h>

class CFlickrServiceTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFlickrServiceTest );
	/*CPPUNIT_TEST( testFkrGetProfile );
	CPPUNIT_TEST( testFkrGetAlbumList );
	CPPUNIT_TEST( testFkrGetUser );*/
	CPPUNIT_TEST( testFkrGetPhotos );
	//CPPUNIT_TEST( testGetFriends );
	CPPUNIT_TEST_SUITE_END();
public:
	CFlickrServiceTest(void);
	~CFlickrServiceTest(void);
	void setUp();
	void tearDown();

	void testFkrGetProfile();
	void testFkrGetAlbumList();
	void testFkrGetUser();
	void testFkrGetPhotos();
	void testGetFriends();
private:
	ISocialNetworkService* pSocialService;
};


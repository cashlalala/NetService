#pragma once
#include <FlickrService.h>
#include <IConnectionInfo.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class CFlickRServiceTest
	: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFlickRServiceTest );
	CPPUNIT_TEST( testGetForb );
	CPPUNIT_TEST( testGetToken );
	CPPUNIT_TEST( testGetPhotos );
	CPPUNIT_TEST( testGetOAuthRqstToken );
	CPPUNIT_TEST_SUITE_END();

public:

	CFlickRServiceTest(void);
	~CFlickRServiceTest(void);

	void setUp();
	void tearDown();
	void testGetPhotos();
	void testGetForb();
	void testGetOAuthRqstToken();
	void testGetToken();

private:
	CFlickrService* m_pFlickrService;
	CFlickrConnectionInfo m_cCnctInfoVO;
};


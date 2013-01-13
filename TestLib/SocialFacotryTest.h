#pragma once

#include <SocialServiceFactory.h>
#include <cppunit/extensions/HelperMacros.h>


class CSocialFacotryTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CSocialFacotryTest );
	CPPUNIT_TEST( testGetServiceFacebook );
	//CPPUNIT_TEST( testCloseServices ); no more used after apply prototype pattern
	CPPUNIT_TEST_SUITE_END();

public:
	void CSocialFacotryTest::setUp();

	void CSocialFacotryTest::tearDown();
	
	void testGetServiceFacebook();

	void testCloseServices();


};

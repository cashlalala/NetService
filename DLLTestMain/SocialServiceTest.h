#pragma once

#include <ISocialNetworkService.h>
#include <cppunit/extensions/HelperMacros.h>

class CSocialServiceTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CSocialServiceTest );
	CPPUNIT_TEST( testFBGetProfile );
	CPPUNIT_TEST_SUITE_END();

public:
	CSocialServiceTest(void);
	~CSocialServiceTest(void);
	void setUp();
	void tearDown();

	void testFBGetProfile();

private:
	ISocialNetworkService* pSocialService;

};

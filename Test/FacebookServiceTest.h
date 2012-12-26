#pragma once
#include <FacebookService.h>
#include <cppunit/extensions/HelperMacros.h>

class CFacebookServiceTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CFacebookServiceTest );
	CPPUNIT_TEST( testCallGraphApi );
	CPPUNIT_TEST_SUITE_END();

public:
	CFacebookServiceTest(void);
	~CFacebookServiceTest(void);

	void setUp();
	void tearDown();
	void testCallGraphApi();

private:
	CFacebookService* m_pFacebookService;
};

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class CUrlHelperTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CUrlHelperTest );
	CPPUNIT_TEST( testEncodeUrl );
	CPPUNIT_TEST_SUITE_END();
public:
	CUrlHelperTest(void);
	~CUrlHelperTest(void);

	void testEncodeUrl();

	void setUp();
	void tearDown();
};

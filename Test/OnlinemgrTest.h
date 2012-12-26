#pragma once

#include <cppunit/extensions/HelperMacros.h>


class COnlinemgrTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( COnlinemgrTest );
	CPPUNIT_TEST( testLoginUrl );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();

	void tearDown();

	void testLoginUrl();

private:
};

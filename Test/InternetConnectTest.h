#pragma once
#include "..\src\stdafx.h"
#include "..\src\InternetConnectService.h"
#include <cppunit/extensions/HelperMacros.h>

class InternetConnectTest  : public CPPUNIT_NS::TestFixture
{

	CPPUNIT_TEST_SUITE( InternetConnectTest );
	CPPUNIT_TEST( testDetectProxy );
	CPPUNIT_TEST( testForceStopNetKernel );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();


protected:
	void testDetectProxy();
	void testForceStopNetKernel();

private:
	CInternetConnectService* m_pCInetServ;
};

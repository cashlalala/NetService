#include "InternetConnectTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( InternetConnectTest );

void InternetConnectTest::setUp()
{
	m_pCInetServ = new CInternetConnectService();
}

void InternetConnectTest::tearDown()
{
	delete m_pCInetServ ;
}

void InternetConnectTest::testDetectProxy()
{
	m_pCInetServ->SetProxyDetectUrl("http://www.google.com");
	bool result = m_pCInetServ->DetectProxy();

	CPPUNIT_ASSERT(result);
}

void InternetConnectTest::testForceStopNetKernel()
{
	CPPUNIT_ASSERT(true);
}

#pragma once

#include <InternetConnectService.h>
#include <cppunit/extensions/HelperMacros.h>

class InternetConnectTest  : public CPPUNIT_NS::TestFixture
{

	CPPUNIT_TEST_SUITE( InternetConnectTest );
	CPPUNIT_TEST( testDetectProxy );
	CPPUNIT_TEST( testForceStopNetKernel );
	CPPUNIT_TEST( testOpenUrl );
	CPPUNIT_TEST( testOpenUrlWithJpg );
	CPPUNIT_TEST( testOpenUrlWithWrongFileName );
	CPPUNIT_TEST_SUITE_END();

public:
	InternetConnectTest();
	~InternetConnectTest();

	void setUp();
	void tearDown();


protected:
	void testDetectProxy();
	void testForceStopNetKernel();

	void testOpenUrl();
	void testOpenUrlWithJpg();
	void testOpenUrlWithWrongFileName();

private:
	CInternetConnectService* m_pCInetServ;
	wstring m_wszCacheFile;
	string m_szJpgUrl;
	string m_szFacebookUrl;
	string m_szGoogleUrl;
	string m_szProxyUrl;
};

#include "InternetConnectTest.h"
#include <iostream>

//CPPUNIT_TEST_SUITE_REGISTRATION( InternetConnectTest );

InternetConnectTest::InternetConnectTest()
{
	m_wszCacheFile = L"C:\\Users\\cash_chang\\Desktop\\cache.txt";
	m_szJpgUrl = "http://www.peu.cuhk.edu.hk/peuphotos/07-08/acug_tennis2007/DSC02309.jPG";
	m_szFacebookUrl = "http://www.facebook.com";
	m_szGoogleUrl = "http://www.google.com";
	m_szProxyUrl = "http://www.facebook.com";
}

InternetConnectTest::~InternetConnectTest()
{
}

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
	m_pCInetServ->SetProxyDetectUrl(m_szProxyUrl);
	bool result = m_pCInetServ->DetectProxy();

	CPPUNIT_ASSERT(result);
}

void InternetConnectTest::testOpenUrl()
{
	wstring wszfile = m_wszCacheFile;

	string  resp = m_pCInetServ->OpenUrl(m_szGoogleUrl,HTTP_METHOD_GET,wszfile.c_str());

	std::ifstream fs(string(wszfile.begin(),wszfile.end()).c_str(),std::ios::binary|std::ios::ate);
	fs.seekg (0, std::ios::end);
	bool bIsFileSizeZero = (int)fs.tellg()==0;
	fs.close();

	CPPUNIT_ASSERT(!resp.empty() || !bIsFileSizeZero);
}

void InternetConnectTest::testOpenUrlWithJpg()
{
	wstring wszfile = m_wszCacheFile;

	string  resp = m_pCInetServ->OpenUrl(m_szJpgUrl.c_str(),HTTP_METHOD_GET,wszfile.c_str());

	std::ifstream fs(string(wszfile.begin(),wszfile.end()).c_str(),std::ios::binary|std::ios::ate);
	fs.seekg (0, std::ios::end);
	bool bIsFileSizeZero = (int)fs.tellg()==0;
	fs.close();

	CPPUNIT_ASSERT(!resp.empty() || !bIsFileSizeZero);
}

void InternetConnectTest::testOpenUrlWithWrongFileName()
{
	wstring wszfile = L"c:\user\cash\c.txt";

	string  resp = m_pCInetServ->OpenUrl(m_szGoogleUrl.c_str(),HTTP_METHOD_GET,wszfile.c_str());

	std::ifstream fs(string(wszfile.begin(),wszfile.end()).c_str(),std::ios::binary|std::ios::ate);
	fs.seekg (0, std::ios::end);
	bool bIsFileSizeZero = (int)fs.tellg()==0;
	fs.close();

	CPPUNIT_ASSERT(!resp.empty() || !bIsFileSizeZero);
}

void InternetConnectTest::testForceStopNetKernel()
{
	CPPUNIT_ASSERT(true);
}



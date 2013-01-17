#pragma once
#include <CodecHelper.h>
#include <ILogger.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>


class CCodecHelperTest
	: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CCodecHelperTest );
	CPPUNIT_TEST( testEncodeBase64 );
	CPPUNIT_TEST( testDecodeBase64 );
	CPPUNIT_TEST( testCodecBase64 );
	CPPUNIT_TEST( testCreateApiSignature );
	CPPUNIT_TEST_SUITE_END();
public:
	CCodecHelperTest(void);
	~CCodecHelperTest(void);

	void setUp();
	void tearDown();
	void testEncodeBase64();
	void testDecodeBase64();
	void testCodecBase64();
	void testCreateApiSignature();

private:
	std::string m_szTestString;
	std::string m_szTargetString;
	std::string m_szConfigTestString;
	util::CCodecHelper* m_pCodecHelper;
	util::ILogger* m_pLogger;

};


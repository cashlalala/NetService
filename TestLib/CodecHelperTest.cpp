#include "CodecHelperTest.h"
#include <LoggerMgr.h>
#include <Windows.h>
#include <WinBase.h>
#include <SysTypes.h>
#include <FlickrFields.h>

using namespace util;

CPPUNIT_TEST_SUITE_REGISTRATION( CCodecHelperTest );


CCodecHelperTest::CCodecHelperTest(void)
{
	m_pCodecHelper = util::CCodecHelper::GetInstance();
	m_pLogger = CLoggerMgr::GetLogger(util::Log4Cxx,"CCodecHelperTest");
}


CCodecHelperTest::~CCodecHelperTest(void)
{
}


void CCodecHelperTest::setUp()
{

	m_szTestString = "http://api.flickr.com/services/rest/?method=flickr.auth.getFrob&api_key=14866deb67aca156f3366695ad5d6e60&format=json&nojsoncallback=1&api_sig=f722cc4ef06f2c655ba55fba6489e20a";
	m_szTargetString = "aHR0cDovL2FwaS5mbGlja3IuY29tL3NlcnZpY2VzL3Jlc3QvP21ldGhvZD1mbGlja3IuYXV0aC5nZXRGcm9iJmFwaV9rZXk9MTQ4NjZkZWI2N2FjYTE1NmYzMzY2Njk1YWQ1ZDZlNjAmZm9ybWF0PWpzb24mbm9qc29uY2FsbGJhY2s9MSZhcGlfc2lnPWY3MjJjYzRlZjA2ZjJjNjU1YmE1NWZiYTY0ODllMjBh";

	char* lpszTmp = new char[1025];
	memset(lpszTmp,0x0,1025);
	GetPrivateProfileStringA("Codec","base64_teststring",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	m_szConfigTestString = (lpszTmp && strcmp(lpszTmp,"")==0) ? m_szTestString : string(lpszTmp);
	delete[] lpszTmp;	
}

void CCodecHelperTest::tearDown()
{

}

void CCodecHelperTest::testEncodeBase64()
{
	string szEnB64 =m_pCodecHelper->ToBase64(m_szTestString);
	m_pLogger->Debug("[%s] -> [%s]",m_szTestString.c_str(),szEnB64.c_str());
	CPPUNIT_ASSERT_MESSAGE("Encode Fail",szEnB64==m_szTargetString);
}

void CCodecHelperTest::testDecodeBase64()
{
	string szDecB64 =m_pCodecHelper->FromBase64(m_szTargetString);
	m_pLogger->Debug("[%s] -> [%s]",m_szTargetString.c_str(),szDecB64.c_str());
	CPPUNIT_ASSERT_MESSAGE("Decode Fail",szDecB64==m_szTestString);
}

void CCodecHelperTest::testCodecBase64()
{
	m_pLogger->Debug("Input String: [%s]",m_szConfigTestString.c_str());
	string szEnB64 =m_pCodecHelper->ToBase64(m_szConfigTestString);
	string szDecB64 =m_pCodecHelper->FromBase64(szEnB64);
	m_pLogger->Debug("Output String: [%s]",szDecB64.c_str());
	CPPUNIT_ASSERT_MESSAGE("Codec Fail",szDecB64==m_szConfigTestString);
}

void CCodecHelperTest::testCreateApiSignature()
{
	string szExpectSig ="fe24ec7afa1b43c55515e09a8a3c45f3";
	systypes::SysMaps::Str2Str mapStr;
	mapStr[FLICK_PARAM_API_KEY] = "3d62624979ceb69ee5adea9120adabf2";
	mapStr[FLICK_PARAM_METHOD] = "flickr.auth.getFrob";
	string szResult;
	szResult = m_pCodecHelper->ToMD5(mapStr,"4aa693db92b1cf27");
	CPPUNIT_ASSERT_MESSAGE("Sigs don't equal",szResult==szExpectSig);
}


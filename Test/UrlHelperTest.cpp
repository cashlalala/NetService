#include "UrlHelperTest.h"
#include "UrlHelper.h"


CPPUNIT_TEST_SUITE_REGISTRATION( CUrlHelperTest );

CUrlHelperTest::CUrlHelperTest(void)
{
}

CUrlHelperTest::~CUrlHelperTest(void)
{
}

void CUrlHelperTest::setUp()
{

}

void CUrlHelperTest::tearDown()
{

}

void CUrlHelperTest::testEncodeUrl()
{
	string szUrl = " foo^ bar ";

	string szResult = CUrlHelper::EncodeUrl(szUrl);

	CPPUNIT_ASSERT(szResult == "foo%5E%20bar");

}

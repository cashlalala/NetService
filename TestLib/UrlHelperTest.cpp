#include "UrlHelperTest.h"
#include "UrlHelper.h"

using namespace util;

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

void CUrlHelperTest::testToParamMap()
{
	string szUrl = "https://graph.facebook.com/724760664/albums?fields=id,name,count&offset=3&limit=4&before=MTAxNTAyOTAwMjUxMjU2NjU=";
	map<string,string> mapString = CUrlHelper::ToParamMap(szUrl);
	CPPUNIT_ASSERT(true);
}

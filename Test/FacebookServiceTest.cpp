#include "FacebookServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CFacebookServiceTest );

CFacebookServiceTest::CFacebookServiceTest(void)
{
	m_pFacebookService= NULL;
}

CFacebookServiceTest::~CFacebookServiceTest(void)
{
}

void CFacebookServiceTest::setUp()
{
	m_pFacebookService = new CFacebookService();
	ConnectionInfoValueObject cCnctInfoVO;
	cCnctInfoVO.szAccessToken = "AAACEdEose0cBAJIFkl2aceEH7Mz8IO9V5NTnykjONlmtmXPx51odXZAAWCtv8XC1RSUxeZAoFbrVhSRWAoJg1FG2LRc4KPvrfTvflTTwZDZD";
	cCnctInfoVO.szUid = "724760664";
	m_pFacebookService->SetConnectionInfo(cCnctInfoVO);
}

void CFacebookServiceTest::tearDown()
{
	delete m_pFacebookService;
}

void CFacebookServiceTest::testCallGraphApi()
{
	std::string reslut = m_pFacebookService->CallGraphAPI();
	std::cout << reslut << std::endl;
	CPPUNIT_ASSERT(!reslut.empty());
}

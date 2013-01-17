#include "SocialFacotryTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CSocialFacotryTest );


void CSocialFacotryTest::setUp()
{
}

void CSocialFacotryTest::tearDown()
{
}


void CSocialFacotryTest::testGetServiceFacebook()
{
	ISocialNetworkService* pInst = NULL;
	pInst = CSocialServiceFactory::GetSingletonInstance(FACEBOOK);
	CPPUNIT_ASSERT(pInst!=NULL);
}

void CSocialFacotryTest::testCloseServices()
{
	ISocialNetworkService* pInst = NULL;
	pInst = CSocialServiceFactory::GetSingletonInstance(FACEBOOK);
	if (!pInst)
	{
		CPPUNIT_FAIL("Create Instance Fail!!");
		return;
	}

	CSocialServiceFactory::CloseServices();
	bool bAssert = true;
	list<ISocialNetworkService*> listISNServ = CSocialServiceFactory::GetAllServices();
	for (list<ISocialNetworkService*>::iterator it = listISNServ.begin();it!=listISNServ.end();++it)
	{
		if (*it !=NULL)
		{
			bAssert = false;
			break;
		}
	}

	CPPUNIT_ASSERT_MESSAGE("Items in container were not cleaned!!!",bAssert);
}

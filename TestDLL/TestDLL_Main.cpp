// DLLTestMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#include <ISocialNetworkService.h>
#include <IConnectionInfo.h>
#include <FBUserModel.h>
#include <FBErrorModel.h>

HMODULE g_hNerServ = LoadLibraryA("NetService_DLL.dll");

int _tmain(int argc, _TCHAR* argv[])
{

	//ISocialNetworkService::PFNGETINSTANCE pfn = (ISocialNetworkService::PFNGETINSTANCE) GetProcAddress(g_hNerServ,"GetInstance");
	//ISocialNetworkService* pSocialService = pfn(FACEBOOK);
	//CFBConnectionInfo cCnctInfoVO;

	//char* lpszTmp = new char[1025];
	//memset(lpszTmp,0x0,1025);
	//GetModuleFileNameA(NULL,lpszTmp,1024);
	//memset(lpszTmp,0x0,1025);
	//GetPrivateProfileStringA("FBService","access_token",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	//cCnctInfoVO.szAccessToken = string(lpszTmp);

	//memset(lpszTmp,0x0,1025);
	//GetPrivateProfileStringA("FBService","uid",NULL,lpszTmp,1024,"..\\TestData\\TestConfig.ini");
	//cCnctInfoVO.szUid = string(lpszTmp);

	//delete[] lpszTmp;

	//pSocialService->SetConnectionInfo(cCnctInfoVO);

	//model::CFBProfile cFbProfile;
	//model::CFBError cFbErr;

	//int nResult = pSocialService->GetProfile(cFbProfile,cFbErr);

	// Create the event manager and test controller
	CPPUNIT_NS::TextTestResult controller;

	// Add a listener that colllects test result
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );        

	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener( &progress );      

	// Add the top suite to the test runner
	//CPPUNIT_NS::TextTestRunner runner;
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller);

	// Print test in a compiler compatible format.
	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
	outputter.write(); 

	FreeLibrary(g_hNerServ);

	return result.wasSuccessful() ? 0 : 1;
}


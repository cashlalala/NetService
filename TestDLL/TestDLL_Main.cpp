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

#include <cstdlib>

HMODULE g_hNerServ = LoadLibraryA("NetService_DLL.dll");

int _tmain(int argc, _TCHAR* argv[])
{

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

	system("pause");
	return result.wasSuccessful() ? 0 : 1;
}


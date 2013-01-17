// EasyTestPlugIn.cpp : Defines the entry point for the DLL application.
//
#include <LoggerMgr.h>
#include <cppunit/plugin/TestPlugIn.h>


// Implements all the plug-in stuffs, WinMain...
//CPPUNIT_PLUGIN_IMPLEMENT();

CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( CPPUNIT_NS::TestPlugInDefaultImpl ); 

BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		util::CLoggerMgr::Config(util::Log4Cxx);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		util::CLoggerMgr::CleanLoggers();
		break;
	}
	return TRUE;
}       
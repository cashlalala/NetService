// NetService.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "NetService.h"
#include "SocialServiceFactory.h"

#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx::xml;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DOMConfigurator::configure("Log4cxxConfig.xml");
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}


NETSERVCIE_EXTERNC NETSERVICE_API ISocialNetworkService* __cdecl GetInstance(EnServiceType enServTyp)
{
	return CSocialServiceFactory::GetInstance(enServTyp);
}

NETSERVCIE_EXTERNC NETSERVICE_API void __cdecl DelInstance(ISocialNetworkService* pISns)
{
	CSocialServiceFactory::DeleteInstance(pISns);
}


#ifdef _MANAGED
#pragma managed(pop)
#endif

//// This is an example of an exported variable
//NETSERVICE_API int nNetService=0;
//
//// This is an example of an exported function.
//NETSERVICE_API int fnNetService(void)
//{
//	return 42;
//}
//
//// This is the constructor of a class that has been exported.
//// see NetService.h for the class definition
//CNetService::CNetService()
//{
//	return;
//}

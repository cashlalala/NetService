#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#ifdef NETSERVICE_EXPORTS
#define NETSERVICE_API __declspec(dllexport)
#else
#define NETSERVICE_API __declspec(dllimport)
#endif

// This class is exported from the NetService.dll
class NETSERVICE_API CNetService {
public:
	CNetService(void);
	// TODO: add your methods here.
};

extern NETSERVICE_API int nNetService;

NETSERVICE_API int fnNetService(void);

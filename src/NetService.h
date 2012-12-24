// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the NETSERVICE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NETSERVICE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
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

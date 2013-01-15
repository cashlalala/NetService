#pragma once
#include <string>

#define DEFAULT_COUNT_DOWN 40

//expose the symbol for compiler use
extern std::string g_szToken;
extern bool g_bIsAuthFlowDone;

namespace testutil{
	enum ServiceType {
		FB,
		Fkr
	};
}

typedef struct {
	testutil::ServiceType enService;
	std::string szLoginUrl;
	std::string szBrowser;
} ThreadParams;

void BeginMonitorUrlThread(ThreadParams& params);

void WaitForAuthorization();
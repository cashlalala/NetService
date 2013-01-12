#pragma once
#include <string>

#define DEFAULT_COUNT_DOWN 40

//expose the symbol for compiler use
extern std::string g_szToken;

namespace testutil{
	enum ServiceType {
		FB,
		Fkr
	};
}

typedef struct {
	testutil::ServiceType enService;
	std::string szLoginUrl;
} ThreadParams;

void BeginMonitorUrlThread(ThreadParams& params);

void WaitForAuthorization();
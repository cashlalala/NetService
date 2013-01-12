#pragma once
#include <string>

#define DEFAULT_COUNT_DOWN 40

//expose the symbol for compiler use
extern std::string g_szToken;

void BeginMonitorUrlThread();

void WaitForAuthorization();
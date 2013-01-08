#pragma once
#include "internetconnectservice.h"
#include "ISocialNetworkService.h"

using systypes::SysMaps;

#define EXCEPTION_HANDLING(result) if (!SUCCEEDED(result)) break;

typedef struct {
	const char* szServerName;
	const char* szServerURL;
	const char* szPort;
	const char* szSecurePort;
} ServerInfo;

class CBaseSocialService :
	public CInternetConnectService,
	public ISocialNetworkService
{
public:
	virtual ~CBaseSocialService() = 0;

	static const SysMaps::HttpMethod2Str S_MAP_HTTP_METHOD;

};

inline CBaseSocialService::~CBaseSocialService() {};

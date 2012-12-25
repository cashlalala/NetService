#pragma once
#include "internetconnectservice.h"
#include "ISocialNetworkService.h"

class CBaseSocialService :
	public CInternetConnectService,
	public ISocialNetworkService
{
public:
	CBaseSocialService(void);
	~CBaseSocialService(void);

	virtual map<string,string> PrepareParams( string szMethod, map<string,string> params, bool bSignature );

	virtual void CheckError( string szRootNode );

	virtual string GetLoginURL( string params = "" );

	virtual map<string,string> GetMediaData( map<string,string> mapMedia );

};

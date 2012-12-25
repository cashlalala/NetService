#pragma once
#include "baseservice.h"

class CFacebookService :
	public CBaseSocialService
{
public:
	CFacebookService(void);
	~CFacebookService(void);

	virtual map<string,string> PrepareParams( string szMethod, map<string,string> params, bool bSignature );

	virtual void CheckError( string szRootNode );

	virtual string GetLoginURL( string params = "" );

	virtual map<string,string> GetMediaData( map<string,string> mapMedia );

};

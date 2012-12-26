#pragma once
#include "internetconnectservice.h"
#include "ISocialNetworkService.h"

using systypes::SysMaps;

class CBaseSocialService :
	public CInternetConnectService,
	public ISocialNetworkService
{
public:
	CBaseSocialService(void);
	~CBaseSocialService(void);

	virtual SysMaps::Str2Str 
		PrepareParams( string szMethod, SysMaps::Str2Str params, bool bSignature );

	virtual void CheckError( string szRootNode );

	virtual string GetLoginURL( string params = "" );

	virtual SysMaps::Str2Str GetPhotos( SysMaps::Str2Str mapQryCriteria );

	virtual void SetConnectionInfo(ConnectionInfoValueObject cConectInfoVO);

	virtual ConnectionInfoValueObject GetConnectionInfo(void);

	static const SysMaps::HttpMethod2Str S_MAP_HTTP_METHOD;

private:
	ConnectionInfoValueObject m_cConnectInfo;

};

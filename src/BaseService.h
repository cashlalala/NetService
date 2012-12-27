#pragma once
#include "internetconnectservice.h"
#include "ISocialNetworkService.h"

using systypes::SysMaps;

class CBaseSocialService :
	public CInternetConnectService,
	public ISocialNetworkService
{
public:

	virtual SysMaps::Str2Str PrepareParams( string szMethod, SysMaps::Str2Str params, bool bSignature ) =0;

	virtual void CheckError( string szRootNode ) =0;

	virtual string GetLoginURL( string params = "" ) =0;

	virtual IPhotoList GetPhotos( SysMaps::Str2Str mapQryCriteria=SysMaps::Str2Str(), string szId = "me") =0;

	virtual void SetConnectionInfo(ConnectionInfoValueObject cConectInfoVO)
	{
		m_cConnectInfo = cConectInfoVO;
	}

	virtual ConnectionInfoValueObject GetConnectionInfo(void)
	{
		return m_cConnectInfo;
	}

	static const SysMaps::HttpMethod2Str S_MAP_HTTP_METHOD;

private:
	ConnectionInfoValueObject m_cConnectInfo;

};

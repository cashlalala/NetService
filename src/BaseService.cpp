#include "StdAfx.h"
#include "BaseService.h"
#include "MapHelper.h"

CBaseSocialService::CBaseSocialService(void)
:m_cConnectInfo()
{
}

CBaseSocialService::~CBaseSocialService(void)
{
}

SysMaps::Str2Str CBaseSocialService::PrepareParams( string szMethod, SysMaps::Str2Str params, bool bSignature )
{
	throw std::exception("The method or operation is not implemented.");
}

void CBaseSocialService::CheckError( string szRootNode )
{
	throw std::exception("The method or operation is not implemented.");
}

string CBaseSocialService::GetLoginURL( string params /*= "" */ )
{
	throw std::exception("The method or operation is not implemented.");
}

SysMaps::Str2Str CBaseSocialService::GetPhotos( SysMaps::Str2Str mapQryCriteria )
{
	throw std::exception("The method or operation is not implemented.");
}

const SysMaps::HttpMethod2Str
CBaseSocialService::S_MAP_HTTP_METHOD = CMapHelper::CreateHttpMethodMap();

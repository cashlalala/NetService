#include "StdAfx.h"
#include "BaseService.h"

CBaseSocialService::CBaseSocialService(void)
{
}

CBaseSocialService::~CBaseSocialService(void)
{
}

map<string,string> CBaseSocialService::PrepareParams( string szMethod, map<string,string> params, bool bSignature )
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

map<string,string> CBaseSocialService::GetMediaData( map<string,string> mapMedia )
{
	throw std::exception("The method or operation is not implemented.");
}

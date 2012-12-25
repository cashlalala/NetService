#include "StdAfx.h"
#include "FacebookService.h"

CFacebookService::CFacebookService(void)
{
}

CFacebookService::~CFacebookService(void)
{
}

map<string,string> CFacebookService::PrepareParams( string szMethod, map<string,string> params, bool bSignature )
{
	throw std::exception("The method or operation is not implemented.");
}

void CFacebookService::CheckError( string szRootNode )
{
	throw std::exception("The method or operation is not implemented.");
}

string CFacebookService::GetLoginURL( string params /*= "" */ )
{
	throw std::exception("The method or operation is not implemented.");
}

map<string,string> CFacebookService::GetMediaData( map<string,string> mapMedia )
{
	throw std::exception("The method or operation is not implemented.");
}

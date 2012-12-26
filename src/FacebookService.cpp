#include "StdAfx.h"
#include "FacebookService.h"
#include <boost/format.hpp>
#include "MapHelper.h"

using boost::format;
using systypes::EnCategory;
using systypes::EnHttpMethod;

const string CFacebookService::S_STR_URL_PREFIX = "https://";

const SysMaps::EnSvrInfo2Str
CFacebookService::S_MAP_SERVER_INFO = CMapHelper::CreateServerInfoMap();


const SysMaps::EnCat2Str 
CFacebookService::S_MAP_CATEGORY = CMapHelper::CreateCategoryMap();

CFacebookService::CFacebookService(void)
: CBaseSocialService()
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

map<string,string> CFacebookService::GetPhotos( map<string,string> mapQryCriteria )
{
	map<string,string> QQ;
	return QQ;
}

HttpResponseValueObject CFacebookService::CallGraphAPI( string szId, EnCategory enCatogory /*= None*/, SysMaps::Str2Str mapParams /*= MapStringStirng()*/, EnHttpMethod enMethod /*= Get*/, bool bCheckError /*= true*/ )
{
	string szParams;
	for (SysMaps::Str2Str::iterator it = mapParams.begin();it!=mapParams.end();++it)
	{
		szParams += it->first + "=" + it->second;
	}

	//[%1%] [            %2%       ]   [     %3      ]   [ %4%]	 [         %5     ]
	//https:// graph.facebook.com / 724760664 /  photos  ?  fields=id,name
	//format fmter("%1%%2%/%3%/%4%?%5%") % S_STR_URL_PREFIX % S_MAP_SERVER_INFO;

	//
	//if (mapParams["access_token"] == "")
	//	mapParams["access_token"] = this->m_cConnectInfo.szAccessToken;

	HttpResponseValueObject cHttpRespVo;
	return cHttpRespVo;

}



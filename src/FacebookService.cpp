#include "StdAfx.h"
#include "FacebookService.h"
#include "MapHelper.h"
#include "FacebookPhotoModel.h"
#include "..\..\Utility\Debug.h"

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

IPhotoList CFacebookService::GetPhotos(SysMaps::Str2Str mapQryCriteria, string szId)
{
	model::CFacebookPhotoList listPhoto;
	string szResultStr = CallGraphAPI(szId, Photo,mapQryCriteria);

	return listPhoto;
}

string CFacebookService::CallGraphAPI( string szId /*= "me"*/, EnCategory enCatogory /*= None*/, SysMaps::Str2Str mapParams /*= SysMaps::Str2Str()*/, EnHttpMethod enMethod /*= Get*/, bool bCheckError /*= true*/ )
{
	if (mapParams["access_token"]=="")
		mapParams["access_token"] = GetConnectionInfo().szAccessToken;
	
	//[prefix] [    server name       ]     [    szId      ]     [categ]     [   params     ]
	//https://  graph.facebook.com   /  724760664  /  photos  ?  fields=id,name
	string szComposedUrl = 
		CFacebookService::S_STR_URL_PREFIX 
		+	CMapHelper::GetValue(S_MAP_SERVER_INFO,systypes::ServerName)
		+ "/"
		+ ((szId=="")? (GetConnectionInfo().szUid=="")? "me": GetConnectionInfo().szUid : szId)
		+ "/"
		+ CMapHelper::GetValue(S_MAP_CATEGORY,enCatogory)
		+ "?"
		+ CMapHelper::ToParamString(mapParams);

	dprintf("Composed Url is [%s]",szComposedUrl.c_str());

	string szResult = OpenUrl(szComposedUrl);
	return szResult;

}



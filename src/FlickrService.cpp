#include "StdAfx.h"
#include "FlickrService.h"

const string CFlickrService::S_STR_URL_PREFIX = "http://";

CFlickrService::CFlickrService(void)
{
}


CFlickrService::~CFlickrService(void)
{
}

void CFlickrService::SetConnectionInfo( IConnectionInfo& cConectInfoVO )
{
	m_cConnectInfo = *(dynamic_cast<CFlickrConnectionInfo*>(&cConectInfoVO));
}

int CFlickrService::GetPhotos( IPhotoList& iPhotoLst, IError& iErr, string szId /*= "me"*/, SysMaps::Str2Str& mapQryCriteria/*=SysMaps::Str2Str()*/ )
{
	return 0;
}

int CFlickrService::CallApi(HttpRespValObj& cHttpRespVO, string szId /*= "me"*/, EnCategory enCatogory /*= None*/, SysMaps::Str2Str mapParams /*= SysMaps::Str2Str()*/, EnHttpMethod enMethod /*= Get*/, bool bCheckError /*= true*/)
{
	if (mapParams["auth_token"]=="")
		mapParams["auth_token"] = m_cConnectInfo.szAuthToken;
	//http:// api.flickr.com/services/rest/?method=flickr.people.getInfo&api_key=29ad045368681f23ec8bba5b2ac99a07&user_id=91328748%40N02&format=rest&auth_token=72157632466031231-b19acae054059fc1&api_sig=c9719ae3bd5191234082488a9f371ad6
	//string szComposedUrl = S_STR_URL_PREFIX
	//	+ "api.flickr.com/services/rest/?"
	//	+ 

	return 0;
}
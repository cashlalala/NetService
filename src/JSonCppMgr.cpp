#include "StdAfx.h"
#include "JSonCppMgr.h"
#include "FacebookFields.h"
#include "FacebookPhotoModel.h"
#include "NetServiceErr.h"
#include <sstream>
#include <json/json.h>

using util::CJsonCppMgr;

CJsonCppMgr::CJsonCppMgr(void)
{
}

CJsonCppMgr::~CJsonCppMgr(void)
{
}

int util::CJsonCppMgr::ParsePhotoList( string szInput, IPhotoList& iPhotoList, EnDataOwner enDataOwner  ) 
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		switch(enDataOwner)
		{
		case Facebook:
			TravFBPhotoList(jvRoot, iPhotoList);
			nResult = S_OK;
			break;
		case Flickr:
			break;
		default:
			nResult = NS_S_DMGR_NO_DATA_OWNER;
			break;
		}
		
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParsePhoto( string szInput, IPhoto& iPhoto, EnDataOwner enDataOwner  ) 
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		switch(enDataOwner)
		{
		case Facebook:
			{
				TravFBPhoto(jvRoot,iPhoto);
				nResult = S_OK;
				break;
			}
		default: 
			nResult = NS_S_DMGR_NO_DATA_OWNER;
			break;
		}
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

void util::CJsonCppMgr::TravFBPhotoList( Json::Value &jvRoot, IPhotoList &iPhotoList )
{
	int nPhotoNum = jvRoot[FB_DATA].size();
	for (int i=0;i<nPhotoNum;++i)
	{
		Json::Value item = jvRoot[FB_DATA][i];
		model::CFacebookPhoto cFbPhot;
		TravFBPhoto(item,cFbPhot);
		iPhotoList.push_back(cFbPhot);
	}
}

void util::CJsonCppMgr::TravFBPhoto( Json::Value &jvRoot, IPhoto &iPhoto )
{
	model::CFacebookPhoto* pFbPhto = (model::CFacebookPhoto*)&iPhoto;
	pFbPhto->id = jvRoot[FB_ID].asString();
	pFbPhto->nHeight = jvRoot[FB_IMAGE_HEIGHT].asInt();
	pFbPhto->nWidth = jvRoot[FB_IMAGE_WIDTH].asInt();
	pFbPhto->szlink = jvRoot[FB_PHOTO_LINK].asString();
	pFbPhto->szSource = jvRoot[FB_IMAGE_SOURCE].asString();
	int nImageNum = jvRoot[FB_PHOTO_IMAGES].size();
	for (int j = 0; j<nImageNum;++j)
	{
		Json::Value item = jvRoot[FB_PHOTO_IMAGES][j];
		model::IImage iImage;
		iImage.nHeight = item[FB_IMAGE_HEIGHT].asInt();
		iImage.nWidth = item[FB_IMAGE_WIDTH].asInt();
		iImage.szSource = item[FB_IMAGE_SOURCE].asString();
		pFbPhto->listImages.push_back(iImage);
	}
}
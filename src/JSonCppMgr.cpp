#include "StdAfx.h"
#include "JSonCppMgr.h"
#include "FacebookFields.h"
#include "FacebookPhotoModel.h"
#include "NetServiceErr.h"

#include <sstream>

#include <json/json.h>

#define ERROR_RETURN(retVal,retCondition) if (retVal == retCondition) return retVal;

using std::stringstream;
using util::CJsonCppMgr;

CJsonCppMgr::CJsonCppMgr(void)
{
}

CJsonCppMgr::~CJsonCppMgr(void)
{
}

int util::CJsonCppMgr::ParsePhotoList( IPhotoList& iPhotoList, string szInput, EnDataOwner enDataOwner, IError& iError  ) 
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		switch(enDataOwner)
		{
		case Facebook:
			nResult = TravFBErr(jvRoot,iError);
			ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
			TravFBPhotoList(jvRoot, iPhotoList);
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

int util::CJsonCppMgr::ParsePhoto( string szInput, IPhoto& iPhoto, EnDataOwner enDataOwner, IError& iError  ) 
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
				nResult = TravFBErr(jvRoot,iError);
				ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
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

int util::CJsonCppMgr::ParseUser( string szInput, IUser& iUser, EnDataOwner enDataOwner, IError& iError )
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
				nResult = TravFBErr(jvRoot,iError);
				ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
				TravFBUser(jvRoot,iUser);
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
	pFbPhto->szId = jvRoot[FB_ID].asString();
	pFbPhto->nHeight = jvRoot[FB_IMAGE_HEIGHT].asInt();
	pFbPhto->nWidth = jvRoot[FB_IMAGE_WIDTH].asInt();
	pFbPhto->szLink = jvRoot[FB_PHOTO_LINK].asString();
	pFbPhto->szSource = jvRoot[FB_IMAGE_SOURCE].asString();
	int nImageNum = jvRoot[FB_PHOTO_IMAGES].size();
	for (int j = 0; j<nImageNum;++j)
	{
		Json::Value item = jvRoot[FB_PHOTO_IMAGES][j];
		model::CFacebookImage iImage;
		iImage.nHeight = item[FB_IMAGE_HEIGHT].asInt();
		iImage.nWidth = item[FB_IMAGE_WIDTH].asInt();
		iImage.szSource = item[FB_IMAGE_SOURCE].asString();
		pFbPhto->listImages.push_back(iImage);
	}
}


void util::CJsonCppMgr::TravFBUser( Json::Value jvRoot, IUser& iUser )
{
	model::CFBUser* pFbUser = (model::CFBUser*)&iUser;
	pFbUser->szId = jvRoot[FB_ID].asString();
	pFbUser->szFullName = jvRoot[FB_USER_NAME].asString();
}

int util::CJsonCppMgr::TravFBErr( Json::Value &jvRoot, IError& cFbErr )
{
	CFBError* pCFBErr = dynamic_cast<CFBError*>(&cFbErr);
	if (jvRoot[FB_ERROR].isNull()) return S_OK;
	pCFBErr->szCode = jvRoot[FB_ERROR][FB_ERROR_CODE].asString();
	pCFBErr->szMsg = jvRoot[FB_ERROR][FB_ERROR_MSG].asString();
	return NS_E_DMGR_BAD_REQUEST_PARAMS;
}

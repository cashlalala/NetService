#include "StdAfx.h"
#include "JSonCppMgr.h"
#include "FBFields.h"
#include "FBPhotoModel.h"
#include "NetServiceErr.h"
#include "FBUserModel.h"
#include "FBErrorModel.h"

#include <typeinfo>
#include <sstream>

#include <json/json.h>

#define FB_ERROR_RETURN(retVal,retCondition) if (retVal == retCondition) return retVal;

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
			FB_ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
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

int util::CJsonCppMgr::ParsePhoto( IPhoto& iPhoto, string szInput, EnDataOwner enDataOwner, IError& iError  ) 
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
				FB_ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
				TravFBPhoto(jvRoot,&iPhoto);
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

int util::CJsonCppMgr::ParseUser( IUser& iUser, string szInput, EnDataOwner enDataOwner, IError& iError )
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
				FB_ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
				TravFBUser(jvRoot,&iUser);
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
		model::CFBPhoto* cFbPhot = new model::CFBPhoto();
		TravFBPhoto(item,cFbPhot);
		iPhotoList.listPhoto.push_back(cFbPhot);
	}
}

void util::CJsonCppMgr::TravFBPhoto( Json::Value &jvRoot, IPhoto* pIPhoto )
{
	model::CFBPhoto* pFbPhto = dynamic_cast<model::CFBPhoto*>(pIPhoto);
	pFbPhto->szId = jvRoot[FB_ID].asString();
	pFbPhto->nHeight = jvRoot[FB_IMAGE_HEIGHT].asInt();
	pFbPhto->nWidth = jvRoot[FB_IMAGE_WIDTH].asInt();
	pFbPhto->szLink = jvRoot[FB_PHOTO_LINK].asString();
	pFbPhto->szSource = jvRoot[FB_IMAGE_SOURCE].asString();
	int nImageNum = jvRoot[FB_PHOTO_IMAGES].size();
	for (int j = 0; j<nImageNum;++j)
	{
		Json::Value item = jvRoot[FB_PHOTO_IMAGES][j];
		model::CFBImage* iImage = new model::CFBImage();
		iImage->nHeight = item[FB_IMAGE_HEIGHT].asInt();
		iImage->nWidth = item[FB_IMAGE_WIDTH].asInt();
		iImage->szSource = item[FB_IMAGE_SOURCE].asString();
		pFbPhto->listImages.push_back(iImage);
	}
}


void util::CJsonCppMgr::TravFBUser( Json::Value jvRoot, IUser* pIUser )
{
	model::CFBUser* pFbUser = dynamic_cast<model::CFBUser*>(pIUser);
	pFbUser->szId = jvRoot[FB_ID].asString();
	pFbUser->szFullName = jvRoot[FB_USER_NAME].asString();
}

int util::CJsonCppMgr::TravFBErr( Json::Value &jvRoot, IError& cFbErr )
{
	model::CFBError* pCFBErr = dynamic_cast<model::CFBError*>(&cFbErr);
	if (jvRoot[FB_ERROR].isNull()) return S_OK;
	pCFBErr->szCode = jvRoot[FB_ERROR][FB_ERROR_CODE].asString();
	pCFBErr->szMsg = jvRoot[FB_ERROR][FB_ERROR_MSG].asString();
	return NS_E_DMGR_BAD_REQUEST_PARAMS;
}

int util::CJsonCppMgr::ParseError( IError& iError, string szInput, EnDataOwner enDataOwner )
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
				FB_ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
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

int util::CJsonCppMgr::ParseFriendList( IUserList& iUserList, string szInput, EnDataOwner enDataOwner, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		if (typeid(iUserList)==typeid(CFBUserList))
		{
			nResult = TravFBErr(jvRoot,iError);
			FB_ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

			TravFBFriendList(jvRoot,&iUserList);
			nResult = S_OK;
		}
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

void util::CJsonCppMgr::TravFBFriendList( Json::Value jvRoot, IUserList* iUserList )
{
	model::CFBUserList* pFbUserList = dynamic_cast<model::CFBUserList*>(iUserList);
	int nFriendNum = jvRoot[FB_DATA].size();
	for (int i = 0;i<nFriendNum;++i)
	{
		model::CFBUser* pFbUsr = new model::CFBUser(); 
		pFbUsr->szId = jvRoot[FB_DATA][i][FB_ID].asString();
		pFbUsr->szFullName = jvRoot[FB_DATA][i][FB_USER_NAME].asString();
		pFbUsr->szIcon = jvRoot[FB_DATA][i][FB_USER_PICTURE][FB_USER_PICTURE_DATA][FB_USER_PICTURE_DATA_URL].asString();
		pFbUserList->listUser.push_back(pFbUsr);
	}
	pFbUserList->szNext = jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	pFbUserList->szPrevious = jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

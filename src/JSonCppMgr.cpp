#include "StdAfx.h"
#include "JSonCppMgr.h"
#include "FBFields.h"
#include "FBPhotoModel.h"
#include "NetServiceErr.h"
#include "FBUserModel.h"
#include "FBErrorModel.h"
#include "FBVideoModel.h"
#include "FBAlbumModel.h"

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
	pFbPhto->szThumbNail = jvRoot[FB_PHOTO_THUBMNAIL].asString();
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

void util::CJsonCppMgr::TravFBFriendList( Json::Value jvRoot, IUserList* pUserList )
{
	model::CFBUserList* pFbUserList = dynamic_cast<model::CFBUserList*>(pUserList);
	int nFriendNum = jvRoot[FB_DATA].size();
	for (int i = 0;i<nFriendNum;++i)
	{
		model::CFBUser* pFbUsr = new model::CFBUser(); 
		pFbUsr->szId = jvRoot[FB_DATA][i][FB_ID].asString();
		pFbUsr->szFullName = jvRoot[FB_DATA][i][FB_USER_NAME].asString();
		pFbUsr->pProfile  = new CFBProfile();
		pFbUsr->pProfile->szThumNail = jvRoot[FB_DATA][i][FB_USER_PICTURE][FB_USER_PICTURE_DATA][FB_USER_PICTURE_DATA_URL].asString();
		pFbUserList->listUser.push_back(pFbUsr);
	}
	pFbUserList->szNext = jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	pFbUserList->szPrevious = jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

int util::CJsonCppMgr::ParseVideoList( IVideoList&iVideoList, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		if (typeid(iVideoList)==typeid(CFBVideoList))
		{
			nResult = TravFBErr(jvRoot,iError);
			FB_ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

			TravFBVideoList(jvRoot,&iVideoList);
			nResult = S_OK;
		}
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

void util::CJsonCppMgr::TravFBVideoList( Json::Value& jvRoot, IVideoList* pIVideoList )
{
	model::CFBVideoList* pFbVideoList = dynamic_cast<model::CFBVideoList*>(pIVideoList);
	int nVideoNum = jvRoot[FB_DATA].size();
	for (int i = 0 ;i<nVideoNum;++i)
	{
		CFBVideo* pFbVideo = new CFBVideo();
		Json::Value jvItem = jvRoot[FB_DATA][i];
		TravFBVideo(jvItem,pFbVideo);
		pFbVideoList->listVideo.push_back(pFbVideo);
	}
	pFbVideoList->szNext = jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	pFbVideoList->szPrevious = jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

void util::CJsonCppMgr::TravFBVideo( Json::Value& jvRoot, IVideo* pIVideo )
{
		model::CFBVideo* pFbVideo = dynamic_cast<model::CFBVideo*>(pIVideo);
		pFbVideo->szId = jvRoot[FB_ID].asString();
		pFbVideo->szSource = jvRoot[FB_VIDEO_SOURCE].asString();
		pFbVideo->szThumbNail = jvRoot[FB_VIDEO_THUMBNAIL].asString();
		pFbVideo->szEmbedHtml = jvRoot[FB_VIDEO_EMBED_HTML].asString();
		int nVideoFormat = jvRoot[FB_VIDEO_FORMAT].size();
		for (int i = 0;i<nVideoFormat;++i)
		{
			CFBVideoFormat* pFbVideoFormat = new CFBVideoFormat();
			pFbVideoFormat->nHeight = jvRoot[FB_VIDEO_FORMAT][i][FB_VIDEO_HEIGHT].asInt();
			pFbVideoFormat->nWidth = jvRoot[FB_VIDEO_FORMAT][i][FB_VIDEO_WIDTH].asInt();
			pFbVideoFormat->szThumbNail = jvRoot[FB_VIDEO_FORMAT][i][FB_VIDEO_THUMBNAIL].asString();
			pFbVideoFormat->szEmbedHtml = jvRoot[FB_VIDEO_FORMAT][i][FB_VIDEO_EMBED_HTML].asString();
			pFbVideo->listFormat.push_back(pFbVideoFormat);
		}
}

int util::CJsonCppMgr::ParseAlbumList( IAlbumList& iAlbumList, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		if (typeid(iAlbumList)==typeid(CFBAlbumList))
		{
			nResult = TravFBErr(jvRoot,iError);
			FB_ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

			TravFBAlbumList(jvRoot,&iAlbumList);
			nResult = S_OK;
		}
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

void util::CJsonCppMgr::TravFBAlbumList( Json::Value& jvRoot, IAlbumList* pIAlbumList )
{
	model::CFBAlbumList* pFbAlbumList = dynamic_cast<model::CFBAlbumList*>(pIAlbumList);
	int nAlbumNum = jvRoot[FB_DATA].size();
	for (int i = 0 ;i<nAlbumNum;++i)
	{
		CFBAlbum* pFbAlbum = new CFBAlbum();
		Json::Value jvItem = jvRoot[FB_DATA][i];
		TravFBAlbum(jvItem,pFbAlbum);
		pFbAlbumList->listAlbum.push_back(pFbAlbum);
	}
	pFbAlbumList->szNext = jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	pFbAlbumList->szPrevious = jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

void util::CJsonCppMgr::TravFBAlbum( Json::Value& jvRoot, IAlbum* pIAlbum )
{
	model::CFBAlbum* pFbAlbum = dynamic_cast<model::CFBAlbum*>(pIAlbum);
	pFbAlbum->szId = jvRoot[FB_ID].asString();
	pFbAlbum->szCoverPhotoId = jvRoot[FB_ALBUM_COVER_PHOTO].asString();
	pFbAlbum->nCount = jvRoot[FB_ALBUM_PHOTO_COUNT].asInt();
}

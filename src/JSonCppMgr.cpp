#include "StdAfx.h"
#include "JSonCppMgr.h"
#include "FBFields.h"
#include "FBPhotoModel.h"
#include "NetServiceErr.h"
#include "FBUserModel.h"
#include "FBErrorModel.h"
#include "FBVideoModel.h"
#include "FBAlbumModel.h"

#include "FlickrFields.h"
#include "FkRErrorModel.h"
#include "FkRPhotoModel.h"
#include "FkrAlbumModel.h"
#include "FkrUserModel.h"

#include "ErrorParseRuler.h"
#include "PhotoParseRuler.h"
#include "UserParseRuler.h"
#include "AlbumParseRuler.h"
#include "ProfileParseRuler.h"
#include "ImageParseRuler.h"
#include "VideoParseRuler.h"

#include "StringHelper.h"

#include <typeinfo>
#include <sstream>
#include <assert.h>

#include <json/json.h>

#define ERROR_RETURN(retVal,retCondition) if (retVal == retCondition) return retVal;

using std::stringstream;
using util::CJsonCppMgr;

CJsonCppMgr::CJsonCppMgr(void)
{
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_SQ);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_T);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_S);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_Q);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_M);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_N);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_Z);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_C);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_L);
	m_listFkrPhotSizes.push_back(FLICK_PHOTO_O);

	m_pLogger = util::CLoggerMgr::GetLogger(Log4Cxx,"CJsonCppMgr");
}

CJsonCppMgr::~CJsonCppMgr(void)
{
}

int util::CJsonCppMgr::ParsePhotoList( IPhotoList& iPhotoList, string szInput, IError& iError  ) 
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CPhotoListParseRuler cPhotoLstRuler((void*)&jvRoot);
		iPhotoList.AcceptPhotoListParser(cPhotoLstRuler);		
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParsePhoto( IPhoto& iPhoto, string szInput, IError& iError  ) 
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CPhotoParseRuler cPhotoRuler((void*)&jvRoot);
		iPhoto.AcceptPhotoParser(cPhotoRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseUser( IUser& iUser, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CUserParseRuler cUserRuler((void*)&jvRoot);
		iUser.AcceptUserParser(cUserRuler);
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
		iPhotoList.items.push_back(cFbPhot);
	}
	TravFBPagination(iPhotoList, jvRoot);
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
	TravFBImgList(jvRoot[FB_PHOTO_IMAGES], *pIPhoto->pListImage);
}


void util::CJsonCppMgr::TravFBUser( Json::Value jvRoot, IUser* pIUser )
{
	model::CFBUser* pFbUser = dynamic_cast<model::CFBUser*>(pIUser);
	pFbUser->szId = jvRoot[FB_ID].asString();
	pFbUser->szFullName = jvRoot[FB_USER_NAME].asString();
	if (!jvRoot[FB_USER_PICTURE].isNull())
	{
		pFbUser->pProfile = new CFBProfile();
		pFbUser->pProfile->szThumNail = jvRoot[FB_USER_PICTURE][FB_USER_PICTURE_DATA][FB_USER_PICTURE_DATA_URL].asString();
	}
}

int util::CJsonCppMgr::TravFBErr( Json::Value &jvRoot, IError& cFbErr )
{
	model::CFBError* pCFBErr = dynamic_cast<model::CFBError*>(&cFbErr);
	if (jvRoot[FB_ERROR].isNull()) return S_OK;
	pCFBErr->szCode = jvRoot[FB_ERROR][FB_ERROR_CODE].asString();
	pCFBErr->szMsg = jvRoot[FB_ERROR][FB_ERROR_MSG].asString();
	return NS_E_DMGR_BAD_REQUEST_PARAMS;
}

int util::CJsonCppMgr::ParseError( IError& iError, string szInput )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseFriendList( IUserList& iUserList, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CUserListParseRuler cUsrLstRuler((void*)&jvRoot);
		iUserList.AcceptUserListParser(cUsrLstRuler);	
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
		TravFBUser(jvRoot[FB_DATA][i],pFbUsr);
		pFbUserList->items.push_back(pFbUsr);
	}
	TravFBPagination(*pFbUserList,jvRoot);
}

int util::CJsonCppMgr::ParseVideoList( IVideoList&iVideoList, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CVideoListParseRuler cVideoLstRuler((void*)&jvRoot);
		iVideoList.AcceptVideoListParser(cVideoLstRuler);
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
		pFbVideoList->items.push_back(pFbVideo);
	}
	TravFBPagination(*pFbVideoList,jvRoot);
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
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CAlbumListParseRuler cAlbumLstRuler((void*)&jvRoot);
		iAlbumList.AcceptAlbumListParser(cAlbumLstRuler);		
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
		pFbAlbumList->items.push_back(pFbAlbum);
	}
	TravFBPagination(*pFbAlbumList, jvRoot);
}

void util::CJsonCppMgr::TravFBAlbum( Json::Value& jvRoot, IAlbum* pIAlbum )
{
	model::CFBAlbum* pFbAlbum = dynamic_cast<model::CFBAlbum*>(pIAlbum);
	pFbAlbum->szId = jvRoot[FB_ID].asString();
	pFbAlbum->szName = jvRoot[FB_ALBUM_NAME].asString();
	pFbAlbum->szCoverPhotoId = jvRoot[FB_ALBUM_COVER_PHOTO].asString();
	pFbAlbum->nCount = jvRoot[FB_ALBUM_PHOTO_COUNT].asInt();
}

int util::CJsonCppMgr::ParseProfile( IProfile& iProfile, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CProfileParseRuler cProfileRuler((void*)&jvRoot);
		iProfile.AcceptProfileParser(cProfileRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::TravFBProfile( Json::Value& jvRoot, IProfile* pIProfile, IError& iError )
{
	model::CFBProfile* pFbProfile = dynamic_cast<model::CFBProfile*>(pIProfile);
	int nSize = jvRoot[FB_DATA].size();
	if (nSize==1)
	{
		pFbProfile->szThumNail = jvRoot[FB_DATA][0][FB_PROFILE_PIC].asString();
		pFbProfile->szBig = jvRoot[FB_DATA][0][FB_PROFILE_PIC_BIG].asString();
		pFbProfile->szSmall = jvRoot[FB_DATA][0][FB_PROFILE_PIC_SMALL].asString();
		pFbProfile->szSquare = jvRoot[FB_DATA][0][FB_PROFILE_PIC_SQUARE].asString();
		return S_OK;
	}
	else
		return NS_E_DMGR_WRONG_DATA_SIZE;
}

int util::CJsonCppMgr::TravFkrErr(Json::Value& jvRoot, IError& iError)
{
	model::CFkrError* pFkrErr = dynamic_cast<model::CFkrError*>(&iError);
	pFkrErr->szStat = jvRoot[FLICK_ERROR_STAT].asString();
	if (pFkrErr->szStat == "ok") return S_OK;
	pFkrErr->szCode = jvRoot[FLICK_ERROR_CODE].asString();
	pFkrErr->szMsg = jvRoot[FLICK_ERROR_MSG].asString();
	return NS_E_DMGR_BAD_REQUEST_PARAMS;
}

int util::CJsonCppMgr::ParseFkrFrob( string& szFrob, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		nResult = TravFkrErr(jvRoot,iError);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		szFrob = jvRoot[FLICK_FIELD_FROB][FLICK_FIELD_CONTENT].asString();
		nResult = S_OK;
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseFkrAuthToken( SysMaps::Str2Str& mapAuth, string szInput,IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		nResult = TravFkrErr(jvRoot,iError);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		mapAuth[FLICK_AUTH_TOKEN] = jvRoot[FLICK_AUTH][FLICK_AUTH_TOKEN][FLICK_AUTH_TOKEN_CONTENT].asString();
		mapAuth[FLICK_AUTH_NSID] = jvRoot[FLICK_AUTH][FLICK_AUTH_USER][FLICK_AUTH_NSID].asString();
		nResult = S_OK;
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

void util::CJsonCppMgr::TravrFkrPhotoList( Json::Value &jvRoot, IPhotoList &iPhotoList )
{
	model::CFkrPhotoList* cFkrPhotoLst  = dynamic_cast<model::CFkrPhotoList*>( &iPhotoList);
	
	string szSets = FLICK_PHOTOS;
	if (jvRoot[szSets].isNull()) szSets = FLICK_PHOTOSET;
	//for composing the next & prev page url
	cFkrPhotoLst->nPage = atoi(jvRoot[szSets][FLICK_PHOTOS_PAGE].asString().c_str());
	cFkrPhotoLst->nPages = atoi(jvRoot[szSets][FLICK_PHOTOS_PAGES].asString().c_str());
	cFkrPhotoLst->nPerpage = atoi(jvRoot[szSets][FLICK_PHOTOS_PERPAGE].asString().c_str());
	cFkrPhotoLst->nTotal = atoi(jvRoot[szSets][FLICK_PHOTOS_TOTAL].asString().c_str());

	int nPhotoNum = jvRoot[szSets][FLICK_PHOTO].size();
	for (int i=0;i<nPhotoNum;++i)
	{
		Json::Value item = jvRoot[szSets][FLICK_PHOTO][i];
		model::CFkrPhoto* cFkrPhoto = new model::CFkrPhoto();
		TravFkrPhoto(item,cFkrPhoto);
		cFkrPhotoLst->items.push_back(cFkrPhoto);
	}
}

void util::CJsonCppMgr::TravFkrPhoto( Json::Value &jvRoot, IPhoto* pIPhoto )
{
	model::CFkrPhoto* pFkrPhto = dynamic_cast<model::CFkrPhoto*>(pIPhoto);
	pFkrPhto->bIsFamily = jvRoot[FLICK_PHOTO_ISFAMILY].asBool();
	pFkrPhto->bIsFriend = jvRoot[FLICK_PHOTO_ISFRIEND].asBool();
	pFkrPhto->bIsPublic = jvRoot[FLICK_PHOTO_ISPUBLIC].asBool();
	pFkrPhto->szId = jvRoot[FLICK_PHOTO_ID].asString();
	pFkrPhto->szTitle = jvRoot[FLICK_PHOTO_TITLE].asString();
	pFkrPhto->szOwner = jvRoot[FLICK_PHOTO_OWNER].asString();
	pFkrPhto->szLink = "http://www.flickr.com/photos/" + pFkrPhto->szOwner + "/"+ pFkrPhto->szId;
	pFkrPhto->szMedia = jvRoot[FLICK_PHOTO_MEDIA].asString();

	//the original size if only available for pro user
	pFkrPhto->szSource = jvRoot[FLICK_PHOTO_URL_O].asString();
	pFkrPhto->nHeight = atoi(jvRoot[FLICK_PHOTO_HEIGHT_O].asString().c_str());
	pFkrPhto->nWidth = atoi(jvRoot[FLICK_PHOTO_WIDTH_O].asString().c_str());
	pFkrPhto->szThumbNail = jvRoot[FLICK_PHOTO_URL_T].asString();	

	std::list<string>::iterator it = m_listFkrPhotSizes.begin();
	for (;it!=m_listFkrPhotSizes.end();++it)
	{
		model::CFkrImage* pFkrImg = new model::CFkrImage();
		pFkrImg->szSource = jvRoot[FLICK_PHOTO_URL + *it].asString();
		pFkrImg->nWidth = atoi(jvRoot[FLICK_PHOTO_WIDTH + *it].asString().c_str());
		pFkrImg->nHeight = atoi(jvRoot[FLICK_PHOTO_HEIGHT + *it].asString().c_str());
		pFkrPhto->pListImage->items.push_back(pFkrImg);
	}
}

void util::CJsonCppMgr::TravFkrAlbumList( Json::Value& jvRoot, IAlbumList& iAlbumList )
{
	model::CFkrAlbumList* pFkrAlbumLst = dynamic_cast<model::CFkrAlbumList*>(&iAlbumList);
	pFkrAlbumLst->nPage = atoi(jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_PAGE].asString().c_str());
	pFkrAlbumLst->nPages = atoi(jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_PAGES].asString().c_str());
	pFkrAlbumLst->nPerpage = atoi(jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_PERPAGE].asString().c_str());
	pFkrAlbumLst->nTotal = atoi(jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_TOTAL].asString().c_str());

	int nAlbums = jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSET].size();
	for (int i =0;i<nAlbums;++i)
	{
		Json::Value item = jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSET][i];
		model::CFkrAlbum* cFkrAlbum = new model::CFkrAlbum();
		TravFkrAlbum(item,cFkrAlbum);
		iAlbumList.items.push_back(cFkrAlbum);
	}
}

void util::CJsonCppMgr::TravFkrAlbum( Json::Value& item,IAlbum* pIAlbum )
{
	model::CFkrAlbum* pFkrAlbum = dynamic_cast<model::CFkrAlbum*>(pIAlbum);
	pFkrAlbum->nCount = atoi(item[FLICK_PHOTOSET_VIDEOS].asString().c_str()) + 
										atoi(item[FLICK_PHOTOSET_PHOTOS].asString().c_str());
	pFkrAlbum->szCoverPhotoId = item[FLICK_PHOTOSET_PRIMARY].asString();
	pFkrAlbum->szDescription = item[FLICK_PHOTOSET_DESCRIPTION][FLICK_FIELD_CONTENT].asString();
	pFkrAlbum->szId = item[FLICK_PHOTOSET_ID].asString();
	pFkrAlbum->szTitle = item[FLICK_PHOTOSET_TITLE][FLICK_FIELD_CONTENT].asString();
	pFkrAlbum->szThumbNail = util::CStringHelper::Format("http://farm%s.staticflickr.com/%s/%s_%s_t.jpg",
																							item[FLICK_PHOTOSET_FARM].asString().c_str(),
																							item[FLICK_PHOTOSET_SERVER].asString().c_str(),
																							pFkrAlbum->szCoverPhotoId.c_str(),
																							item[FLICK_PHOTOSET_SECRET].asString().c_str());
}

void util::CJsonCppMgr::TravFkrFriendList( Json::Value& jvRoot, IUserList& iUserList )
{
	model::CFkrUserList* pFrkUsrLst = dynamic_cast<model::CFkrUserList*>(&iUserList);
	pFrkUsrLst->nPage = atoi(jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_PAGE].asString().c_str());
	pFrkUsrLst->nPages = atoi(jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_PAGES].asString().c_str());
	pFrkUsrLst->nPerpage = atoi(jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_PERPAGE].asString().c_str());
	pFrkUsrLst->nTotal = atoi(jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_TOTAL].asString().c_str());

	int nFriends = jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_CONTACT].size();
	for (int i =0;i<nFriends;++i)
	{
		Json::Value item = jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_CONTACT][i];
		model::CFkrUser* cFkrUsr = new model::CFkrUser();
		TravFkrFriend(item,cFkrUsr);
		iUserList.items.push_back(cFkrUsr);
	}
}

void util::CJsonCppMgr::TravFkrFriend( Json::Value& item, model::IUser* pIUsr )
{
	model::CFkrUser* pFkrUsr = dynamic_cast<model::CFkrUser*>(pIUsr);
	pFkrUsr->szId = item[FLICK_CONTACT_NSID].asString();
	pFkrUsr->szFullName = item[FLICK_CONTACT_REAL_NAME].asString();
	pFkrUsr->szUsrName = item[FLICK_CONTACT_USR_NAME].asString();
	pFkrUsr->bIsFriend = item[FLICK_CONTACT_FRIEND].asBool();
	pFkrUsr->bIsFamily = item[FLICK_CONTACT_FAMILY].asBool();	
	if (item[FLICK_CONTACT_ICON_FARM].asString()=="0" && 
		item[FLICK_CONTACT_ICON_SVR].asString()=="0")
	{
		LOGGER_DEBUG(m_pLogger,"This queryee [%s] don't have the thumbnail or open the access right for the querier",pFkrUsr->szId.c_str())
	}
	else
	{
		pFkrUsr->pProfile = new CFkrProfile();
		pFkrUsr->pProfile->szThumNail = util::CStringHelper::Format("http://farm%s.staticflickr.com/%s/buddyicons/%s.jpg", 
			item[FLICK_CONTACT_ICON_FARM].asString().c_str(),
			item[FLICK_CONTACT_ICON_SVR].asString().c_str(),
			pFkrUsr->szId.c_str());
	}
}

void util::CJsonCppMgr::TravFkrUser( Json::Value& jvRoot, IUser& iUser )
{
	model::CFkrUser* pFkrUser = dynamic_cast<model::CFkrUser*>(&iUser);
	pFkrUser->bIsFamily = atoi(jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ISFAMILY].asString().c_str()) != 0;
	pFkrUser->bIsFriend = atoi(jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ISFRIEND].asString().c_str()) != 0;
	pFkrUser->bIsProUsr = atoi(jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ISPRO].asString().c_str()) != 0;
	pFkrUser->szFullName = jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_REAL_NAME][FLICK_FIELD_CONTENT].asString();
	pFkrUser->szId = jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ID].asString();
	pFkrUser->szUsrName = jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_USR_NAME][FLICK_FIELD_CONTENT].asString();
	if (jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ICONFARM].asString()=="0" && 
		jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ICONSVR].asString()=="0")
	{
		LOGGER_DEBUG(m_pLogger,"This queryee [%s] don't have the thumbnail or open the access right for the querier",pFkrUser->szId.c_str())
	}
	else
	{
		pFkrUser->pProfile = new CFkrProfile();
		pFkrUser->pProfile->szThumNail = util::CStringHelper::Format("http://farm%s.staticflickr.com/%s/buddyicons/%s.jpg", 
			jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ICONFARM].asString().c_str(),
			jvRoot[FLICK_PEOPLE_PERSON][FLICK_PEOPLE_PERSON_ICONSVR].asString().c_str(),
			pFkrUser->szId.c_str());
	}
		

	
}

void util::CJsonCppMgr::TravFBPagination( IPage &iPhotoList, Json::Value & jvRoot )
{
	iPhotoList.szNextPageUrl = jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	iPhotoList.szPreviousPageUrl = jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

void util::CJsonCppMgr::TravFBImgList( Json::Value & jvRoot, IImageList& iImgList )
{
	int nImageNum = jvRoot.size();
	for (int j = 0; j<nImageNum;++j)
	{
		Json::Value item = jvRoot[j];
		model::CFBImage* pIImage = new model::CFBImage();
		TravFBImg(item, *pIImage);
		iImgList.items.push_back(pIImage);
	}
}

void util::CJsonCppMgr::TravFBImg( Json::Value& item, model::IImage& iImage)
{
	iImage.nHeight = item[FB_IMAGE_HEIGHT].asInt();
	iImage.nWidth = item[FB_IMAGE_WIDTH].asInt();
	iImage.szSource = item[FB_IMAGE_SOURCE].asString();
}

int util::CJsonCppMgr::ParseImageList( IImageList& listImage, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		CImageListParseRuler cImgLstRuler((void*)&jvRoot);
		listImage.AcceptImageListParser(cImgLstRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseFBSrouceSmall( SysList::Str2StrMapList& listMap, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		nResult = TravFBErr(jvRoot,iError);
		ERROR_RETURN(nResult,NS_E_DMGR_BAD_REQUEST_PARAMS)

		int nSize = jvRoot[FB_DATA].size();
		for (int i=0;i<nSize;++i)
		{
			SysMaps::Str2Str mapCoverPhoto;
			mapCoverPhoto[FB_IMAGE_SOURCE_SMALL] = jvRoot[FB_DATA][i][FB_IMAGE_SOURCE_SMALL].asString();
			mapCoverPhoto[FB_ALBUM_OBJECT_ID] = jvRoot[FB_DATA][i][FB_ALBUM_OBJECT_ID].asString();
			listMap.push_back(mapCoverPhoto);
		}
		nResult = S_OK;
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

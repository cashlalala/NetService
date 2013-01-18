#include "stdafx.h"
#include "PhotoParseRuler.h"

#include "FkRPhotoModel.h"
#include "FBPhotoModel.h"
#include "FlickrFields.h"
#include "FBFields.h"

#include "ImageParseRuler.h"

#include "ListHelper.h"

void util::CPhotoListParseRuler::Traverse( CFBPhotoList& cFBPhotoList )
{
	int nPhotoNum = m_jvRoot[FB_DATA].size();
	CPhotoParseRuler cPhotoRuler;
	for (int i=0;i<nPhotoNum;++i)
	{
		Json::Value item = m_jvRoot[FB_DATA][i];
		cPhotoRuler.SetExecutor((void*)&item);
		CFBPhoto* pFbPhot = new CFBPhoto();
		pFbPhot->AcceptPhotoParser(cPhotoRuler);
		cFBPhotoList.items.push_back(pFbPhot);
	}
	cFBPhotoList.szNextPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	cFBPhotoList.szPreviousPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

void util::CPhotoListParseRuler::Traverse( CFkrPhotoList& cFkrPhotoList )
{
	string szSets = FLICK_PHOTOS;
	if (m_jvRoot[szSets].isNull()) szSets = FLICK_PHOTOSET;
	//for composing the next & prev page url
	cFkrPhotoList.nPage = atoi(m_jvRoot[szSets][FLICK_PHOTOS_PAGE].asString().c_str());
	cFkrPhotoList.nPages = atoi(m_jvRoot[szSets][FLICK_PHOTOS_PAGES].asString().c_str());
	cFkrPhotoList.nPerpage = atoi(m_jvRoot[szSets][FLICK_PHOTOS_PERPAGE].asString().c_str());
	cFkrPhotoList.nTotal = atoi(m_jvRoot[szSets][FLICK_PHOTOS_TOTAL].asString().c_str());

	int nPhotoNum = m_jvRoot[szSets][FLICK_PHOTO].size();
	CPhotoParseRuler cPhotoRuler;
	for (int i=0;i<nPhotoNum;++i)
	{
		Json::Value item = m_jvRoot[szSets][FLICK_PHOTO][i];
		cPhotoRuler.SetExecutor((void*)&item);
		model::CFkrPhoto* cFkrPhoto = new model::CFkrPhoto();
		cFkrPhoto->AcceptPhotoParser(cPhotoRuler);
		cFkrPhotoList.items.push_back(cFkrPhoto);
	}
}

util::CPhotoListParseRuler::CPhotoListParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

util::CPhotoListParseRuler::CPhotoListParseRuler()
{

}

void util::CPhotoListParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

void util::CPhotoParseRuler::Traverse( CFBPhoto& cFBPhoto )
{
	cFBPhoto.szId = m_jvRoot[FB_ID].asString();
	cFBPhoto.nHeight = m_jvRoot[FB_IMAGE_HEIGHT].asInt();
	cFBPhoto.nWidth = m_jvRoot[FB_IMAGE_WIDTH].asInt();
	cFBPhoto.szLink = m_jvRoot[FB_PHOTO_LINK].asString();
	cFBPhoto.szSource = m_jvRoot[FB_IMAGE_SOURCE].asString();
	cFBPhoto.szThumbNail = m_jvRoot[FB_PHOTO_THUBMNAIL].asString();
	cFBPhoto.pListImage = new CFBImageList();
	CImageListParseRuler cImgLstRuler((void*)&m_jvRoot[FB_PHOTO_IMAGES]);
	cFBPhoto.pListImage->AcceptImageListParser(cImgLstRuler);
}

void util::CPhotoParseRuler::Traverse( CFkrPhoto& cFkrPhoto )
{
	cFkrPhoto.bIsFamily = m_jvRoot[FLICK_PHOTO_ISFAMILY].asBool();
	cFkrPhoto.bIsFriend = m_jvRoot[FLICK_PHOTO_ISFRIEND].asBool();
	cFkrPhoto.bIsPublic = m_jvRoot[FLICK_PHOTO_ISPUBLIC].asBool();
	cFkrPhoto.szId = m_jvRoot[FLICK_PHOTO_ID].asString();
	cFkrPhoto.szTitle = m_jvRoot[FLICK_PHOTO_TITLE].asString();
	cFkrPhoto.szOwner = m_jvRoot[FLICK_PHOTO_OWNER].asString();
	cFkrPhoto.szLink = "http://www.flickr.com/photos/" + cFkrPhoto.szOwner + "/"+ cFkrPhoto.szId;
	cFkrPhoto.szMedia = m_jvRoot[FLICK_PHOTO_MEDIA].asString();

	//the original size if only available for pro user
	cFkrPhoto.szSource = m_jvRoot[FLICK_PHOTO_URL_O].asString();
	cFkrPhoto.nHeight = atoi(m_jvRoot[FLICK_PHOTO_HEIGHT_O].asString().c_str());
	cFkrPhoto.nWidth = atoi(m_jvRoot[FLICK_PHOTO_WIDTH_O].asString().c_str());
	cFkrPhoto.szThumbNail = m_jvRoot[FLICK_PHOTO_URL_T].asString();	

	cFkrPhoto.pListImage = new CFkrImageList();
	std::list<string>::const_iterator it = S_LIST_FKRPHOTOSIZES.begin();
	for (;it!=S_LIST_FKRPHOTOSIZES.end();++it)
	{
		model::CFkrImage* pFkrImg = new model::CFkrImage();
		pFkrImg->szSource = m_jvRoot[FLICK_PHOTO_URL + *it].asString();
		pFkrImg->nWidth = atoi(m_jvRoot[FLICK_PHOTO_WIDTH + *it].asString().c_str());
		pFkrImg->nHeight = atoi(m_jvRoot[FLICK_PHOTO_HEIGHT + *it].asString().c_str());
		cFkrPhoto.pListImage->items.push_back(pFkrImg);
	}
}

util::CPhotoParseRuler::CPhotoParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

util::CPhotoParseRuler::CPhotoParseRuler()
{

}

void util::CPhotoParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

const list<string> util::CPhotoParseRuler::S_LIST_FKRPHOTOSIZES = util::CListHelper::CreateFkrImgFormatList();


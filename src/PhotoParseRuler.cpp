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
	int nPhotoNum = m_pParser->GetValueAsArrarySize(FB_DATA);
	CPhotoParseRuler cPhotoRuler;
	cPhotoRuler.SetExecutor(m_pParser);
	m_pParser->StoreRoot();
	for (int i=0;i<nPhotoNum;++i)
	{
		m_pParser->GetObjectAsRoot("%s.%d",FB_DATA,i);
		CFBPhoto* pFbPhot = new CFBPhoto();
		pFbPhot->AcceptPhotoParser(cPhotoRuler);
		cFBPhotoList.items.push_back(pFbPhot);
		m_pParser->RestoreRoot();
	}
	m_pParser->ClearBuffTop();
	cFBPhotoList.szNextPageUrl = m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_NEXT);
	cFBPhotoList.szPreviousPageUrl = m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_PREVIOUS);
}

void util::CPhotoListParseRuler::Traverse( CFkrPhotoList& cFkrPhotoList )
{
	string szSets = FLICK_PHOTOS;
	if (m_pParser->IsObjectNull(szSets.c_str())) szSets = FLICK_PHOTOSET;
	//for composing the next & prev page url
	cFkrPhotoList.nPage = atoi(m_pParser->GetValueAsString("%s.%s",szSets.c_str(),FLICK_PHOTOS_PAGE).c_str());
	cFkrPhotoList.nPages = atoi(m_pParser->GetValueAsString("%s.%s",szSets.c_str(),FLICK_PHOTOS_PAGES).c_str());
	cFkrPhotoList.nPerpage = atoi(m_pParser->GetValueAsString("%s.%s",szSets.c_str(),FLICK_PHOTOS_PERPAGE).c_str());
	cFkrPhotoList.nTotal = atoi(m_pParser->GetValueAsString("%s.%s",szSets.c_str(),FLICK_PHOTOS_TOTAL).c_str());

	int nPhotoNum = m_pParser->GetValueAsArrarySize("%s.%s",szSets.c_str(),FLICK_PHOTO);
	CPhotoParseRuler cPhotoRuler;
	cPhotoRuler.SetExecutor(m_pParser);
	m_pParser->StoreRoot();
	for (int i=0;i<nPhotoNum;++i)
	{
		m_pParser->GetObjectAsRoot("%s.%s.%d",szSets.c_str(),FLICK_PHOTO,i);
		model::CFkrPhoto* cFkrPhoto = new model::CFkrPhoto();
		cFkrPhoto->AcceptPhotoParser(cPhotoRuler);
		cFkrPhotoList.items.push_back(cFkrPhoto);
		m_pParser->RestoreRoot();
	}
	m_pParser->ClearBuffTop();
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
}

void util::CPhotoListParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

void util::CPhotoParseRuler::Traverse( CFBPhoto& cFBPhoto )
{
	cFBPhoto.szId = m_pParser->GetValueAsString(FB_ID);
	cFBPhoto.nHeight = m_pParser->GetValueAsInt(FB_IMAGE_HEIGHT);
	cFBPhoto.nWidth = m_pParser->GetValueAsInt(FB_IMAGE_WIDTH);
	cFBPhoto.szLink = m_pParser->GetValueAsString(FB_PHOTO_LINK);
	cFBPhoto.szSource = m_pParser->GetValueAsString(FB_IMAGE_SOURCE);
	cFBPhoto.szThumbNail = m_pParser->GetValueAsString(FB_PHOTO_THUBMNAIL);
	cFBPhoto.pListImage = new CFBImageList();
	CImageListParseRuler cImgLstRuler;
	cImgLstRuler.SetExecutor(m_pParser);
	cFBPhoto.pListImage->AcceptImageListParser(cImgLstRuler);
}

void util::CPhotoParseRuler::Traverse( CFkrPhoto& cFkrPhoto )
{
	cFkrPhoto.bIsFamily = m_pParser->GetValueAsBool(FLICK_PHOTO_ISFAMILY);
	cFkrPhoto.bIsFriend = m_pParser->GetValueAsBool(FLICK_PHOTO_ISFRIEND);
	cFkrPhoto.bIsPublic = m_pParser->GetValueAsBool(FLICK_PHOTO_ISPUBLIC);
	cFkrPhoto.szId = m_pParser->GetValueAsString(FLICK_PHOTO_ID);
	cFkrPhoto.szTitle = m_pParser->GetValueAsString(FLICK_PHOTO_TITLE);
	cFkrPhoto.szOwner = m_pParser->GetValueAsString(FLICK_PHOTO_OWNER);
	cFkrPhoto.szLink = "http://www.flickr.com/photos/" + cFkrPhoto.szOwner + "/"+ cFkrPhoto.szId;
	cFkrPhoto.szMedia = m_pParser->GetValueAsString(FLICK_PHOTO_MEDIA);

	//the original size if only available for pro user
	cFkrPhoto.szSource = m_pParser->GetValueAsString(FLICK_PHOTO_URL_O);
	cFkrPhoto.nHeight = atoi(m_pParser->GetValueAsString(FLICK_PHOTO_HEIGHT_O).c_str());
	cFkrPhoto.nWidth = atoi(m_pParser->GetValueAsString(FLICK_PHOTO_WIDTH_O).c_str());
	cFkrPhoto.szThumbNail = m_pParser->GetValueAsString(FLICK_PHOTO_URL_T);

	cFkrPhoto.pListImage = new CFkrImageList();
	std::list<string>::const_iterator it = S_LIST_FKRPHOTOSIZES.begin();
	for (;it!=S_LIST_FKRPHOTOSIZES.end();++it)
	{
		model::CFkrImage* pFkrImg = new model::CFkrImage();
		pFkrImg->szSource = m_pParser->GetValueAsString("%s%s",FLICK_PHOTO_URL,it->c_str());
		pFkrImg->nWidth = atoi(m_pParser->GetValueAsString("%s%s",FLICK_PHOTO_WIDTH,it->c_str()).c_str());
		pFkrImg->nHeight = atoi(m_pParser->GetValueAsString("%s%s",FLICK_PHOTO_HEIGHT,it->c_str()).c_str());
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
}

void util::CPhotoParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

const list<string> util::CPhotoParseRuler::S_LIST_FKRPHOTOSIZES = util::CListHelper::CreateFkrImgFormatList();


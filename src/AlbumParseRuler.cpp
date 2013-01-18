#include "stdafx.h"
#include "AlbumParseRuler.h"
#include "FkRAlbumModel.h"
#include "FBAlbumModel.h"
#include "FlickrFields.h"
#include "FBFields.h"
#include "StringHelper.h"

util::CAlbumListParseRuler::CAlbumListParseRuler()
{

}

util::CAlbumListParseRuler::CAlbumListParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CAlbumListParseRuler::Traverse( CFBAlbumList& cFBAlbumList )
{
	int nAlbumNum = m_jvRoot[FB_DATA].size();
	CAlbumParseRuler cAlbumParseRuler;
	for (int i = 0 ;i<nAlbumNum;++i)
	{
		CFBAlbum* pFbAlbum = new CFBAlbum();
		Json::Value jvItem = m_jvRoot[FB_DATA][i];
		cAlbumParseRuler.SetExecutor((void*)&jvItem);
		pFbAlbum->AcceptAlbumParser(cAlbumParseRuler);
		cFBAlbumList.items.push_back(pFbAlbum);
	}
	cFBAlbumList.szNextPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	cFBAlbumList.szPreviousPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

void util::CAlbumListParseRuler::Traverse( CFkrAlbumList& cFkrAlbumList )
{
	cFkrAlbumList.nPage = atoi(m_jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_PAGE].asString().c_str());
	cFkrAlbumList.nPages = atoi(m_jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_PAGES].asString().c_str());
	cFkrAlbumList.nPerpage = atoi(m_jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_PERPAGE].asString().c_str());
	cFkrAlbumList.nTotal = atoi(m_jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSETS_TOTAL].asString().c_str());

	CAlbumParseRuler cAlbumParseRuler;
	int nAlbums = m_jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSET].size();
	for (int i =0;i<nAlbums;++i)
	{
		Json::Value item = m_jvRoot[FLICK_PHOTOSETS][FLICK_PHOTOSET][i];
		cAlbumParseRuler.SetExecutor((void*)&item);
		model::CFkrAlbum* cFkrAlbum = new model::CFkrAlbum();
		cFkrAlbum->AcceptAlbumParser(cAlbumParseRuler);
		cFkrAlbumList.items.push_back(cFkrAlbum);
	}
}

void util::CAlbumListParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

util::CAlbumParseRuler::CAlbumParseRuler()
{

}

util::CAlbumParseRuler::CAlbumParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CAlbumParseRuler::Traverse( CFBAlbum& cFBAlbum )
{
	cFBAlbum.szId = m_jvRoot[FB_ID].asString();
	cFBAlbum.szName = m_jvRoot[FB_ALBUM_NAME].asString();
	cFBAlbum.szCoverPhotoId = m_jvRoot[FB_ALBUM_COVER_PHOTO].asString();
	cFBAlbum.nCount = m_jvRoot[FB_ALBUM_PHOTO_COUNT].asInt();
}

void util::CAlbumParseRuler::Traverse( CFkrAlbum& cFkrAlbum )
{
	cFkrAlbum.nCount = atoi(m_jvRoot[FLICK_PHOTOSET_VIDEOS].asString().c_str()) + 
									atoi(m_jvRoot[FLICK_PHOTOSET_PHOTOS].asString().c_str());
	cFkrAlbum.szCoverPhotoId = m_jvRoot[FLICK_PHOTOSET_PRIMARY].asString();
	cFkrAlbum.szDescription = m_jvRoot[FLICK_PHOTOSET_DESCRIPTION][FLICK_FIELD_CONTENT].asString();
	cFkrAlbum.szId = m_jvRoot[FLICK_PHOTOSET_ID].asString();
	cFkrAlbum.szTitle = m_jvRoot[FLICK_PHOTOSET_TITLE][FLICK_FIELD_CONTENT].asString();
	cFkrAlbum.szThumbNail = util::CStringHelper::Format("http://farm%s.staticflickr.com/%s/%s_%s_t.jpg",
		m_jvRoot[FLICK_PHOTOSET_FARM].asString().c_str(),
		m_jvRoot[FLICK_PHOTOSET_SERVER].asString().c_str(),
		cFkrAlbum.szCoverPhotoId.c_str(),
		m_jvRoot[FLICK_PHOTOSET_SECRET].asString().c_str());
}

void util::CAlbumParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

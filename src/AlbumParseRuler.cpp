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
	int nAlbumNum = m_pParser->GetValueAsArrarySize(FB_DATA);
	CAlbumParseRuler cAlbumParseRuler;
	cAlbumParseRuler.SetExecutor(m_pParser);
	for (int i = 0 ;i<nAlbumNum;++i)
	{
		CFBAlbum* pFbAlbum = new CFBAlbum();
		m_pParser->GetObjectAsRoot("%s.%d",FB_DATA,i);
		pFbAlbum->AcceptAlbumParser(cAlbumParseRuler);
		cFBAlbumList.items.push_back(pFbAlbum);
		m_pParser->ResetParseRoot();
	}
	cFBAlbumList.szNextPageUrl = m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_NEXT);
	cFBAlbumList.szPreviousPageUrl = m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_PREVIOUS);
}

void util::CAlbumListParseRuler::Traverse( CFkrAlbumList& cFkrAlbumList )
{
	cFkrAlbumList.nPage = atoi(m_pParser->GetValueAsString(FLICK_PHOTOSETS"."FLICK_PHOTOSETS_PAGE).c_str());
	cFkrAlbumList.nPages = atoi(m_pParser->GetValueAsString(FLICK_PHOTOSETS"."FLICK_PHOTOSETS_PAGES).c_str());
	cFkrAlbumList.nPerpage = atoi(m_pParser->GetValueAsString(FLICK_PHOTOSETS"."FLICK_PHOTOSETS_PERPAGE).c_str());
	cFkrAlbumList.nTotal = atoi(m_pParser->GetValueAsString(FLICK_PHOTOSETS"."FLICK_PHOTOSETS_TOTAL).c_str());

	CAlbumParseRuler cAlbumParseRuler;
	cAlbumParseRuler.SetExecutor(m_pParser);
	int nAlbums = m_pParser->GetValueAsArrarySize(FLICK_PHOTOSETS"."FLICK_PHOTOSET);
	for (int i =0;i<nAlbums;++i)
	{
		m_pParser->GetObjectAsRoot("%s.%s.%d",FLICK_PHOTOSETS,FLICK_PHOTOSET,i);		
		model::CFkrAlbum* cFkrAlbum = new model::CFkrAlbum();
		cFkrAlbum->AcceptAlbumParser(cAlbumParseRuler);
		cFkrAlbumList.items.push_back(cFkrAlbum);
		m_pParser->ResetParseRoot();
	}
}




void util::CAlbumListParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

void util::CAlbumListParseRuler::SetExecutor( IParser* pParser )
{
	m_pParser = pParser;
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
	cFBAlbum.szId = m_pParser->GetValueAsString(FB_ID);
	cFBAlbum.szName = m_pParser->GetValueAsString(FB_ALBUM_NAME);
	cFBAlbum.szCoverPhotoId = m_pParser->GetValueAsString(FB_ALBUM_COVER_PHOTO);
	cFBAlbum.nCount = m_pParser->GetValueAsInt(FB_ALBUM_PHOTO_COUNT);
}

void util::CAlbumParseRuler::Traverse( CFkrAlbum& cFkrAlbum )
{
	;
	cFkrAlbum.nCount = atoi(m_pParser->GetValueAsString(FLICK_PHOTOSET_VIDEOS).c_str()) + 
									atoi(m_pParser->GetValueAsString(FLICK_PHOTOSET_PHOTOS).c_str());
	cFkrAlbum.szCoverPhotoId = m_pParser->GetValueAsString(FLICK_PHOTOSET_PRIMARY);
	cFkrAlbum.szDescription = m_pParser->GetValueAsString(FLICK_PHOTOSET_DESCRIPTION"."FLICK_FIELD_CONTENT);
	cFkrAlbum.szId = m_pParser->GetValueAsString(FLICK_PHOTOSET_ID);
	cFkrAlbum.szTitle = m_pParser->GetValueAsString(FLICK_PHOTOSET_TITLE"."FLICK_FIELD_CONTENT);
	cFkrAlbum.szThumbNail = util::CStringHelper::Format("http://farm%s.staticflickr.com/%s/%s_%s_t.jpg",
		m_pParser->GetValueAsString(FLICK_PHOTOSET_FARM).c_str(),
		m_pParser->GetValueAsString(FLICK_PHOTOSET_SERVER).c_str(),
		cFkrAlbum.szCoverPhotoId.c_str(),
		m_pParser->GetValueAsString(FLICK_PHOTOSET_SECRET).c_str());
}

void util::CAlbumParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

void util::CAlbumParseRuler::SetExecutor( IParser* pParser )
{
	m_pParser = pParser;
}

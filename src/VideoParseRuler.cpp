#include "stdafx.h"
#include "VideoParseRuler.h"
#include "FBVideoModel.h"
#include "FlickrFields.h"
#include "FBFields.h"
#include "StringHelper.h"

util::CVideoListParseRuler::CVideoListParseRuler()
{

}

util::CVideoListParseRuler::CVideoListParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CVideoListParseRuler::Traverse( CFBVideoList& cFBVideoList )
{
	int nVideoNum = m_pParser->GetValueAsArrarySize(FB_DATA);
	CVideoParseRuler cVideoParseRuler;
	cVideoParseRuler.SetExecutor(m_pParser);
	m_pParser->StoreRoot();
	for (int i = 0 ;i<nVideoNum;++i)
	{
		m_pParser->GetObjectAsRoot("%s.%d",FB_DATA,i);
		CFBVideo* pFbVideo = new CFBVideo();
		pFbVideo->AcceptVideoParser(cVideoParseRuler);
		cFBVideoList.items.push_back(pFbVideo);
		m_pParser->RestoreRoot();
	}
	m_pParser->ClearBuffTop();
	cFBVideoList.szNextPageUrl =  m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_NEXT);
	cFBVideoList.szPreviousPageUrl = m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_PREVIOUS);
}

void util::CVideoListParseRuler::Traverse( CFkrVideoList& cFkrVideoList )
{
	//not implemented because of sepc
}

void util::CVideoListParseRuler::SetExecutor( void* pExecutor )
{
}

void util::CVideoListParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

util::CVideoParseRuler::CVideoParseRuler()
{

}

util::CVideoParseRuler::CVideoParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CVideoParseRuler::Traverse( CFBVideo& cFBVideo )
{
	cFBVideo.szId = m_pParser->GetValueAsString(FB_ID);
	cFBVideo.szSource = m_pParser->GetValueAsString(FB_VIDEO_SOURCE);
	cFBVideo.szThumbNail = m_pParser->GetValueAsString(FB_VIDEO_THUMBNAIL);
	cFBVideo.szEmbedHtml = m_pParser->GetValueAsString(FB_VIDEO_EMBED_HTML);

	CVideoFormatParseRuler cVideoFormatParseRuler;
	cVideoFormatParseRuler.SetExecutor(m_pParser);
	int nVideoFormat = m_pParser->GetValueAsArrarySize(FB_VIDEO_FORMAT);
	m_pParser->StoreRoot();
	for (int i = 0;i<nVideoFormat;++i)
	{
		m_pParser->GetObjectAsRoot("%s.%d",FB_VIDEO_FORMAT,i);
		CFBVideoFormat* pFbVideoFormat = new CFBVideoFormat();
		pFbVideoFormat->AcceptVideoFormatParser(cVideoFormatParseRuler);
		cFBVideo.listFormat.push_back(pFbVideoFormat);
		m_pParser->RestoreRoot();
	}
	m_pParser->ClearBuffTop();
}

void util::CVideoParseRuler::Traverse( CFkrVideo& cFkrVideo )
{
	//not implemented because of spec
}

void util::CVideoParseRuler::SetExecutor( void* pExecutor )
{
}

void util::CVideoParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

util::CVideoFormatParseRuler::CVideoFormatParseRuler()
{

}

util::CVideoFormatParseRuler::CVideoFormatParseRuler( void* pExecutor )
{
		this->SetExecutor(pExecutor);
}

void util::CVideoFormatParseRuler::Traverse( CFBVideoFormat& cFBVideoFormat )
{
	cFBVideoFormat.nHeight = m_pParser->GetValueAsInt(FB_VIDEO_HEIGHT);
	cFBVideoFormat.nWidth = m_pParser->GetValueAsInt(FB_VIDEO_WIDTH);
	cFBVideoFormat.szThumbNail = m_pParser->GetValueAsString(FB_VIDEO_THUMBNAIL);
	cFBVideoFormat.szEmbedHtml = m_pParser->GetValueAsString(FB_VIDEO_EMBED_HTML);
}

void util::CVideoFormatParseRuler::Traverse( CFkrVideoFormat& cFkrVideoFormat )
{
	//not implemented because of spec
}

void util::CVideoFormatParseRuler::SetExecutor( void* pExecutor )
{
}

void util::CVideoFormatParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

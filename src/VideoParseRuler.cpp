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
	int nVideoNum = m_jvRoot[FB_DATA].size();
	CVideoParseRuler cVideoParseRuler;
	for (int i = 0 ;i<nVideoNum;++i)
	{
		Json::Value jvItem = m_jvRoot[FB_DATA][i];
		cVideoParseRuler.SetExecutor((void*)&jvItem);
		CFBVideo* pFbVideo = new CFBVideo();
		pFbVideo->AcceptVideoParser(cVideoParseRuler);
		cFBVideoList.items.push_back(pFbVideo);
	}
	cFBVideoList.szNextPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	cFBVideoList.szPreviousPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

void util::CVideoListParseRuler::Traverse( CFkrVideoList& cFkrVideoList )
{
	//not implemented because of sepc
}

void util::CVideoListParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
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
	cFBVideo.szId = m_jvRoot[FB_ID].asString();
	cFBVideo.szSource = m_jvRoot[FB_VIDEO_SOURCE].asString();
	cFBVideo.szThumbNail = m_jvRoot[FB_VIDEO_THUMBNAIL].asString();
	cFBVideo.szEmbedHtml = m_jvRoot[FB_VIDEO_EMBED_HTML].asString();

	CVideoFormatParseRuler cVideoFormatParseRuler;
	int nVideoFormat = m_jvRoot[FB_VIDEO_FORMAT].size();
	for (int i = 0;i<nVideoFormat;++i)
	{
		Json::Value item = m_jvRoot[FB_VIDEO_FORMAT][i];
		cVideoFormatParseRuler.SetExecutor((void*)&item);
		CFBVideoFormat* pFbVideoFormat = new CFBVideoFormat();
		pFbVideoFormat->AcceptVideoFormatParser(cVideoFormatParseRuler);
		cFBVideo.listFormat.push_back(pFbVideoFormat);
	}
}

void util::CVideoParseRuler::Traverse( CFkrVideo& cFkrVideo )
{
	//not implemented because of spec
}

void util::CVideoParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
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
	cFBVideoFormat.nHeight = m_jvRoot[FB_VIDEO_HEIGHT].asInt();
	cFBVideoFormat.nWidth = m_jvRoot[FB_VIDEO_WIDTH].asInt();
	cFBVideoFormat.szThumbNail = m_jvRoot[FB_VIDEO_THUMBNAIL].asString();
	cFBVideoFormat.szEmbedHtml = m_jvRoot[FB_VIDEO_EMBED_HTML].asString();
}

void util::CVideoFormatParseRuler::Traverse( CFkrVideoFormat& cFkrVideoFormat )
{
	//not implemented because of spec
}

void util::CVideoFormatParseRuler::SetExecutor( void* pExecutor )
{
		m_jvRoot = * ((Json::Value*) pExecutor);
}

#include "stdafx.h"
#include "ImageParseRuler.h"
#include "FkRPhotoModel.h"
#include "FBPhotoModel.h"
#include "FlickrFields.h"
#include "FBFields.h"

util::CImageListParseRuler::CImageListParseRuler()
{

}

util::CImageListParseRuler::CImageListParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CImageListParseRuler::Traverse( CFBImageList& cFBImageList )
{
	int nImageNum = m_jvRoot.size();
	CImageParseRuler cImgRuler;
	for (int j = 0; j<nImageNum;++j)
	{
		Json::Value item = m_jvRoot[j];
		cImgRuler.SetExecutor((void*)&item);
		model::CFBImage* pIImage = new model::CFBImage();
		pIImage->AcceptImageParser(cImgRuler);
		cFBImageList.items.push_back(pIImage);
	}
}

void util::CImageListParseRuler::Traverse( CFkrImageList& cFkrImageList )
{

}

void util::CImageListParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

util::CImageParseRuler::CImageParseRuler()
{

}

util::CImageParseRuler::CImageParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CImageParseRuler::Traverse( CFBImage& cFBImage )
{
	cFBImage.nHeight = m_jvRoot[FB_IMAGE_HEIGHT].asInt();
	cFBImage.nWidth = m_jvRoot[FB_IMAGE_WIDTH].asInt();
	cFBImage.szSource = m_jvRoot[FB_IMAGE_SOURCE].asString();
}

void util::CImageParseRuler::Traverse( CFkrImage& cFkrImage )
{

}

void util::CImageParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

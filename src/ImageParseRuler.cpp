#include "stdafx.h"
#include "ImageParseRuler.h"
#include "FkRPhotoModel.h"
#include "FBPhotoModel.h"
#include "FlickrFields.h"
#include "FBFields.h"

util::CImageListParseRuler::CImageListParseRuler()
{

}

util::CImageListParseRuler::CImageListParseRuler( Json::Value& jvRoot )
{
	this->SetExecutor(jvRoot);
}

void util::CImageListParseRuler::Traverse( CFBImageList& cFBImageList )
{
	int nImageNum = m_jvRoot.size();
	CImageParseRuler cImgRuler;
	for (int j = 0; j<nImageNum;++j)
	{
		Json::Value item = m_jvRoot[j];
		cImgRuler.SetExecutor(item);
		model::CFBImage* pIImage = new model::CFBImage();
		pIImage->AcceptImageParser(cImgRuler);
		cFBImageList.listOfItem.push_back(pIImage);
	}
}

void util::CImageListParseRuler::Traverse( CFkrImageList& cFkrImageList )
{

}

void util::CImageListParseRuler::SetExecutor( Json::Value& jvRoot )
{
	m_jvRoot = jvRoot;
}

util::CImageParseRuler::CImageParseRuler()
{

}

util::CImageParseRuler::CImageParseRuler( Json::Value& jvRoot )
{
	this->SetExecutor(jvRoot);
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

void util::CImageParseRuler::SetExecutor( Json::Value& jvRoot )
{
	m_jvRoot = jvRoot;
}

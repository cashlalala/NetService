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
	int nImageNum = m_pParser->GetValueAsArrarySize(FB_PHOTO_IMAGES);
	CImageParseRuler cImgRuler;
	cImgRuler.SetExecutor(m_pParser);
	m_pParser->StoreRoot();
	for (int j = 0; j<nImageNum;++j)
	{
		m_pParser->GetObjectAsRoot("%s.%d",FB_PHOTO_IMAGES,j);
		model::CFBImage* pIImage = new model::CFBImage();
		pIImage->AcceptImageParser(cImgRuler);
		cFBImageList.items.push_back(pIImage);
		m_pParser->RestoreRoot();
	}
	m_pParser->ClearBuffTop();
}

void util::CImageListParseRuler::Traverse( CFkrImageList& cFkrImageList )
{

}

void util::CImageListParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

void util::CImageListParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
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
	cFBImage.nHeight = m_pParser->GetValueAsInt(FB_IMAGE_HEIGHT);
	cFBImage.nWidth = m_pParser->GetValueAsInt(FB_IMAGE_WIDTH);
	cFBImage.szSource = m_pParser->GetValueAsString(FB_IMAGE_SOURCE);
}

void util::CImageParseRuler::Traverse( CFkrImage& cFkrImage )
{

}

void util::CImageParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = * ((Json::Value*) pExecutor);
}

void util::CImageParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

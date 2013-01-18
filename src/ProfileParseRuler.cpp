#include "stdafx.h"
#include "ProfileParseRuler.h"
#include "NetServiceErr.h"
#include "FlickrFields.h"
#include "FBFields.h"
#include "FBUserModel.h"
#include "FkrUserModel.h"

int util::CProfileParseRuler::Traverse( CFkrProfile& cFkrErr )
{
	//done by Query user info, the size of thumbnail of Flickr is the same
	return S_OK;
}

int util::CProfileParseRuler::Traverse( CFBProfile& cFBErr )
{
	int nSize = m_jvRoot[FB_DATA].size();
	if (nSize==1)
	{
		cFBErr.szThumNail = m_jvRoot[FB_DATA][0][FB_PROFILE_PIC].asString();
		cFBErr.szBig = m_jvRoot[FB_DATA][0][FB_PROFILE_PIC_BIG].asString();
		cFBErr.szSmall = m_jvRoot[FB_DATA][0][FB_PROFILE_PIC_SMALL].asString();
		cFBErr.szSquare = m_jvRoot[FB_DATA][0][FB_PROFILE_PIC_SQUARE].asString();
		return S_OK;
	}
	else
		return NS_E_DMGR_WRONG_DATA_SIZE;
}

util::CProfileParseRuler::CProfileParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CProfileParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = *((Json::Value*) pExecutor);
}


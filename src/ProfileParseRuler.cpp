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
	int nSize = m_pParser->GetValueAsArrarySize(FB_DATA);
	if (nSize==1)
	{
		cFBErr.szThumNail = m_pParser->GetValueAsString("%s.%d.%s",FB_DATA,0,FB_PROFILE_PIC);
		cFBErr.szBig = m_pParser->GetValueAsString("%s.%d.%s",FB_DATA,0,FB_PROFILE_PIC_BIG);
		cFBErr.szSmall = m_pParser->GetValueAsString("%s.%d.%s",FB_DATA,0,FB_PROFILE_PIC_SMALL);
		cFBErr.szSquare = m_pParser->GetValueAsString("%s.%d.%s",FB_DATA,0,FB_PROFILE_PIC_SQUARE);
		return S_OK;
	}
	else
		return NS_E_DMGR_WRONG_DATA_SIZE;
}

util::CProfileParseRuler::CProfileParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

util::CProfileParseRuler::CProfileParseRuler()
{

}

void util::CProfileParseRuler::SetExecutor( void* pExecutor )
{
}

void util::CProfileParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}


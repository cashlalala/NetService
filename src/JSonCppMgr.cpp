#include "StdAfx.h"
#include "JSonCppMgr.h"
#include "FacebookFields.h"
#include "FacebookPhotoModel.h"
#include <sstream>
#include <json/json.h>

using std::stringstream;
using util::CJsonCppMgr;

CJsonCppMgr::CJsonCppMgr(void)
{
}

CJsonCppMgr::~CJsonCppMgr(void)
{
}

int util::CJsonCppMgr::ParsePhotoList( string szInput, IPhotoList& iPhotoList, EnDataOwner enDataOwner  ) 
{
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		switch(enDataOwner)
		{
		case Facebook:
			TravFBPhotoList(jvRoot, iPhotoList);
			break;
		case Flickr:
			break;
		default:
			break;
		}
		return 0;
	}
	else
		return 1;
}

int util::CJsonCppMgr::ParsePhoto( string szInput, IPhoto& iPhoto, EnDataOwner enDataOwner  ) 
{
	return 0;
}

void util::CJsonCppMgr::TravFBPhotoList( Json::Value &jvRoot, IPhotoList &iPhotoList )
{
	int nPhotoNum = jvRoot[FB_DATA].size();
	for (int i=0;i<nPhotoNum;++i)
	{
		Json::Value item = jvRoot[FB_DATA][i];
		model::CFacebookPhoto cFbPhot;
		cFbPhot.id = item[FB_ID].asString();
		cFbPhot.nHeight = item[FB_IMAGE_HEIGHT].asInt();
		cFbPhot.nWidth = item[FB_IMAGE_WIDTH].asInt();
		cFbPhot.szlink = item[FB_PHOTO_LINK].asString();
		cFbPhot.szSource = item[FB_IMAGE_SOURCE].asString();
		iPhotoList.push_back(cFbPhot);
	}
}

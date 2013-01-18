#include "StdAfx.h"
#include "ListHelper.h"

#include "FlickrFields.h"

using namespace util;

list<string> CListHelper::CreateFkrImgFormatList()
{
	list<string> listResult;
	listResult.push_back(FLICK_PHOTO_SQ);
	listResult.push_back(FLICK_PHOTO_T);
	listResult.push_back(FLICK_PHOTO_S);
	listResult.push_back(FLICK_PHOTO_Q);
	listResult.push_back(FLICK_PHOTO_M);
	listResult.push_back(FLICK_PHOTO_N);
	listResult.push_back(FLICK_PHOTO_Z);
	listResult.push_back(FLICK_PHOTO_C);
	listResult.push_back(FLICK_PHOTO_L);
	listResult.push_back(FLICK_PHOTO_O);
	return listResult;
}

#include "StdAfx.h"
#include "FBPhotoModel.h"

model::CFBPhoto::~CFBPhoto( void )
{
	for (list<IImage*>::iterator it = listImages.begin();it!=listImages.end();++it)
	{
		NETSERV_SAFE_DELETE(*it);
	}
	listImages.clear();
}

model::CFBPhotoList::~CFBPhotoList( void )
{
	for (list<IPhoto*>::iterator it = listPhoto.begin();it!=listPhoto.end();++it)
	{
		NETSERV_SAFE_DELETE(*it);
	}
	listPhoto.clear();
}

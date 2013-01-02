#include "StdAfx.h"
#include "FacebookPhotoModel.h"

model::CFacebookPhoto::~CFacebookPhoto( void )
{
	for (list<IImage*>::iterator it = listImages.begin();it!=listImages.end();++it)
	{
		NETSERV_SAFE_DELETE(*it);
	}
	listImages.clear();
}

model::CFacebookPhotoList::~CFacebookPhotoList( void )
{
	for (list<IPhoto*>::iterator it = listPhoto.begin();it!=listPhoto.end();++it)
	{
		NETSERV_SAFE_DELETE(*it);
	}
	listPhoto.clear();
}

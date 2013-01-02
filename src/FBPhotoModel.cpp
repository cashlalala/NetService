#include "StdAfx.h"
#include "FBPhotoModel.h"

model::CFBPhoto::~CFBPhoto( void )
{
	NETSERV_LIST_SAFE_DELETE(list<IImage*>,listImages)
}

model::CFBPhotoList::~CFBPhotoList( void )
{
	NETSERV_LIST_SAFE_DELETE(list<IPhoto*>,listPhoto)
}

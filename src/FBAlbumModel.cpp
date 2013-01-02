#include "StdAfx.h"
#include "FBAlbumModel.h"
#include <list>

using std::list;

model::CFBAlbum::CFBAlbum(void)
{
	nCount = 0;
}

model::CFBAlbum::~CFBAlbum(void)
{
}

model::CFBAlbumList::CFBAlbumList( void )
{

}

model::CFBAlbumList::~CFBAlbumList( void )
{
	NETSERV_LIST_SAFE_DELETE(list<IAlbum*>,listAlbum)
}

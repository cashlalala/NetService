#include "StdAfx.h"
#include "FBVideoModel.h"

model::CFBVideo::CFBVideo(void)
{
}

model::CFBVideo::~CFBVideo(void)
{
	NETSERV_LIST_SAFE_DELETE(list<IVideoFormat*>,listFormat)
}

model::CFBVideoFormat::~CFBVideoFormat( void )
{
	
}

model::CFBVideoFormat::CFBVideoFormat( void )
{

}

model::CFBVideoList::~CFBVideoList( void )
{
	NETSERV_LIST_SAFE_DELETE(list<IVideo*>,listVideo)
}

model::CFBVideoList::CFBVideoList( void )
{

}

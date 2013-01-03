#pragma once

#include "IAlbumModel.h"


namespace model
{
	struct CFBAlbum :
		public IAlbum
	{
		virtual ~CFBAlbum(void){};
	};

	struct CFBAlbumList :
		public IAlbumList	
	{
		virtual ~CFBAlbumList(void){};
	};
}


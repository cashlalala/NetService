#pragma once

#include "IAlbumModel.h"


namespace model
{
	class CFBAlbum :
		public IAlbum
	{
	public:
		CFBAlbum(void);
		virtual ~CFBAlbum(void);
	};

	class CFBAlbumList :
		public IAlbumList	
	{
	public:
		CFBAlbumList(void);
		virtual ~CFBAlbumList(void);
	};
}


#pragma once

#include "IAlbumModel.h"


namespace model
{
	struct CFBAlbum :
		public IAlbum
	{
		virtual ~CFBAlbum(void){};
		void AcceptAlbumParser(IAlbumParseRuler& cAlbumParser) {cAlbumParser.Traverse(*this);}
	};

	struct CFBAlbumList :
		public IAlbumList	
	{
		virtual ~CFBAlbumList(void){};
		void AcceptAlbumListParser(IAlbumListParseRuler& cAlbumListParser) {cAlbumListParser.Traverse(*this);}
	};
}


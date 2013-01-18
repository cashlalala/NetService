#pragma once

#include "IAlbumModel.h"


namespace model
{
	struct CFkrAlbum :
		public IAlbum
	{
		virtual ~CFkrAlbum(void){};
		string szTitle;
		string szDescription;
		void AcceptAlbumParser(IAlbumParseRuler& cAlbumParser) { cAlbumParser.Traverse(*this);}
	};

	struct CFkrAlbumList :
		public IAlbumList	
	{
		CFkrAlbumList(): nPage(0), nPages(0), nTotal(0){};
		virtual ~CFkrAlbumList(void){};
		int nPage;
		int nPages;
		int nPerpage;
		int nTotal; 
		void AcceptAlbumListParser(IAlbumListParseRuler& cAlbumListParser)  {cAlbumListParser.Traverse(*this);}
	};
}


#pragma once
#include "IParseRuler.h"
#include "IParser.h"
#include <json/json.h>

namespace util
{
	class CAlbumListParseRuler : public IAlbumListParseRuler 
	{
	public:
		CAlbumListParseRuler();

		CAlbumListParseRuler(IParser* pExecutor);

		virtual void Traverse( CFBAlbumList& cFBAlbumList ) ;

		virtual void Traverse( CFkrAlbumList& cFkrAlbumList ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pParser);
	private:
		IParser* m_pParser;
	};

	class CAlbumParseRuler : public IAlbumParseRuler 
	{
	public:
		CAlbumParseRuler();

		CAlbumParseRuler(IParser* pExecutor);

		virtual void Traverse( CFBAlbum& cFBAlbum ) ;

		virtual void Traverse( CFkrAlbum& cFkrAlbum ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pParser);
	private:
		IParser* m_pParser;
	};
}
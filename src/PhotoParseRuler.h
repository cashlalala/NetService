#pragma once
#include "IParseRuler.h"
#include "IParser.h"
#include <json/json.h>
#include <string>
#include <list>

using std::string;
using std::list;

namespace util
{
	class CPhotoListParseRuler : public IPhotoListParseRuler 
	{
	public:
		CPhotoListParseRuler();

		CPhotoListParseRuler(void* pExecutor);

		virtual void Traverse( CFBPhotoList& cFBPhotoList ) ;

		virtual void Traverse( CFkrPhotoList& cFkrPhotoList ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor);
	private:
		IParser* m_pParser;
	};

	class CPhotoParseRuler : public IPhotoParseRuler 
	{
	public:
		CPhotoParseRuler();

		CPhotoParseRuler(void* pExecutor);

		virtual void Traverse( CFBPhoto& cFBPhoto ) ;

		virtual void Traverse( CFkrPhoto& cFkrPhoto ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor);
	private:
		IParser* m_pParser;
		static const list<string> S_LIST_FKRPHOTOSIZES;
	};
}
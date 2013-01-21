#pragma  once
#include "IParseRuler.h"
#include "IParser.h"
#include <json/json.h>

namespace util
{
	class CProfileParseRuler : public IProfileParseRuler 
	{
	public:
		CProfileParseRuler();

		CProfileParseRuler(void* pExecutor);

		virtual int Traverse( CFBProfile& cFBProfile ) ;

		virtual int Traverse( CFkrProfile& cFkrProfile ) ;

		virtual void SetExecutor(void* pExecutor);

		virtual void SetExecutor(IParser* pExecutor);
	private:
		IParser* m_pParser;
	};
}


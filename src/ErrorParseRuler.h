#pragma  once
#include "IParseRuler.h"
#include "IParser.h"
#include <json/json.h>

namespace util
{
	class CErrorParseRuler : public IErrorParseRuler 
	{
	public:
		CErrorParseRuler(void* pExecutor);

		virtual int Traverse( CFBError& cFkrErr ) ;

		virtual int Traverse( CFkrError& cFBErr ) ;

		virtual void SetExecutor(void* pExecutor);

		virtual void SetExecutor(IParser* pExecutor);
	private:
		IParser* m_pParser;

		Json::Value m_jvRoot;
	};
}


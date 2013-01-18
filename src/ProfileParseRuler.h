#pragma  once
#include "IParseRuler.h"
#include <json/json.h>

namespace util
{
	class CProfileParseRuler : public IProfileParseRuler 
	{
	public:
		CProfileParseRuler(void* pExecutor);

		virtual int Traverse( CFBProfile& cFBProfile ) ;

		virtual int Traverse( CFkrProfile& cFkrProfile ) ;

		virtual void SetExecutor(void* pExecutor);
	private:
		Json::Value m_jvRoot;
	};
}


#pragma  once
#include "IParseRuler.h"
#include <json/json.h>

namespace util
{
	class CErrorParseRuler : public IErrorParseRuler 
	{
	public:
		CErrorParseRuler(Json::Value& jvRoot);

		virtual int Traverse( CFBError& cFkrErr ) ;

		virtual int Traverse( CFkrError& cFBErr ) ;

		virtual void SetExecutor(Json::Value& jvRoot);
	private:
		Json::Value m_jvRoot;
	};
}


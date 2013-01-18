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
	private:
		Json::Value m_jvRoot;
	};
}


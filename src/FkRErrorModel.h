#pragma once
#include "IErrorModel.h"

namespace model
{

	struct CFkrError :
		public IError
	{
		virtual ~CFkrError(void) {};
		int AcceptErrorParser(util::IErrorParseRuler& errParse) { return errParse.Traverse(*this);};
		string szStat;
	};

}



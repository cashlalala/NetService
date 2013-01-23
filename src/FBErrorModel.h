#pragma once
#include "IErrorModel.h"

namespace model
{

	struct CFBError :
		public IError
	{
		virtual ~CFBError(void) {};
		int AcceptErrorParser(util::IErrorParseRuler& errParse) { return errParse.Traverse(*this);};
	};

}



#pragma once
#include "IErrorModel.h"

namespace model
{

	struct CFkRError :
		public IError
	{
		virtual ~CFkRError(void) {};
		string szStat;
	};

}



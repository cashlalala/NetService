#pragma once
#include "IErrorModel.h"

namespace model
{

	struct CFkrError :
		public IError
	{
		virtual ~CFkrError(void) {};
		string szStat;
	};

}



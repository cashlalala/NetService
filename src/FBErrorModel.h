#pragma once

#include "IErrorModel.h"

namespace model
{

	class CFBError :
		public IError
	{
	public:
		CFBError(void);
		virtual ~CFBError(void);
	};

}



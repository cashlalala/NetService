#pragma once

#include "IDataParser.h"

namespace util
{
	class CDataParserFactory
	{
	public:
		static IDataParser* GetInstance(EnParser enParser = Json);
	};
}



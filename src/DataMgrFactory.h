#pragma once

#include "IDataManager.h"

namespace util
{
	class CDataMgrFactory
	{
	public:
		static IDataManager* GetInstance(EnDataMgr enParser = BoostJson);
	};
}



#pragma once
#include "IDataManager.h"
#include <map>
#include <typeinfo>

using std::map;

namespace util
{
	class CDataMgrFactory
	{
	public:
		static IDataManager* GetInstance(EnDataMgr enParser = BoostJson);
		//static int DeleteInstance(IDataManager* pIDataMgr); 

	private:
		//static map<EnDataMgr, IDataManager*> S_MAP_DATAMGR;
	};
}



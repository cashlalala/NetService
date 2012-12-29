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
		static int DeleteInstance(IDataManager* pIDataMgr); 

		static void RemoveSingleInstanceFromMap( map<EnDataMgr,IDataManager*>::iterator& it );



	private:
		static void CleanSingleInstance( IDataManager* pIDataMgr , int& nResuilt );
		static map<EnDataMgr, IDataManager*> S_MAP_DATAMGR;
	};
}



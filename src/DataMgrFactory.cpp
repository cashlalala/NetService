#include "StdAfx.h"
#include "DataMgrFactory.h"
#include "JSonCppMgr.h"
#include "NetServiceErr.h"

#include <map>

using std::map;
using namespace util;

map<EnDataMgr, IDataManager*> CDataMgrFactory::S_MAP_DATAMGR;

IDataManager* CDataMgrFactory::GetInstance( EnDataMgr enDataMgr /*= BoostJson*/ )
{
	IDataManager* pIDataMgr =  S_MAP_DATAMGR[enDataMgr];
	if (!pIDataMgr)
	{
		switch (enDataMgr)
		{
		case JsonCpp:
			pIDataMgr= new CJsonCppMgr();
			break;
		}
		S_MAP_DATAMGR[enDataMgr] = pIDataMgr;
	}
	return pIDataMgr;
	return  new CJsonCppMgr();
}

int util::CDataMgrFactory::DeleteInstance( IDataManager* pIDataMgr )
{
	int nResuilt = E_FAIL;
	map<EnDataMgr,IDataManager*>::iterator it = S_MAP_DATAMGR.begin();
	for (;it!=S_MAP_DATAMGR.end();++it)
	{
		if (pIDataMgr == it->second)
		{
			delete it->second;
			it->second = NULL;
			S_MAP_DATAMGR.erase(it);
			nResuilt = S_OK;
			break;
		}
	}
	return nResuilt;
}
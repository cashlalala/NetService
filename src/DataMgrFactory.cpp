#include "StdAfx.h"
#include "DataMgrFactory.h"
#include "JSonCppMgr.h"

#include <map>

using std::map;
using util::CJsonCppMgr;
using util::IDataManager;
using util::CDataMgrFactory;
using util::EnDataMgr;

IDataManager* CDataMgrFactory::GetInstance( EnDataMgr enDataMgr /*= BoostJson*/ )
{
	static map<EnDataMgr,IDataManager*> smapMgrs;
	IDataManager* pIDataMgr =  smapMgrs[enDataMgr];
	if (!pIDataMgr)
	{
		switch (enDataMgr)
		{
		case BoostJson:
			pIDataMgr = new CJsonCppMgr();
			break;
		}
		smapMgrs[enDataMgr] = pIDataMgr;
	}
	return pIDataMgr;
}

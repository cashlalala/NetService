#pragma once


#include "ISocialNetworkService.h"
#include <map>
#include <list>

using std::map;
using std::list;

class CSocialServiceFactory
{
public:
	static ISocialNetworkService* GetInstance(EnServiceType enServTp);
	static list<ISocialNetworkService*> GetAllServices();
	static void CloseServices();
	static int DeleteInstance( ISocialNetworkService* pISNS );

private:
	CSocialServiceFactory(void);
	~CSocialServiceFactory(void);
	
	static map<EnServiceType,ISocialNetworkService*> S_MAP_SERVICES;
};

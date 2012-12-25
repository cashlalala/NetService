#pragma once

#include "ISocialNetworkService.h"
#include <map>
#include <list>

using std::map;
using std::list;

typedef enum {
	FACEBOOK = 0,
	FLICKR = 1
} EnServiceType;

class CSocialServiceFactory
{
public:
	static ISocialNetworkService* GetService(EnServiceType enServTp);
	static list<ISocialNetworkService*> GetAllServices();

private:
	CSocialServiceFactory(void);
	~CSocialServiceFactory(void);
	static map<EnServiceType,ISocialNetworkService*> m_mapServices;

};

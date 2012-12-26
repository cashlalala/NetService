#include "StdAfx.h"
#include "SocialServiceFactory.h"
#include "FacebookService.h"


map<EnServiceType,ISocialNetworkService*> CSocialServiceFactory::m_mapServices;

CSocialServiceFactory::CSocialServiceFactory(void)
{
}

CSocialServiceFactory::~CSocialServiceFactory(void)
{
}

ISocialNetworkService* CSocialServiceFactory::GetService( EnServiceType enServTp )
{
	ISocialNetworkService* pInst = m_mapServices[enServTp];
	if (pInst == NULL)
	{
		switch (enServTp)
		{
		case FACEBOOK:
			pInst = new CFacebookService();
			break;
		case FLICKR:
			break;
		default:
			break;
		}
		m_mapServices[enServTp] = pInst;
	}
	return pInst;
}

list<ISocialNetworkService*> CSocialServiceFactory::GetAllServices()
{
	list<ISocialNetworkService*> listISNServ;
	map<EnServiceType,ISocialNetworkService*>::iterator it = m_mapServices.begin();
	for (;it!=m_mapServices.end();++it)
	{
		listISNServ.push_back(it->second);
	}
	return listISNServ;
}


void CSocialServiceFactory::CloseServices()
{
	map<EnServiceType,ISocialNetworkService*>::iterator it = m_mapServices.begin();
	for (;it!=m_mapServices.end();++it)
	{
		void* pRaw = NULL;
		if (pRaw = dynamic_cast<CFacebookService*> (it->second))
		{
			CFacebookService* pInst = (CFacebookService*) pRaw;
			delete pInst;
			pInst =  NULL;
			it->second = NULL;
		}
	}
}

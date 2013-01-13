#include "StdAfx.h"
#include "SocialServiceFactory.h"
#include "FacebookService.h"
#include "FlickrService.h"


map<EnServiceType,ISocialNetworkService*> CSocialServiceFactory::S_MAP_SERVICES;

CSocialServiceFactory::CSocialServiceFactory(void)
{
}

CSocialServiceFactory::~CSocialServiceFactory(void)
{
}

ISocialNetworkService* CSocialServiceFactory::GetSingletonInstance( EnServiceType enServTp )
{
	if ( NULL == S_MAP_SERVICES[enServTp] )
	{
		switch (enServTp)
		{
		case FACEBOOK:
			{
				static CFacebookService cFbServicePrototype;
				S_MAP_SERVICES[enServTp] = &cFbServicePrototype;
			}
			break;
		case FLICKR:
			{
				static CFlickrService cFkrServicePrototype;
				S_MAP_SERVICES[enServTp] =  &cFkrServicePrototype;
			}
			break;
		default:
			break;
		}
	}
	return S_MAP_SERVICES[enServTp];
}

list<ISocialNetworkService*> CSocialServiceFactory::GetAllServices()
{
	list<ISocialNetworkService*> listISNServ;
	map<EnServiceType,ISocialNetworkService*>::iterator it = S_MAP_SERVICES.begin();
	for (;it!=S_MAP_SERVICES.end();++it)
	{
		listISNServ.push_back(it->second);
	}
	return listISNServ;
}


void CSocialServiceFactory::CloseServices()
{
	map<EnServiceType,ISocialNetworkService*>::iterator it = S_MAP_SERVICES.begin();
	for (;it!=S_MAP_SERVICES.end();++it)
	{
		delete it->second;
		it->second = NULL;
	}
	S_MAP_SERVICES.clear();
}

//int CSocialServiceFactory::DeleteInstance( ISocialNetworkService* pISNS )
//{
//	int nResuilt = E_FAIL;
//	map<EnServiceType,ISocialNetworkService*>::iterator it = S_MAP_SERVICES.begin();
//	for (;it!=S_MAP_SERVICES.end();++it)
//	{
//		if (pISNS == it->second)
//		{
//			delete it->second;
//			it->second = NULL;
//			S_MAP_SERVICES.erase(it);
//			nResuilt = S_OK;
//			break;
//		}
//	}
//	return nResuilt;
//}
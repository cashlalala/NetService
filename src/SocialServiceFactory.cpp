#include "StdAfx.h"
#include "SocialServiceFactory.h"
#include "FacebookService.h"




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
		case EnServiceType::FACEBOOK:
			pInst = new CFacebookService();
			break;
		case EnServiceType::FLICKR:
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

#include "stdafx.h"
#include "LoggerMgr.h"
#include "Log4CxxLogger.h"

#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx::xml;

std::map<string,util::ILogger*> util::CLoggerMgr::S_MAP_LOGGER;

void util::CLoggerMgr::Config( EnLogger enLogger)
{
	if (!bIsLoggerConfiged)
	{
		switch (enLogger)
		{
		case Log4Cxx:
			DOMConfigurator::configure("Log4cxxConfig.xml");
			break;
		default:
			break;
		}
		bIsLoggerConfiged = true; // this line should be made to thread-safe, because you can't control the usages of end users
	}
}

util::ILogger* util::CLoggerMgr::GetLogger( EnLogger enLogger, const std::string& szName )
{
	ILogger* pILogger = CLoggerMgr::S_MAP_LOGGER[szName];
	switch (enLogger)
	{
	case Log4Cxx:
		{
			if (!pILogger)
				pILogger =  new util::CCxxLogger(szName); // this line should be made to thread-safe
			break;
		}
	default:
		break;
	}
	CLoggerMgr::S_MAP_LOGGER[szName] = pILogger;
	return pILogger;
}

void util::CLoggerMgr::CleanLoggers()
{
	for (std::map<string,ILogger*>::iterator it = S_MAP_LOGGER.begin();it!=S_MAP_LOGGER.end();++it)
	{
		if (it->second)
		{
			delete it->second; // this line should be made to thread-safe
			it->second = NULL; // this line should be made to thread-safe
		}
	}
	S_MAP_LOGGER.clear(); // this line should be made to thread-safe
}

#pragma once
#include "ILogger.h"

#include <string>
#include <map>

#include <log4cxx/logger.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

namespace util
{
	class CCxxLogger : public ILogger 
	{
	public:
		CCxxLogger(const std::string& szName);

		virtual ~CCxxLogger();

		virtual void Debug( const string& szMsg );

		virtual void Info( const string& szMsg );

		virtual void Error(const string& szMsg) ;
	private:
		LoggerPtr m_pCurrentLogger;
	};
}

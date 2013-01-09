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

		virtual void Trace(const char* lpszFormat, ...);

		virtual void Debug( const char* lpszFormat, ... );

		virtual void Info( const char* lpszFormat, ... );

		virtual void Error(const char* lpszFormat, ...) ;
	private:
		char* MsgFormat(const char* lpszFormat, va_list args);
		LoggerPtr m_pCurrentLogger;
	};
}

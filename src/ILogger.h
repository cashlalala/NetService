#pragma once

#include <string>

using std::string;

namespace util
{
	typedef enum{
		Log4Cxx,
		DefaultLog
	} EnLogger;

	struct ILogger {

		virtual ~ILogger(){} ;

		virtual void Debug(const char* lpszFormat, ...) = 0;

		virtual void Info(const char* lpszFormat, ...) = 0;

		virtual void Error(const char* lpszFormat, ...) = 0;
	};
}


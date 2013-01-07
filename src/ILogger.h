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

		virtual void Debug(const string& szMsg) = 0;

		virtual void Info(const string& szMsg) = 0;

		virtual void Error(const string& szMsg) = 0;
	};
}


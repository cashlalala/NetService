#pragma once

#include <string>
#include <map>

#include "ILogger.h"

namespace util
{

	class CLoggerMgr
	{
	public:
		//A configured method which should be called at the begin of process
		static void Config( EnLogger enLogger);

		//The gotten logger will be automatically cleaned at the end of the process if you manually called the CleanLoggers function.
		//The Cxx logger self is thread-safe.
		//If you want to implement a customized logger, please keep an eye on thread-safety
		static ILogger* GetLogger(EnLogger enLogger, const std::string& szName);
		
		//A clean method which should be called at the end of process
		static void CleanLoggers();
	private:
		//Logger records for deleting instances,
		//loggers life cycle should be as long as the program because you can never know how many times 
		//the class who owns the logger would be instantiated.
		//This work is done by log4cxx itself, but, somehow, the logger wrapper isn't. So we do this compromise.
		static std::map<string,ILogger*> S_MAP_LOGGER;
	};
}

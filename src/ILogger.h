#pragma once

#include <string>

using std::string;

#define LOGGER_SETLOCATIONINFO(pLogger,file,func,line) {\
	pLogger->lpcszFileName=file;\
	pLogger->lpcszFuncName=func;\
	pLogger->nLineNum=line;}

#if defined(_MSC_VER) && _MSC_VER >= 1300
#define __LOGGERFUNC__	 __FUNCSIG__
#endif
#if !defined(__LOGGERFUNC__)
#define __LOGGERFUNC__ ""
#endif

//for future thread safe
#define BEGIN_LOG(pLogger) \
	LOGGER_SETLOCATIONINFO(pLogger,__FILE__,__LOGGERFUNC__,__LINE__)

//for future thread safe
#define END_LOG(pLogger) \
	LOGGER_SETLOCATIONINFO(pLogger,"","",0)

#define LOGGER_ERROR(pLogger, ...) {\
	BEGIN_LOG(pLogger)\
	pLogger->Error(__VA_ARGS__);\
	END_LOG(pLogger)}

#define LOGGER_INFO(pLogger, ...) {\
	BEGIN_LOG(pLogger)\
	pLogger->Info(__VA_ARGS__);\
	END_LOG(pLogger)}

#define LOGGER_DEBUG(pLogger, ...) {\
	BEGIN_LOG(pLogger)\
	pLogger->Debug(__VA_ARGS__);\
	END_LOG(pLogger)}

#define LOGGER_TRACE(pLogger, ...) {\
	BEGIN_LOG(pLogger)\
	pLogger->Trace(__VA_ARGS__);\
	END_LOG(pLogger)}


namespace util
{
	typedef enum{
		Log4Cxx,
		DefaultLog
	} EnLogger;

	struct ILogger {

		const char* lpcszFileName;

		int nLineNum;

		const char* lpcszFuncName;

		virtual ~ILogger(){} ;

		virtual void Trace(const char* lpszFormat, ...) = 0;

		virtual void Debug(const char* lpszFormat, ...) = 0;

		virtual void Info(const char* lpszFormat, ...) = 0;

		virtual void Error(const char* lpszFormat, ...) = 0;
	};
}


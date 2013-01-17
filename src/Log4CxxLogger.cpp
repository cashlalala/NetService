#include "stdafx.h"
#include "Log4CxxLogger.h"

#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx::xml;

#define CUSTOM_LOCATION ::log4cxx::spi::LocationInfo(this->lpcszFileName, \
																							this->lpcszFuncName,\
																							this->nLineNum)

#define CUSTOM_ERROR(logger, message) { \
	if (logger->isErrorEnabled()) {\
	::log4cxx::helpers::MessageBuffer oss_; \
	logger->forcedLog(::log4cxx::Level::getError(), oss_.str(oss_ << message), CUSTOM_LOCATION); }}

#define CUSTOM_INFO(logger, message) { \
	if (logger->isInfoEnabled()) {\
	::log4cxx::helpers::MessageBuffer oss_; \
	logger->forcedLog(::log4cxx::Level::getInfo(), oss_.str(oss_ << message), CUSTOM_LOCATION); }}

#define CUSTOM_DEBUG(logger, message) { \
	if (LOG4CXX_UNLIKELY(logger->isDebugEnabled())) {\
	::log4cxx::helpers::MessageBuffer oss_; \
	logger->forcedLog(::log4cxx::Level::getDebug(), oss_.str(oss_ << message), CUSTOM_LOCATION); }}

#define CUSTOM_TRACE(logger, message) { \
	if (LOG4CXX_UNLIKELY(logger->isTraceEnabled())) {\
	::log4cxx::helpers::MessageBuffer oss_; \
	logger->forcedLog(::log4cxx::Level::getTrace(), oss_.str(oss_ << message), CUSTOM_LOCATION); }}


util::CCxxLogger::CCxxLogger( const std::string& szName )
{
	m_pCurrentLogger = Logger::getLogger( szName);
	lpcszFileName = "";
	lpcszFuncName = "";
    nLineNum = 0;
}

util::CCxxLogger::~CCxxLogger()
{
}

void util::CCxxLogger::Debug( const char* lpszFormat, ... )
{	
	va_list args;
	va_start(args, lpszFormat);
	char* lpszMsg = MsgFormat(lpszFormat,args);
	CUSTOM_DEBUG(m_pCurrentLogger,lpszMsg);
	va_end(args);
	free(lpszMsg);
}

void util::CCxxLogger::Info( const char* lpszFormat, ... )
{
	va_list args;
	va_start(args, lpszFormat);
	char* lpszMsg = MsgFormat(lpszFormat,args);
	CUSTOM_INFO(m_pCurrentLogger,lpszMsg);
	va_end(args);
	free(lpszMsg);
}

void util::CCxxLogger::Error( const char* lpszFormat, ... )
{
	va_list args;
	va_start(args, lpszFormat);
	char* lpszMsg = MsgFormat(lpszFormat,args);
	CUSTOM_ERROR(m_pCurrentLogger,lpszMsg);
	va_end(args);
	free(lpszMsg);
}

char* util::CCxxLogger::MsgFormat(const char* lpszFormat, va_list args)
{
	int nLen = _vscprintf( lpszFormat, args ) + 1;
	char* lpszBuffer = (char*) calloc(nLen,sizeof(char));
	if (!lpszBuffer) 
	{
		CUSTOM_ERROR(m_pCurrentLogger,"Out of Memory");
		return NULL;
	}
	vsprintf_s(lpszBuffer,nLen,lpszFormat,args);
	return lpszBuffer;
}

void util::CCxxLogger::Trace( const char* lpszFormat, ... )
{
	va_list args;
	va_start(args, lpszFormat);
	char* lpszMsg = MsgFormat(lpszFormat,args);
	CUSTOM_TRACE(m_pCurrentLogger,lpszMsg);
	va_end(args);
	free(lpszMsg);
}



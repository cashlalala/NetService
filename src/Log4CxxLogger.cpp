#include "stdafx.h"
#include "Log4CxxLogger.h"

#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx::xml;


util::CCxxLogger::CCxxLogger( const std::string& szName )
{
	m_pCurrentLogger = Logger::getLogger( szName);
}

util::CCxxLogger::~CCxxLogger()
{
}

void util::CCxxLogger::Debug( const char* lpszFormat, ... )
{
	va_list args;
	va_start(args, lpszFormat);
	char* lpszMsg = MsgFormat(lpszFormat,args);
	m_pCurrentLogger->debug(lpszMsg);
	va_end(args);
	free(lpszMsg);
}

void util::CCxxLogger::Info( const char* lpszFormat, ... )
{
	va_list args;
	va_start(args, lpszFormat);
	char* lpszMsg = MsgFormat(lpszFormat,args);
	m_pCurrentLogger->info(lpszMsg);
	va_end(args);
	free(lpszMsg);
}

void util::CCxxLogger::Error( const char* lpszFormat, ... )
{
	va_list args;
	va_start(args, lpszFormat);
	char* lpszMsg = MsgFormat(lpszFormat,args);
	m_pCurrentLogger->error(lpszMsg);
	va_end(args);
	free(lpszMsg);
}

char* util::CCxxLogger::MsgFormat(const char* lpszFormat, va_list args)
{
	int nLen = _vscprintf( lpszFormat, args ) + 1;
	char* lpszBuffer = (char*) calloc(nLen,sizeof(char));
	if (!lpszBuffer) 
	{
		m_pCurrentLogger->trace("Out of Memory!!");
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
	m_pCurrentLogger->trace(lpszMsg);
	va_end(args);
	free(lpszMsg);
}



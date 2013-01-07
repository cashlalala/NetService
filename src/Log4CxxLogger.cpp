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

void util::CCxxLogger::Debug( const string& szMsg )
{
	m_pCurrentLogger->debug(szMsg);
}

void util::CCxxLogger::Info( const string& szMsg )
{
	m_pCurrentLogger->info(szMsg);
}

void util::CCxxLogger::Error( const string& szMsg )
{
	m_pCurrentLogger->error(szMsg);
}



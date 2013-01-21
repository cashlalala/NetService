#include "StdAfx.h"
#include "JSonCppParser.h"
#include "NetServiceErr.h"

#include <json/json.h>

using namespace util;

CJsonCppParser::CJsonCppParser(void)
{
}

util::CJsonCppParser::~CJsonCppParser(void)
{
}


int util::CJsonCppParser::GetValueAsInt( const char* lpcszFormat, ... )
{
	va_list args;
	va_start(args, lpcszFormat);
	string szResult = MsgFormat(lpcszFormat,args);
	va_end(args);
	return GetObject(m_jvCurRoot,szResult).asInt();
}

bool util::CJsonCppParser::GetValueAsBool( const char* lpcszFormat, ... )
{
	va_list args;
	va_start(args, lpcszFormat);
	string szResult = MsgFormat(lpcszFormat,args);
	va_end(args);
	return GetObject(m_jvCurRoot,szResult).asBool();
}

string util::CJsonCppParser::GetValueAsString( const char* lpcszFormat, ... )
{
	va_list args;
	va_start(args, lpcszFormat);
	string szResult = MsgFormat(lpcszFormat,args);
	va_end(args);
	return GetObject(m_jvCurRoot,szResult).asString();
}

string util::CJsonCppParser::MsgFormat(const char* lpszFormat, va_list args)
{
	int nLen = _vscprintf( lpszFormat, args ) + 1;
	char* lpszBuffer = (char*) calloc(nLen,sizeof(char));
	vsprintf_s(lpszBuffer,nLen,lpszFormat,args);
	string szResult(lpszBuffer);
	free(lpszBuffer);
	return szResult;
}

Json::Value& util::CJsonCppParser::GetObject( Json::Value& jvRoot, string szTarget )
{
	unsigned nToken = szTarget.find_first_of(".");
	if (nToken==string::npos) 
	{
		if (szTarget=="")
			return jvRoot;
		else if (!isdigit(szTarget[0]) && atoi(szTarget.c_str())==0)
			return jvRoot[szTarget];
		else
			return jvRoot[atoi(szTarget.c_str())];
	}
	else
	{
		string szCurTarget = szTarget.substr(0,nToken);
		string szNextTarget = szTarget.substr(nToken+1);
		if (isalpha(szCurTarget[0]))
			return GetObject(jvRoot[szCurTarget],szNextTarget);
		else
			return GetObject(jvRoot[atoi(szCurTarget.c_str())],szNextTarget);
	}
}

int util::CJsonCppParser::Parse( string szSrc )
{
	Json::Reader jrReader;
	if (jrReader.parse(szSrc.c_str(),m_jvRoot))
	{
		m_jvCurRoot = m_jvRoot;
		return S_OK;
	}
	else
		return NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;
}

int util::CJsonCppParser::GetValueAsArrarySize( const char* lpcszFormat, ... )
{
	va_list args;
	va_start(args, lpcszFormat);
	string szResult = MsgFormat(lpcszFormat,args);
	va_end(args);
	return GetObject(m_jvCurRoot,szResult).size();
}

void util::CJsonCppParser::ResetRoot()
{
	m_jvCurRoot = m_jvRoot;
}

void util::CJsonCppParser::GetObjectAsListRoot( const char* lpcszFormat, ... )
{
	va_list args;
	va_start(args, lpcszFormat);
	string szResult = MsgFormat(lpcszFormat,args);
	va_end(args);
	m_jvCurRoot = GetObject(m_jvCurRoot,szResult);
}

void util::CJsonCppParser::StoreListRoot()
{
	m_jvListRoot.push_back(m_jvCurRoot);
}

void util::CJsonCppParser::RestoreListRoot()
{
	m_jvCurRoot = m_jvListRoot.back();
}

void util::CJsonCppParser::ClearTop()
{
	m_jvListRoot.pop_back();
}

bool util::CJsonCppParser::IsObjectNull( const char* lpcszFormat, ... )
{
	va_list args;
	va_start(args, lpcszFormat);
	string szResult = MsgFormat(lpcszFormat,args);
	va_end(args);
	return GetObject(m_jvCurRoot,szResult).isNull();
}

#include "stdafx.h"
#include "ErrorParseRuler.h"
#include "NetServiceErr.h"
#include "FlickrFields.h"
#include "FBFields.h"
#include "FBErrorModel.h"
#include "FkRErrorModel.h"

int util::CErrorParseRuler::Traverse( CFkrError& cFkrErr )
{
	cFkrErr.szStat = m_jvRoot[FLICK_ERROR_STAT].asString();
	if (cFkrErr.szStat == "ok") return S_OK;
	cFkrErr.szCode = m_jvRoot[FLICK_ERROR_CODE].asString();
	cFkrErr.szMsg = m_jvRoot[FLICK_ERROR_MSG].asString();
	return NS_E_DMGR_BAD_REQUEST_PARAMS;
}

int util::CErrorParseRuler::Traverse( CFBError& cFBErr )
{
	if (m_jvRoot[FB_ERROR].isNull()) return S_OK;
	cFBErr.szCode = m_jvRoot[FB_ERROR][FB_ERROR_CODE].asString();
	cFBErr.szMsg = m_jvRoot[FB_ERROR][FB_ERROR_MSG].asString();
	return NS_E_DMGR_BAD_REQUEST_PARAMS;
}

util::CErrorParseRuler::CErrorParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CErrorParseRuler::SetExecutor( void* pExecutor )
{
	m_jvRoot = *((Json::Value*) pExecutor);
}

void util::CErrorParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}


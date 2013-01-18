#include "stdafx.h"
#include "UserParseRuler.h"
#include "FkRUserModel.h"
#include "FBUserModel.h"

#include "FlickrFields.h"
#include "FBFields.h"

#include "LoggerMgr.h"
#include "StringHelper.h"

util::CUserListParseRuler::CUserListParseRuler()
{

}

util::CUserListParseRuler::CUserListParseRuler( void* pExecutor )
{
	this->SetExecutor(pExecutor);
}

void util::CUserListParseRuler::SetExecutor( void* pExecutor )
{
	if (pExecutor) m_jvRoot = * ((Json::Value*) pExecutor);
}

void util::CUserListParseRuler::Traverse( CFBUserList& cFBUserList )
{
	int nFriendNum = m_jvRoot[FB_DATA].size();
	CUserParseRuler cUsrParseRuler; 
	for (int i = 0;i<nFriendNum;++i)
	{
		model::CFBUser* pFbUsr = new model::CFBUser(); 
		cUsrParseRuler.SetExecutor((void*)&m_jvRoot[FB_DATA][i]);
		pFbUsr->AcceptUserParser(cUsrParseRuler);
		cFBUserList.items.push_back(pFbUsr);
	}
	cFBUserList.szNextPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_NEXT].asString();
	cFBUserList.szPreviousPageUrl = m_jvRoot[FB_PAGING][FB_PAGING_PREVIOUS].asString();
}

void util::CUserListParseRuler::Traverse( CFkrUserList& cFkrUserList )
{
	cFkrUserList.nPage = atoi(m_jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_PAGE].asString().c_str());
	cFkrUserList.nPages = atoi(m_jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_PAGES].asString().c_str());
	cFkrUserList.nPerpage = atoi(m_jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_PERPAGE].asString().c_str());
	cFkrUserList.nTotal = atoi(m_jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_TOTAL].asString().c_str());

	int nFriends = m_jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_CONTACT].size();
	CUserParseRuler cUserParseRuler;
	for (int i =0;i<nFriends;++i)
	{
		Json::Value item = m_jvRoot[FLICK_CONTACTS][FLICK_CONTACTS_CONTACT][i];
		cUserParseRuler.SetExecutor((void*)&item);
		model::CFkrUser* cFkrUsr = new model::CFkrUser();
		cFkrUsr->AcceptUserParser(cUserParseRuler);
		cFkrUserList.items.push_back(cFkrUsr);
	}
}


util::CUserParseRuler::CUserParseRuler( void* pExecutor  /*= NULL*/)
{
	this->SetExecutor(pExecutor);
	m_pILogger = util::CLoggerMgr::GetLogger(Log4Cxx,"CUserParseRuler");
}

void util::CUserParseRuler::SetExecutor( void* pExecutor )
{
	if (pExecutor) m_jvRoot = * ((Json::Value*) pExecutor);
}

void util::CUserParseRuler::Traverse( CFBUser& cFBUser )
{
	cFBUser.szId = m_jvRoot[FB_ID].asString();
	cFBUser.szFullName = m_jvRoot[FB_USER_NAME].asString();
	if (!m_jvRoot[FB_USER_PICTURE].isNull())
	{
		cFBUser.pProfile = new CFBProfile();
		cFBUser.pProfile->szThumNail = m_jvRoot[FB_USER_PICTURE][FB_USER_PICTURE_DATA][FB_USER_PICTURE_DATA_URL].asString();
	}
}

void util::CUserParseRuler::Traverse( CFkrUser& cFkrUser )
{
	Json::Value jvValue = m_jvRoot;
	if (jvValue[FLICK_PEOPLE_PERSON].isNull())
	{
		cFkrUser.szId = jvValue[FLICK_CONTACT_NSID].asString();
		cFkrUser.szFullName = jvValue[FLICK_CONTACT_REAL_NAME].asString();
		cFkrUser.szUsrName = jvValue[FLICK_CONTACT_USR_NAME].asString();
		cFkrUser.bIsFriend = jvValue[FLICK_CONTACT_FRIEND].asBool();
		cFkrUser.bIsFamily = jvValue[FLICK_CONTACT_FAMILY].asBool();	
	}
	else
	{
		jvValue = m_jvRoot[FLICK_PEOPLE_PERSON];
		cFkrUser.bIsFamily = atoi(jvValue[FLICK_PEOPLE_PERSON_ISFAMILY].asString().c_str()) != 0;
		cFkrUser.bIsFriend = atoi(jvValue[FLICK_PEOPLE_PERSON_ISFRIEND].asString().c_str()) != 0;
		cFkrUser.bIsProUsr = atoi(jvValue[FLICK_PEOPLE_PERSON_ISPRO].asString().c_str()) != 0;
		cFkrUser.szFullName = jvValue[FLICK_PEOPLE_PERSON_REAL_NAME][FLICK_FIELD_CONTENT].asString();
		cFkrUser.szId = jvValue[FLICK_PEOPLE_PERSON_ID].asString();
		cFkrUser.szUsrName = jvValue[FLICK_PEOPLE_PERSON_USR_NAME][FLICK_FIELD_CONTENT].asString();
	}

	if (jvValue[FLICK_PEOPLE_PERSON_ICONFARM].asString()=="0" && 
		jvValue[FLICK_PEOPLE_PERSON_ICONSVR].asString()=="0")
	{
		LOGGER_DEBUG(m_pILogger,"This queryee [%s] don't have the thumbnail or open the access right for the querier",cFkrUser.szId.c_str())
	}
	else
	{
		cFkrUser.pProfile = new CFkrProfile();
		cFkrUser.pProfile->szThumNail = util::CStringHelper::Format("http://farm%s.staticflickr.com/%s/buddyicons/%s.jpg", 
			jvValue[FLICK_PEOPLE_PERSON_ICONFARM].asString().c_str(),
			jvValue[FLICK_PEOPLE_PERSON_ICONSVR].asString().c_str(),
			cFkrUser.szId.c_str());
	}

}



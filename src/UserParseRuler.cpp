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
}

void util::CUserListParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

void util::CUserListParseRuler::Traverse( CFBUserList& cFBUserList )
{
	int nFriendNum = m_pParser->GetValueAsArrarySize(FB_DATA);
	CUserParseRuler cUsrParseRuler; 
	cUsrParseRuler.SetExecutor(m_pParser);
	m_pParser->StoreRoot();
	for (int i = 0;i<nFriendNum;++i)
	{
		m_pParser->GetObjectAsRoot("%s.%d",FB_DATA,i);
		model::CFBUser* pFbUsr = new model::CFBUser();
		pFbUsr->AcceptUserParser(cUsrParseRuler);
		cFBUserList.items.push_back(pFbUsr);
		m_pParser->RestoreRoot();
	}
	m_pParser->ClearBuffTop();
	cFBUserList.szNextPageUrl = m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_NEXT);
	cFBUserList.szPreviousPageUrl = m_pParser->GetValueAsString("%s.%s",FB_PAGING,FB_PAGING_PREVIOUS);
}

void util::CUserListParseRuler::Traverse( CFkrUserList& cFkrUserList )
{
	cFkrUserList.nPage = atoi(m_pParser->GetValueAsString(FLICK_CONTACTS"."FLICK_CONTACTS_PAGE).c_str());
	cFkrUserList.nPages = atoi(m_pParser->GetValueAsString(FLICK_CONTACTS"."FLICK_CONTACTS_PAGES).c_str());
	cFkrUserList.nPerpage = atoi(m_pParser->GetValueAsString(FLICK_CONTACTS"."FLICK_CONTACTS_PERPAGE).c_str());
	cFkrUserList.nTotal = atoi(m_pParser->GetValueAsString(FLICK_CONTACTS"."FLICK_CONTACTS_TOTAL).c_str());

	int nFriends = m_pParser->GetValueAsArrarySize(FLICK_CONTACTS"."FLICK_CONTACTS_CONTACT);
	CUserParseRuler cUserParseRuler;
	cUserParseRuler.SetExecutor(m_pParser);
	m_pParser->StoreRoot();
	for (int i =0;i<nFriends;++i)
	{
		m_pParser->GetObjectAsRoot("%s.%s.%d",FLICK_CONTACTS,FLICK_CONTACTS_CONTACT,i);
		model::CFkrUser* cFkrUsr = new model::CFkrUser();
		cFkrUsr->AcceptUserParser(cUserParseRuler);
		cFkrUserList.items.push_back(cFkrUsr);
		m_pParser->RestoreRoot();
	}
	m_pParser->ClearBuffTop();
}


util::CUserParseRuler::CUserParseRuler( void* pExecutor  /*= NULL*/)
{
	this->SetExecutor(pExecutor);
	m_pILogger = util::CLoggerMgr::GetLogger(Log4Cxx,"CUserParseRuler");
}

void util::CUserParseRuler::SetExecutor( void* pExecutor )
{
}

void util::CUserParseRuler::SetExecutor( IParser* pExecutor )
{
	m_pParser = pExecutor;
}

void util::CUserParseRuler::Traverse( CFBUser& cFBUser )
{
	cFBUser.szId = m_pParser->GetValueAsString(FB_ID);
	cFBUser.szFullName = m_pParser->GetValueAsString(FB_USER_NAME);
	if (!m_pParser->IsObjectNull(FB_USER_PICTURE))
	{
		cFBUser.pProfile = new CFBProfile();
		cFBUser.pProfile->szThumNail = m_pParser->GetValueAsString(FB_USER_PICTURE"."FB_USER_PICTURE_DATA"."FB_USER_PICTURE_DATA_URL);
	}
}

void util::CUserParseRuler::Traverse( CFkrUser& cFkrUser )
{
	if (m_pParser->IsObjectNull(FLICK_PEOPLE_PERSON))
	{
		cFkrUser.szId = m_pParser->GetValueAsString(FLICK_CONTACT_NSID);
		cFkrUser.szFullName = m_pParser->GetValueAsString(FLICK_CONTACT_REAL_NAME);
		cFkrUser.szUsrName = m_pParser->GetValueAsString(FLICK_CONTACT_USR_NAME);
		cFkrUser.bIsFriend = m_pParser->GetValueAsBool(FLICK_CONTACT_FRIEND);
		cFkrUser.bIsFamily = m_pParser->GetValueAsBool(FLICK_CONTACT_FAMILY);
	}
	else
	{
		m_pParser->StoreRoot();
		m_pParser->GetObjectAsRoot(FLICK_PEOPLE_PERSON);
		cFkrUser.bIsFamily = atoi(m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ISFAMILY).c_str()) != 0;
		cFkrUser.bIsFriend = atoi(m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ISFRIEND).c_str()) != 0;
		cFkrUser.bIsProUsr = atoi(m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ISPRO).c_str()) != 0;
		cFkrUser.szFullName = m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_REAL_NAME"."FLICK_FIELD_CONTENT);
		cFkrUser.szId = m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ID);
		cFkrUser.szUsrName = m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_USR_NAME"."FLICK_FIELD_CONTENT);
	}

	if (m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ICONFARM)=="0" && 
		m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ICONSVR)=="0")
	{
		LOGGER_DEBUG(m_pILogger,"This queryee [%s] don't have the thumbnail or open the access right for the querier",cFkrUser.szId.c_str())
	}
	else
	{
		cFkrUser.pProfile = new CFkrProfile();
		cFkrUser.pProfile->szThumNail = util::CStringHelper::Format("http://farm%s.staticflickr.com/%s/buddyicons/%s.jpg",
			m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ICONFARM).c_str(),
			m_pParser->GetValueAsString(FLICK_PEOPLE_PERSON_ICONSVR).c_str(),
			cFkrUser.szId.c_str());
	}
}



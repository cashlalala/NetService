#pragma once
#include "ILogger.h"
#include "IParseRuler.h"
#include "IParser.h"
#include <json/json.h>

namespace util
{
	//The User List Ruler traverses the friends list but not specific users list
	//Both Flickr and Facebook don't give the APIs to achieve getting specific users list.
	//I think they have their own reasons not to providing these features.
	//Somehow, Facebook FQL may achieved this , but here we don't handle this case.
	class CUserListParseRuler : public IUserListParseRuler 
	{
	public:
		CUserListParseRuler();

		CUserListParseRuler(void* pExecutor);

		virtual void Traverse( CFBUserList& cFBUserList ) ;

		virtual void Traverse( CFkrUserList& cFkrUserList ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor) ;
		
	private:
		IParser* m_pParser;
	};

	class CUserParseRuler : public IUserParseRuler 
	{
	public:
		CUserParseRuler(void* pExecutor = NULL);

		virtual void Traverse( CFBUser& cFBUser ) ;

		virtual void Traverse( CFkrUser& cFkrUser ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor) ;

	private:
		IParser* m_pParser;

		ILogger* m_pILogger;
	};
}
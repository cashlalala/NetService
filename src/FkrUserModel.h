#pragma once

#include "IUserModel.h"

namespace model
{
	/*
	* Those models are for your convenient to use. you can directly use them to data-bind or inherit.
	*/

	struct CFkrProfile : public IProfile{
		virtual ~CFkrProfile(){};
		int AcceptProfileParser(IProfileParseRuler& cProfileParser) {return cProfileParser.Traverse(*this);}
	};

	struct CFkrUser : public IUser{
	public:
		CFkrUser():bIsFamily(false),bIsFriend(false),bIsProUsr(false){};
		virtual ~CFkrUser(){};
		bool bIsFriend;
		bool bIsFamily;
		bool bIsProUsr;
		string szUsrName;
		void AcceptUserParser(IUserParseRuler& cUserParser) {cUserParser.Traverse(*this);}
	};

	struct CFkrUserList : public IUserList{
		CFkrUserList() : nPage(0),nPages(0),nPerpage(0),nTotal(0){};
		virtual ~CFkrUserList(){};
		int nPage;
		int nPages;
		int nPerpage;
		int nTotal; //not only in current page
		void AcceptUserListParser(IUserListParseRuler& cUserListParser) {cUserListParser.Traverse(*this);}
	};
}



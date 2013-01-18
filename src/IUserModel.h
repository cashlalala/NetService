#pragma once
#include "IModel.h"
#include "IParseRuler.h"
#include <list>
#include <string>

using std::list;
using std::string;
using namespace util;

namespace model
{
	struct IProfile  : public IModel{
		virtual ~IProfile() = 0;
		string szThumNail;
	};

	inline IProfile::~IProfile(){};

	struct IUser : 
		public IModel, public IUserParsable
	{
		IUser() : pProfile(NULL){};
		virtual ~IUser() = 0;
		string szId;
		string szFullName;
		IProfile* pProfile;
		void AcceptUserParser(IUserParseRuler& cUserParser) {};
	};

	inline IUser::~IUser()
	{
		SAFE_DELETE_OBJECT(pProfile);
	};

	struct IUserList  : 
		public IPagedList<IUser*>, public IUserListParsable
	{
		virtual ~IUserList() = 0;
		void AcceptUserListParser(IUserListParseRuler& cUserListParser) {};
	};

	inline IUserList::~IUserList()
	{
	};

}
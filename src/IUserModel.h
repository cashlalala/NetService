#pragma once

#include <list>

using std::list;

namespace model
{
	struct IUser{
		virtual ~IUser() {};
		string szId;
		string szFullName;
	};

	struct IUserList : public list<IUser>{
		virtual ~IUserList(){};
	};

	struct CFBUser : public IUser{
		virtual ~CFBUser(){};
	};

	struct CFBUserList : public IUserList{
		virtual ~CFBUserList(){};
	};

}
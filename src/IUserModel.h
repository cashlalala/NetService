#pragma once

#include <list>
#include <string>

using std::list;
using std::string;

namespace model
{
	struct IUser{
		virtual ~IUser() = 0;
		string szId;
		string szFullName;
		string szIcon;
	};

	inline IUser::~IUser(){};

	struct IUserList {
		virtual ~IUserList() = 0;
		list<IUser*> listUser;
	};

	inline IUserList::~IUserList(){};

}
#pragma once

#include <list>
#include <string>

using std::list;
using std::string;

namespace model
{
	struct IProfile {
		virtual ~IProfile() = 0;
		string szThumNail;
	};

	inline IProfile::~IProfile(){};

	struct IUser{
		virtual ~IUser() = 0;
		string szId;
		string szFullName;
		IProfile* pProfile;
	};

	inline IUser::~IUser(){};

	struct IUserList {
		virtual ~IUserList() = 0;
		list<IUser*> listUser;
		string szNext;
		string szPrevious;
	};

	inline IUserList::~IUserList(){};

}
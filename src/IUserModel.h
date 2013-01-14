#pragma once

#include "IModel.h"
#include <list>
#include <string>

using std::list;
using std::string;

namespace model
{
	struct IProfile  : public IModel{
		virtual ~IProfile() = 0;
		string szThumNail;
	};

	inline IProfile::~IProfile(){};

	struct IUser : public IModel{
		IUser()
		{
			pProfile = 0;
		};
		virtual ~IUser() = 0;
		string szId;
		string szFullName;
		IProfile* pProfile;
	};

	inline IUser::~IUser()
	{
		SAFE_DELETE_OBJECT(pProfile);
	};

	struct IUserList  : public IPagedList<IUser*>{
		virtual ~IUserList() = 0;
	};

	inline IUserList::~IUserList()
	{
		//SAFE_DELETE_LIST(list<IUser*>,listUser)
	};

}
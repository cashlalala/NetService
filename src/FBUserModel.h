#pragma once

#include "IUserModel.h"

namespace model
{
	struct CFBUser : public IUser{
		virtual ~CFBUser(){};
	};

	struct CFBUserList : public IUserList{
		virtual ~CFBUserList();
	};
}



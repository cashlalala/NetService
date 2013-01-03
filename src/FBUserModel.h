#pragma once

#include "IUserModel.h"

namespace model
{
	//only user, group, page, event, and application ID have those properties
	class CFBProfile : public IProfile{
	public:
		CFBProfile(void){};
		virtual ~CFBProfile(){};
		string szBig;
		string szSmall;
		string szSquare;
	};

	class CFBUser : public IUser{
	public:
		CFBUser();
		virtual ~CFBUser();
	};

	struct CFBUserList : public IUserList{
		virtual ~CFBUserList();
	};
}



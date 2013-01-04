#pragma once

#include "IUserModel.h"

namespace model
{
	/*
	* Those models are for your convenient to use. you can directly use them to data-bind or inherit.
	*/

	//only user, group, page, event, and application ID have those properties
	struct CFBProfile : public IProfile{
	public:
		virtual ~CFBProfile(){};
		string szBig;
		string szSmall;
		string szSquare;
	};

	struct CFBUser : public IUser{
	public:
		virtual ~CFBUser(){};
	};

	struct CFBUserList : public IUserList{
		virtual ~CFBUserList(){};
	};
}



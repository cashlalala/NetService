#include "stdafx.h"
#include "FBUserModel.h"

model::CFBUserList::~CFBUserList()
{
	NETSERV_LIST_SAFE_DELETE(list<IUser*>,listUser)
}

#include "stdafx.h"
#include "FBUserModel.h"

model::CFBUserList::~CFBUserList()
{
	for (list<IUser*>::iterator it = listUser.begin();it!=listUser.end();++it)
	{
		if (*it !=NULL)
		{
			delete *it;
			*it = NULL;
		}
	}
	listUser.clear();
}

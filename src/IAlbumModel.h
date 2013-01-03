#pragma once

#include "IModel.h"

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{
	struct IAlbum : IModel{
		virtual ~IAlbum() = 0;
		string szId;
		string szCoverPhotoId;
		int nCount;
	};

	inline IAlbum::~IAlbum(){};

	struct IAlbumList: IModel {
		virtual ~IAlbumList() = 0;
		list<IAlbum*> listAlbum;
		string szNext;
		string szPrevious;
	};

	inline IAlbumList::~IAlbumList()
	{
		SAFE_DELETE_LIST(list<IAlbum*>,listAlbum)
	};

}
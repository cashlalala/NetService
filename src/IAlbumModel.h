#pragma once

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{
	struct IAlbum {
		virtual ~IAlbum() = 0;
		string szId;
		string szCoverPhotoId;
		int nCount;
	};

	inline IAlbum::~IAlbum(){};

	struct IAlbumList {
		virtual ~IAlbumList() = 0;
		list<IAlbum*> listAlbum;
		string szNext;
		string szPrevious;
	};

	inline IAlbumList::~IAlbumList(){};

}
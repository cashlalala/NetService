#pragma once

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{
	struct IImage{
		int nHeight;
		int nWidth;
		string szSource;
	};

	struct IPhoto : public IImage{
		string id;
		string szlink;
		string szThumbNail;
		list<IImage> listImages;
	};

	struct IPhotoList : public list<IPhoto>{
		string szNext;
		string szPrevious;
	};

}


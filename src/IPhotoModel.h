#pragma once

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{
	struct IImage{
		virtual ~IImage(){};
		int nHeight;
		int nWidth;
		string szSource;
	};

	struct IPhoto : public IImage{
		virtual ~IPhoto(){};
		string id;
		string szlink;
		string szThumbNail;
		list<IImage> listImages;
	};

	struct IPhotoList : public list<IPhoto>{
		virtual ~IPhotoList(){};
		string szNext;
		string szPrevious;
	};

}


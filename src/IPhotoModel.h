#pragma once

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{

	struct IImage{
		virtual ~IImage() = 0;
		int nHeight;
		int nWidth;
		string szSource;
	};

	inline IImage::~IImage(){};

	struct IPhoto : public IImage{
		virtual ~IPhoto() = 0;
		string szId;
		string szLink;
		string szThumbNail;
		list<IImage*> listImages;
	};

	inline IPhoto::~IPhoto(){};

	struct IPhotoList {
		virtual ~IPhotoList() = 0;
		list<IPhoto*> listPhoto;
		string szNext;
		string szPrevious;
	};

	inline IPhotoList::~IPhotoList(){};

}


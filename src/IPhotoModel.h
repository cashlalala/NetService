#pragma once
#include "IModel.h"

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{

	struct IImage : public IModel{
		IImage():nHeight(0),nWidth(0){};
		virtual ~IImage() = 0;
		int nHeight;
		int nWidth;
		string szSource;
	};

	inline IImage::~IImage(){};

	struct IImageList : public IList<IImage*>{
		virtual ~IImageList() = 0;
	};

	inline IImageList::~IImageList(){};

	struct IPhoto : virtual public IImage, virtual public IImageList{
		virtual ~IPhoto() = 0;
		string szId;
		string szLink;
		string szThumbNail;
	};

	inline IPhoto::~IPhoto()
	{
		//SAFE_DELETE_LIST(list<IImage*>,listImages)
	};

	struct IPhotoList : public IPagedList<IPhoto*>{
		virtual ~IPhotoList() = 0;
	};

	inline IPhotoList::~IPhotoList()
	{
		//SAFE_DELETE_LIST(list<IPhoto*>,listPhoto)
	};

}


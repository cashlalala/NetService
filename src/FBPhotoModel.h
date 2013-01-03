#pragma once

#include "IPhotoModel.h"
#include <string>
#include <list>

using std::list;
using std::string;
using model::IPhoto;
using model::IPhotoList;

namespace model
{

	struct CFBImage : public IImage
	{
		virtual ~CFBImage(void){};
	};


	struct CFBPhoto : public IPhoto
	{
		virtual ~CFBPhoto(void){};
	};

	struct CFBPhotoList : public IPhotoList
	{
		virtual ~CFBPhotoList(void){};
	};
}



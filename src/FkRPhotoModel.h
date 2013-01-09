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

	struct CFkRImage : public IImage
	{
		virtual ~CFkRImage(void){};
	};


	struct CFkRPhoto : public IPhoto
	{
		virtual ~CFkRPhoto(void){};
	};

	struct CFkRPhotoList : public IPhotoList
	{
		virtual ~CFkRPhotoList(void){};
	};
}



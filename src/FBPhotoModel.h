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

	class CFBImage : public IImage
	{
	public:
		CFBImage(void){};
		virtual ~CFBImage(void){};
	};


	class CFBPhoto : public IPhoto
	{
	public:
		CFBPhoto(void);
		virtual ~CFBPhoto(void);
	};

	class CFBPhotoList : public IPhotoList
	{
	public:
		CFBPhotoList(void){};
		virtual ~CFBPhotoList(void);
	};
}



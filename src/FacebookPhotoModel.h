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
	class CFacebookImage : public IImage
	{
	public:
		CFacebookImage(void){};
		virtual ~CFacebookImage(void){};
	};


	class CFacebookPhoto : public IPhoto
	{
	public:
		CFacebookPhoto(void) {};
		virtual ~CFacebookPhoto(void);
	};

	class CFacebookPhotoList : public IPhotoList
	{
	public:
		CFacebookPhotoList(void){};
		virtual ~CFacebookPhotoList(void);
	};
}



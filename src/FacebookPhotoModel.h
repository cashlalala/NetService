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
	class CFacebookPhoto : public IPhoto
	{
	public:
		CFacebookPhoto(void);
		~CFacebookPhoto(void);
	};

	class CFacebookPhotoList : public IPhotoList
	{

	};
}



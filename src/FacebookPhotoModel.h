#pragma once

#include "IPhotoModel.h"
#include <string>
#include <list>

using std::list;
using std::string;
using model::IPhoto;
using model::IPhotoList;

class CFacebookPhotoModel : public IPhoto
{
public:
	CFacebookPhotoModel(void);
	~CFacebookPhotoModel(void);
};

class CFacebookPhotoListModel : public IPhotoList
{

};

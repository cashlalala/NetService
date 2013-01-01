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
		virtual ~CFacebookPhoto(void)
		{
			for (list<IImage*>::iterator it = listImages.begin();it!=listImages.end();++it)
			{
				if (*it !=NULL)
				{
					delete *it;
					*it = NULL;
				}
			}
			listImages.clear();
		};
	};

	class CFacebookPhotoList : public IPhotoList
	{
	public:
		CFacebookPhotoList(void){};
		virtual ~CFacebookPhotoList(void)
		{ 
			for (list<IPhoto*>::iterator it = listPhoto.begin();it!=listPhoto.end();++it)
			{
				if (*it !=NULL)
				{
					delete *it;
					*it = NULL;
				}
			}
			listPhoto.clear();
		};
	};
}



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

	struct CFkrImage : virtual public IImage
	{
		virtual ~CFkrImage(void){};
		string szLabel;
		string szMedia;
	};

	struct CFkrImageList : virtual public IImageList
	{
		virtual ~CFkrImageList(void){};
	};

	struct CFkrPhoto : public IPhoto , public CFkrImage
	{
		CFkrPhoto():bIsPublic(false),bIsFriend(false),
			bIsFamily(false),bCanBlog(false),bCanPrint(false),bCanDownload(false){};
		virtual ~CFkrPhoto(void){};
		string szOwner;
		string szTitle;
		bool bIsPublic;
		bool bIsFriend;
		bool bIsFamily;
		bool bCanBlog;
		bool bCanPrint;
		bool bCanDownload;
	};

	struct CFkrPhotoList : public IPhotoList
	{
		CFkrPhotoList():nPage(0),nPages(0),nPerpage(0),nTotal(0){};
		virtual ~CFkrPhotoList(void){};
		int nPage;
		int nPages;
		int nPerpage;
		int nTotal; //not only in current page
	};
}



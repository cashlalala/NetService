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

	struct CFkRImage : virtual public IImage
	{
		virtual ~CFkRImage(void){};
		string szLabel;
		string szMedia;
	};


	struct CFkRPhoto : public IPhoto , public CFkRImage
	{
		CFkRPhoto():bIsPublic(false),bIsFriend(false),
			bIsFamily(false),bCanBlog(false),bCanPrint(false),bCanDownload(false){};
		virtual ~CFkRPhoto(void){};
		string szOwner;
		string szTitle;
		bool bIsPublic;
		bool bIsFriend;
		bool bIsFamily;
		bool bCanBlog;
		bool bCanPrint;
		bool bCanDownload;
	};

	struct CFkRPhotoList : public IPhotoList
	{
		CFkRPhotoList():nPage(0),nPages(0),nPerpage(0),nTotal(0){};
		virtual ~CFkRPhotoList(void){};
		int nPage;
		int nPages;
		int nPerpage;
		int nTotal; //not only in current page
	};
}



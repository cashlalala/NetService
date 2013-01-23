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
		void AcceptImageParser(IImageParseRuler& cImageParser) {cImageParser.Traverse(*this);}
	};

	struct CFkrImageList : virtual public IImageList
	{
		virtual ~CFkrImageList(void){};
		void AcceptImageListParser(IImageListParseRuler& cImageListParser) {cImageListParser.Traverse(*this);}
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
		void AcceptPhotoParser(IPhotoParseRuler& cPhotoParser) {cPhotoParser.Traverse(*this);};
	};

	struct CFkrPhotoList : public IPhotoList
	{
		CFkrPhotoList():nPage(0),nPages(0),nPerpage(0),nTotal(0){};
		virtual ~CFkrPhotoList(void){};
		int nPage;
		int nPages;
		int nPerpage;
		int nTotal; //not only in current page
		void AcceptPhotoListParser(IPhotoListParseRuler& cPhotoListParser) {cPhotoListParser.Traverse(*this);}
	};
}



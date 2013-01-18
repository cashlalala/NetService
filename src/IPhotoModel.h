#pragma once
#include "IModel.h"
#include "IParseRuler.h"

#include <string>
#include <list>

using std::list;
using std::string;
using namespace util;

namespace model
{

	struct IImage : 
		public IModel, public IImageParsable
	{
		IImage():nHeight(0),nWidth(0){};
		virtual ~IImage() = 0;
		int nHeight;
		int nWidth;
		string szSource;
		void AcceptImageParser(IImageParseRuler& cImageParser){};
	};

	inline IImage::~IImage(){};

	struct IImageList : 
		public IList<IImage*>, public IImageListParsable
	{
		virtual ~IImageList() = 0;
		void AcceptImageListParser(IImageListParseRuler& cImageListParser){};
	};

	inline IImageList::~IImageList(){};

	struct IPhoto : 
		virtual public IImage, public IPhotoParsable
	{
		IPhoto() : pListImage(NULL) {};
		virtual ~IPhoto() = 0;
		string szId;
		string szLink;
		string szThumbNail;
		IImageList* pListImage;
		void AcceptPhotoParser(IPhotoParseRuler& cPhotoParser){};
	};

	inline IPhoto::~IPhoto()
	{
		SAFE_DELETE_OBJECT(pListImage);
	};

	struct IPhotoList : 
		public IPagedList<IPhoto*>,  public IPhotoListParsable
	{
		virtual ~IPhotoList() = 0;
		void AcceptPhotoListParser(IPhotoListParseRuler& cPhotoListParser){};
	};

	inline IPhotoList::~IPhotoList()
	{
	};

}


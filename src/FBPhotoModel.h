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

	struct CFBImage : virtual public IImage
	{
		virtual ~CFBImage(void){};
		void AcceptImageParser(IImageParseRuler& cImageParser) {cImageParser.Traverse(*this);}
	};

	struct CFBImageList : virtual public IImageList
	{
		virtual ~CFBImageList(void){};
		void AcceptImageListParser(IImageListParseRuler& cImageListParser) {cImageListParser.Traverse(*this);}
	};

	struct CFBPhoto : public IPhoto, public CFBImage
	{
		virtual ~CFBPhoto(void){};
		void AcceptPhotoParser(IPhotoParseRuler& cPhotoParser) {cPhotoParser.Traverse(*this);}
	};

	struct CFBPhotoList : public IPhotoList
	{
		virtual ~CFBPhotoList(void){};
		void AcceptPhotoListParser(IPhotoListParseRuler& cPhotoListParser) { cPhotoListParser.Traverse(*this);}
	};
}



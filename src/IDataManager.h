#pragma once
#include "IPhotoModel.h"
#include <string>

using std::string;
using namespace model;

namespace util
{
	typedef enum {
		BoostJson,
		BoostXml,
		JsonCpp
	} EnDataMgr;

	typedef enum {
		Facebook,
		Flickr
	} EnDataOwner;

	struct IDataManager {
		virtual int ParsePhotoList( string szInput, IPhotoList& iPhotoList, EnDataOwner enDataOwner ) =0;
		virtual int ParsePhoto( string szInput, IPhoto& iPhoto, EnDataOwner enDataOwner  ) =0;
	};
}


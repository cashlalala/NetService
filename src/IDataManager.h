#pragma once
#include "IPhotoModel.h"
#include "IUserModel.h"
#include "IErrorModel.h"
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
		virtual ~IDataManager() = 0;
		virtual int ParsePhotoList(  IPhotoList& iPhotoList, string szInput, EnDataOwner enDataOwner, IError& iError) =0;
		virtual int ParsePhoto( string szInput, IPhoto& iPhoto, EnDataOwner enDataOwner, IError& iError ) =0;
		virtual int ParseUser(string szInput, IUser& iUser, EnDataOwner enDataOwner, IError& iError) = 0;
	};

	inline IDataManager::~IDataManager(){};
}


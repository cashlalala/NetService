#pragma once
#include "IPhotoModel.h"
#include "IUserModel.h"
#include "IErrorModel.h"
#include "IVideoModel.h"
#include "IAlbumModel.h"
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
		virtual int ParsePhotoList( IPhotoList& iPhotoList, string szInput, EnDataOwner enDataOwner, IError& iError) =0;
		virtual int ParsePhoto( IPhoto& iPhoto, string szInput, EnDataOwner enDataOwner, IError& iError ) =0;
		virtual int ParseUser(IUser& iUser, string szInput, EnDataOwner enDataOwner, IError& iError) = 0;
		virtual int ParseFriendList(IUserList& iUser, string szInput, EnDataOwner enDataOwner, IError& iError  )  = 0;
		virtual int ParseVideoList( IVideoList& iVideoList, string szInput, EnDataOwner enDataOwner, IError& iError) = 0;
		virtual int ParseAlbumList(IAlbumList& iAlbumList, string szInput, EnDataOwner enDataOwner, IError& iError) = 0;
		virtual int ParseProfile(IProfile& iProfile, string szInput, EnDataOwner enDataOwner, IError& iError) = 0;

		virtual int ParseError(IError& iError, string szInput, EnDataOwner enDataOwner) = 0;
	};

	inline IDataManager::~IDataManager(){};
}


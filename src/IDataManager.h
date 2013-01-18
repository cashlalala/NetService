#pragma once
#include "IPhotoModel.h"
#include "IUserModel.h"
#include "IErrorModel.h"
#include "IVideoModel.h"
#include "IAlbumModel.h"
#include "SysTypes.h"

#include <string>
#include <map>
#include <list>

using std::list;
using std::map;
using std::string;
using namespace systypes;
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

	struct IDataMgrFBOnly {
		virtual ~IDataMgrFBOnly() = 0;
		virtual int ParseFBSrouceSmall(SysList::Str2StrMapList& listMap, string szInput, IError& iError) = 0;
	};

	inline IDataMgrFBOnly::~IDataMgrFBOnly(){};

	struct IDataMgrFkrOnly {
		virtual ~IDataMgrFkrOnly() = 0;
		virtual int ParseFkrFrob(string& szFrob, string szInput, IError& iError) = 0;
		virtual int ParseFkrAuthToken(SysMaps::Str2Str& szAuthToken, string szInput,IError& iError) = 0;
	};

	inline IDataMgrFkrOnly::~IDataMgrFkrOnly(){};

	struct IDataManager {
		virtual ~IDataManager() = 0;
		virtual int ParsePhotoList( IPhotoList& iPhotoList, string szInput, IError& iError) =0;
		virtual int ParsePhoto( IPhoto& iPhoto, string szInput, IError& iError ) =0;
		virtual int ParseUser(IUser& iUser, string szInput, IError& iError) = 0;
		virtual int ParseFriendList(IUserList& iUser, string szInput, IError& iError  )  = 0;
		virtual int ParseVideoList( IVideoList& iVideoList, string szInput, IError& iError) = 0;
		virtual int ParseAlbumList(IAlbumList& iAlbumList, string szInput, IError& iError) = 0;
		virtual int ParseProfile(IProfile& iProfile, string szInput, IError& iError) = 0;
		virtual int ParseImageList(IImageList& listImage, string szInput, IError& iError) = 0;

		virtual int ParseError(IError& iError, string szInput) = 0;
	};

	inline IDataManager::~IDataManager(){};
}


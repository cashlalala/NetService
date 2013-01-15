#pragma once
#include "IDataManager.h"
#include "LoggerMgr.h"
#include <list>
#include <json/json.h>

using util::IDataManager;

namespace util
{
	class CJsonCppMgr :
		public IDataManager
	{
	public:
		CJsonCppMgr(void);
		virtual ~CJsonCppMgr(void);

		virtual int ParsePhotoList( IPhotoList& iPhotoList, string szInput, EnDataOwner enDataOwner, IError& iError ) ;

		virtual int ParsePhoto( IPhoto& iPhoto, string szInput, EnDataOwner enDataOwner, IError& iError  ) ;

		virtual int ParseUser(IUser& iUser, string szInput, EnDataOwner enDataOwner, IError& iError) ;

		virtual int ParseError(IError& iError, string szInput, EnDataOwner enDataOwner) ;

		virtual int ParseFriendList(IUserList& iUserList, string szInput, EnDataOwner enDataOwner, IError& iError  ) ;

		virtual int ParseVideoList( IVideoList&iVideoList, string szInput, EnDataOwner enDataOwner, IError& iError) ;

		virtual int ParseAlbumList(IAlbumList& iAlbumList, string szInput, EnDataOwner enDataOwner, IError& iError) ;

		virtual int ParseProfile(IProfile& iProfile, string szInput, EnDataOwner enDataOwner, IError& iError);

		virtual int ParseFkrFrob(string& szFrob, string szInput, IError& iError) ;

		virtual int ParseFkrAuthToken(string& szAuthToken, string szInput,IError& iError) ;

	private:
		//To keep the physical linkage isolated, don't specify the explicit type of the interface among the parameters.
		// Even the function name is specified with exact targets like "FB" "FLICKR";
		void TravFBPhotoList( Json::Value &jvRoot, IPhotoList &iPhotoList);

		void TravFBPagination( IPage &iPhotoList, Json::Value & jvRoot );

		int TravFBErr(Json::Value &jvRoot, IError& cFbErr);
		void TravFBPhoto( Json::Value &jvRoot, IPhoto* pIPhoto );
		void TravFBUser( Json::Value jvRoot, IUser* iUser );
		void TravFBFriendList(Json::Value jvRoot, IUserList* pUserList);
		void TravFBVideoList(Json::Value& jvRoot, IVideoList* pIVideoList);
		void TravFBVideo(Json::Value& jvRoot, IVideo* pIVideo);
		void TravFBAlbumList(Json::Value& jvRoot, IAlbumList* pIAlbumList);
		void TravFBAlbum(Json::Value& jvRoot, IAlbum* pIAlbum);
		int TravFBProfile( Json::Value& jvRoot, IProfile* pIProfile, IError& iError );

		int TravFkrErr(Json::Value& jvRoot, IError& iError);
		void TravrFkrPhotoList( Json::Value &jvRoot, IPhotoList &iPhotoList);
		void TravFkrPhoto( Json::Value &jvRoot, IPhoto* pIPhoto );
		void TravFkrAlbumList( Json::Value& jvRoot, IAlbumList& iAlbumList );
		void TravFkrAlbum( Json::Value& item,IAlbum* pIAlbum );
		void TravFkrFriendList( Json::Value& jvRoot, IUserList& iUserList );
		void TravFkrFriend( Json::Value& item, IUser* pIUsr );
		void TravFkrUser( Json::Value& jvRoot, IUser& iUser );
		util::ILogger* m_pLogger;
		std::list<string> m_listFkrPhotSizes;
	};
}




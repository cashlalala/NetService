#pragma once
#include "IDataManager.h"
#include "IParser.h"
#include "LoggerMgr.h"
#include "SysTypes.h"
#include <list>
#include <json/json.h>

using util::IDataManager;
using systypes::SysMaps;

namespace util
{
	class CJsonCppMgr :
		public IDataManager, public IDataMgrFBOnly, public IDataMgrFkrOnly
	{
	public:
		CJsonCppMgr(void);
		virtual ~CJsonCppMgr(void);

		virtual int ParsePhotoList( IPhotoList& iPhotoList, string szInput, IError& iError ) ;

		virtual int ParsePhoto( IPhoto& iPhoto, string szInput, IError& iError  ) ;

		virtual int ParseUser(IUser& iUser, string szInput, IError& iError) ;

		virtual int ParseError(IError& iError, string szInput) ;

		virtual int ParseFriendList(IUserList& iUserList, string szInput, IError& iError  ) ;

		virtual int ParseVideoList( IVideoList&iVideoList, string szInput, IError& iError) ;

		virtual int ParseAlbumList(IAlbumList& iAlbumList, string szInput, IError& iError) ;

		virtual int ParseProfile(IProfile& iProfile, string szInput, IError& iError);

		virtual int ParseImageList(IImageList& listImage, string szInput, IError& iError) ;


		virtual int ParseFBSrouceSmall(SysList::Str2StrMapList& listMap, string szInput, IError& iError) ;

		virtual int ParseFkrFrob(string& szFrob, string szInput, IError& iError) ;

		virtual int ParseFkrAuthToken(SysMaps::Str2Str& szAuthToken, string szInput,IError& iError) ;

	private:
		util::ILogger* m_pLogger;
		util::IParser* m_pParser;
	};
}




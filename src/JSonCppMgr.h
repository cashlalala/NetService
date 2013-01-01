#pragma once
#include "IDataManager.h"
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

		virtual int ParsePhoto( string szInput, IPhoto& iPhoto, EnDataOwner enDataOwner, IError& iError  ) ;

		virtual int ParseUser(string szInput, IUser& iUser, EnDataOwner enDataOwner, IError& iError) ;

	private:
		//To keep the physical linkage isolated, don't specify the explicit type of the interface among the parameters.
		// Even the function name is specified with exact targets like "FB" "FLICKR";
		void TravFBPhotoList( Json::Value &jvRoot, IPhotoList &iPhotoList);
		int TravFBErr(Json::Value &jvRoot, IError& cFbErr);
		void TravFBPhoto( Json::Value &jvRoot, IPhoto* pIPhoto );
		void TravFBUser( Json::Value jvRoot, IUser& iUser );


	};
}


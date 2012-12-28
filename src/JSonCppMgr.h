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
		~CJsonCppMgr(void);

		virtual int ParsePhotoList( string szInput, IPhotoList& iPhotoList, EnDataOwner enDataOwner ) ;

		virtual int ParsePhoto( string szInput, IPhoto& iPhoto, EnDataOwner enDataOwner  ) ;

	private:
		void TravFBPhotoList( Json::Value &jvRoot, IPhotoList &iPhotoList );
	};
}


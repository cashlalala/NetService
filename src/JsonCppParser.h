#pragma once
#include "IParser.h"
#include <json/json.h>
#include <list>

namespace util
{
	class CJsonCppParser :
		public IParser
	{
	public:
		CJsonCppParser(void);
		~CJsonCppParser(void);

		virtual int GetValueAsInt( const char* lpcszFormat, ... );

		virtual bool GetValueAsBool( const char* lpcszFormat, ... );

		virtual string GetValueAsString( const char* lpcszFormat, ... );

		virtual int GetValueAsArrarySize(const char* lpcszFormat, ...) ;

		virtual bool IsObjectNull(const char* lpcszFormat, ...);

		virtual void GetObjectAsListRoot(const char* lpcszFormat, ...);

		virtual void StoreListRoot()  ;
		virtual void RestoreListRoot() ;
		virtual void ClearTop() ;

		virtual int Parse( string szSrc );

		virtual void ResetRoot() ;

	private:
		string MsgFormat(const char* lpszFormat, va_list args);
		Json::Value& GetObject(Json::Value& jvRoot, string szTarget);

		Json::Value m_jvRoot;
		Json::Value m_jvCurRoot;
		std::list<Json::Value> m_jvListRoot;
	};
}




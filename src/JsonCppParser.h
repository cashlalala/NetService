#pragma once
#include "IParser.h"
#include <json/json.h>

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

		virtual void GetObjectAsRoot(const char* llpcszFormat, ...) ;

		virtual int Parse( string szSrc );

		virtual void ResetParseRoot() ;

	private:
		string MsgFormat(const char* lpszFormat, va_list args);
		Json::Value& GetObject(Json::Value& jvRoot, string szTarget);

		Json::Value m_jvRoot;
		Json::Value m_jvCurRoot;
	};
}




#pragma once

#include<string>

using std::string;

namespace util
{
	struct IParser {
		virtual int Parse(string szSrc) = 0;

		virtual int GetValueAsInt(const char* lpcszFormat, ...) = 0;
		virtual bool GetValueAsBool(const char* lpcszFormat, ...) = 0;
		virtual string GetValueAsString(const char* lpcszFormat, ...) = 0;
		virtual int GetValueAsArrarySize(const char* lpcszFormat, ...) = 0;
		virtual bool IsObjectNull(const char* lpcszFormat, ...) = 0;

		virtual void ResetRoot() = 0;

		virtual void StoreListRoot() = 0 ;
		virtual void RestoreListRoot() = 0;
		virtual void ClearTop() = 0 ;

		virtual void GetObjectAsListRoot(const char* lpcszFormat, ...) = 0;
		
	};
}
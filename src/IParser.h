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

		virtual void StoreRoot() = 0 ;
		virtual void RestoreRoot() = 0;
		virtual void ClearBuffTop() = 0 ;

		virtual void GetObjectAsRoot(const char* lpcszFormat, ...) = 0;
		
	};
}
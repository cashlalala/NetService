#pragma once

#include <string>

using std::string;
using std::wstring;

namespace util
{
	class CStringHelper
	{
	public:
		static string Format(const char* lpcszFormat, ...);
		static std::wstring S2WS(const std::string& s);
	};
}




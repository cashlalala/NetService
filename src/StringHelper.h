#pragma once

#include <string>

using std::string;

namespace util
{
	class CStringHelper
	{
	public:
		static string Format(const char* lpcszFormat, ...);
	};
}




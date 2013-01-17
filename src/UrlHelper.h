#pragma once

#include <map>
#include <string>

#define ESCAPE_URL_STRING_LEN 3

using std::string;
using std::map;

namespace util
{
	class CUrlHelper
	{
	public:
		CUrlHelper(void);
		~CUrlHelper(void);

		static string EncodeUrl(const string& szUrl);

		static map<string,string> ToParamMap(const string& szUrl);
	};

}


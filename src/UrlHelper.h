#pragma once

#include <string>

#define ESCAPE_URL_STRING_LEN 3

using std::string;


class CUrlHelper
{
public:
	CUrlHelper(void);
	~CUrlHelper(void);

	static string EncodeUrl(const string& szUrl);
};

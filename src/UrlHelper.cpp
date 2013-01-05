#include "StdAfx.h"
#include "UrlHelper.h"
#include <windows.h>
#include <WinInet.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::wstring;

util::CUrlHelper::CUrlHelper(void)
{
}

util::CUrlHelper::~CUrlHelper(void)
{
}

string util::CUrlHelper::EncodeUrl( const string& szUrl )
{
	DWORD dwSize = (szUrl.length()*ESCAPE_URL_STRING_LEN)+1;
	char* lpszUrl = new char[dwSize];
	memset(lpszUrl,0x0, dwSize);	

	BOOL bResult = InternetCanonicalizeUrlA(szUrl.c_str(),lpszUrl, &dwSize, ICU_BROWSER_MODE);
	if(!bResult)
	{
		unsigned int dwErr = GetLastError();
		switch(dwErr)
		{
		case ERROR_BAD_PATHNAME:
			cout<< "ERROR_BAD_PATHNAME" << endl;
			break;
		case ERROR_INSUFFICIENT_BUFFER:
			cout<< "ERROR_INSUFFICIENT_BUFFER" << endl;
			break;
		case ERROR_INTERNET_INVALID_URL:
			cout<< "ERROR_INTERNET_INVALID_URL" << endl;
			break;
		case ERROR_INVALID_PARAMETER:
			cout<< "ERROR_INVALID_PARAMETER" << endl;
			break;
		default:
			cout<< "unknown error" << endl;
			break;
		}
	}
	string szRetUrl(lpszUrl);
	delete[] lpszUrl;
	return szRetUrl;
}

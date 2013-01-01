#include "StdAfx.h"
#include "UrlHelper.h"
#include <WinInet.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::wstring;

CUrlHelper::CUrlHelper(void)
{
}

CUrlHelper::~CUrlHelper(void)
{
}

string CUrlHelper::EncodeUrl( const string& szUrl )
{
	DWORD dwSize = (szUrl.length()*ESCAPE_URL_STRING_LEN)+1;
	char* lpszUrl = new char[dwSize];
	memset(lpszUrl,0x0, dwSize);	

	BOOL bResult = InternetCanonicalizeUrlA(szUrl.c_str(),lpszUrl, &dwSize, ICU_BROWSER_MODE);
	if(!bResult)
	{
		DWORD dwErr = GetLastError();
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

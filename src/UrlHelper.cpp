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

map<string,string> util::CUrlHelper::ToParamMap( const string& szUrl )
{
	char lpszParam[INTERNET_MAX_PATH_LENGTH+1];
	memset(lpszParam,0x0,sizeof(lpszParam));

	URL_COMPONENTSA urlComponents = {0};
	urlComponents.dwStructSize = sizeof(URL_COMPONENTSA);
	urlComponents.dwExtraInfoLength = INTERNET_MAX_PATH_LENGTH;
	urlComponents.lpszExtraInfo = lpszParam;
	BOOL bResult = InternetCrackUrlA(szUrl.c_str(), szUrl.size(), ICU_ESCAPE, &urlComponents);

	map<string,string> mapResult;
	char* pNextTok = NULL;
	char* pChar = strtok_s(lpszParam,"?&#", &pNextTok);
	while (pChar) 
	{
		string szToken(pChar);
		size_t nPos = szToken.find("=");
		mapResult[szToken.substr(0,nPos)] = szToken.substr(nPos+1);
		pChar = strtok_s(NULL,"?&#", &pNextTok);
	}	
	return mapResult;
}

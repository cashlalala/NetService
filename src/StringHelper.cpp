#include "StdAfx.h"
#include "StringHelper.h"
#include <vector>

using std::vector;
using namespace util;

string CStringHelper::Format( const char* fmt, ... )
{
	std::string strResult=""; 
	if (NULL != fmt) 
	{ 
		va_list marker = NULL; 
		va_start(marker, fmt); 

		size_t nLength = _vscprintf(fmt, marker) + 1; 
		std::vector<char> vBuffer(nLength, '\0'); 

		int nRet = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, fmt, marker); 
		if (nRet > 0) 
		{
			strResult = &vBuffer[0]; 

		} 

		va_end(marker); 
	} 
	return strResult; 
}

std::wstring CStringHelper::S2WS(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
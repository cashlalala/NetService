#pragma once
#include "SysTypes.h"
#include <string>

namespace util
{
	class CCodecHelper
	{
	public:
		static CCodecHelper* GetInstance();

		std::string ToMD5(const systypes::SysMaps::Str2Str& param, const char* sharedSecret);
		systypes::SysMaps::Str2Str CreateApiSignatureHMACSHA1(const systypes::SysMaps::Str2Str& param, 
			const string& serviceSharedSecret,
			const string& apiKey,
			const string& oauthToken,
			const string& tokenSecret = "",
			const string& httpMethod = "GET",
			const string& url = "",
			bool bReturnOAuthParam = false);

		std::string ToBase64( const std::string& szSrc);
		std::string FromBase64(const std::string& szSrc);

		std::string ToHMACSHA1( const std::string& keyBytes, const std::string& data );

	private:
		typedef struct {
			unsigned long         i[2];
			unsigned long        buf[4];
			unsigned char in[64];
			unsigned char digest[16];
		} MD5_CTX;

		typedef void (__stdcall *pfnMD5Init) (MD5_CTX*);
		typedef void (__stdcall *pfnMD5Final) (MD5_CTX*);
		typedef void (__stdcall *pfnMD5Update) (MD5_CTX*, const unsigned char*, unsigned int len);

	private: 
		CCodecHelper(void);
		~CCodecHelper(void);
		void SetupLookup16();

		pfnMD5Init      m_pfnMD5Init;
		pfnMD5Final     m_pfnMD5Final;
		pfnMD5Update    m_pfnMD5Update;

		static const char	Base64Digits[];
		static unsigned char LookupDigits[];
		static unsigned short* m_pusLookup16;
		

	};
}




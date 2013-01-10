#include "StdAfx.h"
#include "CodecHelper.h"
#include "OAuthHelper.h"

#include <assert.h>
#include <Wincrypt.h>
#pragma comment (lib, "Crypt32.lib")

#define SIZEOF(x) (sizeof(x)/sizeof(*x))

//lock symbol in file scope
static HMODULE         m_hCryptDll = NULL;

const char util::CCodecHelper::Base64Digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char util::CCodecHelper::LookupDigits[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //gap: ctrl chars
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //gap: ctrl chars
	0,0,0,0,0,0,0,0,0,0,0,           //gap: spc,!"#$%'()*
	62,                   // +
	0, 0, 0,             // gap ,-.
	63,                   // /
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // 0-9
	0, 0, 0,             // gap: :;<
	99,                   //  = (end padding)
	0, 0, 0,             // gap: >?@
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,
	17,18,19,20,21,22,23,24,25, // A-Z
	0, 0, 0, 0, 0, 0,    // gap: [\]^_`
	26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,
	43,44,45,46,47,48,49,50,51, // a-z    
	0, 0, 0, 0,          // gap: {|}~ (and the rest...)
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

unsigned short* util::CCodecHelper::m_pusLookup16 = NULL;

util::CCodecHelper::CCodecHelper(void)
{
	m_hCryptDll = LoadLibrary(TEXT("Cryptdll.dll"));
	m_pfnMD5Init = (pfnMD5Init)GetProcAddress(m_hCryptDll, "MD5Init");
	m_pfnMD5Final = (pfnMD5Final)GetProcAddress(m_hCryptDll, "MD5Final");
	m_pfnMD5Update = (pfnMD5Update)GetProcAddress(m_hCryptDll, "MD5Update");
}

//It's necessary to be called, so we claim the static instance instead of a pointer 
util::CCodecHelper::~CCodecHelper(void)
{
	if (m_hCryptDll != 0)
		FreeLibrary(m_hCryptDll);
}

util::CCodecHelper* util::CCodecHelper::GetInstance()
{
	static util::CCodecHelper cCodecHelper;
	return &cCodecHelper;
}

std::string util::CCodecHelper::ToMD5( const systypes::SysMaps::Str2Str& param, const char* sharedSecret)
{
	assert(sharedSecret);
	MD5_CTX md5Ctx;
	m_pfnMD5Init(&md5Ctx);
	m_pfnMD5Update(&md5Ctx, (unsigned char*)sharedSecret, (unsigned int)strlen(sharedSecret));
	systypes::SysMaps::Str2Str::const_iterator    iter = param.begin();
	systypes::SysMaps::Str2Str::const_iterator    end = param.end();
	for (; iter != end; ++iter) {
		m_pfnMD5Update(&md5Ctx, (unsigned char*)(iter->first.c_str()), (unsigned int)iter->first.length());
		m_pfnMD5Update(&md5Ctx, (unsigned char*)(iter->second.c_str()), (unsigned int)iter->second.length());
	}
	m_pfnMD5Final(&md5Ctx);

	//signature.clear();
	char    tmpSignature[40] = {0};
	for (int i = 0; i < 16; ++i) {
		char    hexStr[4] = {0};
		sprintf_s(hexStr, 4, "%02x", md5Ctx.digest[i]);
		strcat_s(tmpSignature, 40, hexStr);
	}
	//signature = tmpSignature;
	return string(tmpSignature);
}


//int util::CCodecHelper::ToBase64( const BYTE* pSrc, int nLenSrc, char* pDst, int nLenDst )
std::string util::CCodecHelper::ToBase64( const std::string& szSrc)
{
	std::string szDst;

	int nLenSrc = szSrc.size();
	unsigned char* pOriSrc = (unsigned char*)calloc(nLenSrc+1,sizeof(unsigned char));
	unsigned char* pSrc = pOriSrc;
	strcpy_s((char*)pSrc,nLenSrc+1,szSrc.c_str());

	int nLenOut= ((nLenSrc+2)/3)*4; // 4 out for every 3 in, rounded up
	char* pOriDst = (char*)calloc(nLenOut+1,sizeof(char));
	char* pDst = pOriDst;

	DWORD* pdwDst= (DWORD*)pDst;
	while( nLenSrc > 2 ) {
		DWORD n= pSrc[0];  // xxx1 // roll the data in...
		n <<= 8;           // xx1x
		n |= pSrc[1];      // xx12  
		n <<= 8;           // x12x
		n |= pSrc[2];      // x123  

		BYTE m4= n & 0x3f;  n >>= 6;  // roll it out, 6 bits at a time
		BYTE m3= n & 0x3f;  n >>= 6;
		BYTE m2= n & 0x3f;  n >>= 6;
		BYTE m1= n & 0x3f;  

		n  = Base64Digits[m4];  n <<= 8; 
		n |= Base64Digits[m3];  n <<= 8;
		n |= Base64Digits[m2];  n <<= 8;
		n |= Base64Digits[m1]; 

		*pdwDst++ = n;   // write four bytes in one operation
		nLenSrc -= 3;
		pSrc += 3;
	}
	// -------------- end of buffer special handling
	pDst= (char*)pdwDst;
	if ( nLenSrc > 0 ) {  // some left after last triple
		int n1= (*pSrc & 0xfc) >> 2;
		int n2= (*pSrc & 0x03) << 4;
		if (nLenSrc > 1 ) {  
			pSrc++;
			n2 |= (*pSrc & 0xf0) >> 4;
		}
		*pDst++ = Base64Digits[n1]; // encode at least 2 outputs
		*pDst++ = Base64Digits[n2];
		if (nLenSrc == 2) {  // 2 src bytes left to encode, output xxx=
			int n3= (*pSrc & 0x0f) << 2;
			pSrc++;
			n3 |= (*pSrc & 0xc0) >> 6;
			*pDst++ = Base64Digits[n3];
		}
		if (nLenSrc == 1) {  // 1 src byte left to encode, output xx==
			*pDst++ = '=';
		}
		*pDst++ = '=';
	}

	szDst = string(pOriDst);
	if (pOriDst)
		free(pOriDst);
	if (pOriSrc)
		free(pOriSrc);

	return szDst;
}

std::string util::CCodecHelper::FromBase64( const std::string& szSrc)
{
	std::string szDst;

	int nLenSrc = szSrc.size();
	unsigned char* pOriSrc = (unsigned char*)calloc(nLenSrc+1,sizeof(unsigned char));
	unsigned char* pSrc = pOriSrc;
	strcpy_s((char*)pSrc,nLenSrc+1,szSrc.c_str());

	int nMaxLen = ((nLenSrc/4 + 1/* for ceiling*/)-1) * 3 + 1 /* for tailer 0*/;
	char* pOriDst = (char*) calloc(nMaxLen ,sizeof(char));
	char* pDst  = pOriDst;

	if ( NULL==m_pusLookup16 ) SetupLookup16();  // see below
	int nLenOut= 0;

	int nLoopMax= (nLenSrc/4)-1;
	WORD* pwSrc= (WORD*)pSrc;
	for( int j=0; j<nLoopMax; j++ ) {
		WORD s1= m_pusLookup16[ pwSrc[0] ];  // translate two "digits" at once
		WORD s2= m_pusLookup16[ pwSrc[1] ];  // ... and two more

		DWORD n32;
		n32  = s1;         // xxxxxxxx xxxxxxxx xx111111 222222xx
		n32 <<= 10;        // xxxxxxxx 11111122 2222xxxx xxxxxxxx
		n32 |= s2 >> 2;    // xxxxxxxx 11111122 22223333 33444444

		BYTE b3= ( n32 & 0x00ff ); n32 >>= 8;  // in reverse (WORD order)
		BYTE b2= ( n32 & 0x00ff ); n32 >>= 8;
		BYTE b1= ( n32 & 0x00ff ); 

		// *pDst++ = b1;  *pDst++ = b2;  *pDst++ = b3;  //slighly slower

		pDst[0]= b1;  // slightly faster
		pDst[1]= b2;
		pDst[2]= b3; 

		pwSrc += 2;
		pDst += 3;
	}
	nLenOut= ((nLenSrc/4)-1) * 3;

	//-------------------- special handling outside of loop for end
	WORD s1= m_pusLookup16[ pwSrc[0] ];
	WORD s2= m_pusLookup16[ pwSrc[1] ]; 

	DWORD n32;
	n32  = s1;      
	n32 <<= 10;
	n32 |= s2 >> 2;

	BYTE b3= ( n32 & 0x00ff ); n32 >>= 8;
	BYTE b2= ( n32 & 0x00ff ); n32 >>= 8;
	BYTE b1= ( n32 & 0x00ff ); 

	*pDst++ = b1;  nLenOut++;
	if (b2 != 99)  {
		*pDst++ = b2;  nLenOut++;
	}
	if (b3 != 99) {
		*pDst++ = b3;  nLenOut++;
	}

	int nOffset = pDst - pOriDst;//for debug use

	szDst = string(pOriDst);
	if (pOriDst)
		free(pOriDst);
	if (pOriSrc)
		free(pOriSrc);
	return szDst;

}


void util::CCodecHelper::SetupLookup16()
{
	int nLenTbl= 256*256;            // yes, the table is 128Kb!
	if (NULL==m_pusLookup16) {
		m_pusLookup16= new WORD[nLenTbl];
	}
	WORD* p= m_pusLookup16;
	for (int j= 0; j<256; j++ ) {
		for (int k= 0; k<256; k++ ) {
			WORD w;
			w  = LookupDigits[k] << 8;
			w |= LookupDigits[j] << 2 ; // pre-shifted! See notes
			*p++ = w;
		}
	}
}

string util::CCodecHelper::ToHMACSHA1( const string& keyBytes, const string& data )
{
	// based on http://msdn.microsoft.com/en-us/library/aa382379%28v=VS.85%29.aspx

	string hash;

	//--------------------------------------------------------------------
	// Declare variables.
	//
	// hProv:           Handle to a cryptographic service provider (CSP). 
	//                  This example retrieves the default provider for  
	//                  the PROV_RSA_FULL provider type.  
	// hHash:           Handle to the hash object needed to create a hash.
	// hKey:            Handle to a symmetric key. This example creates a 
	//                  key for the RC4 algorithm.
	// hHmacHash:       Handle to an HMAC hash.
	// pbHash:          Pointer to the hash.
	// dwDataLen:       Length, in bytes, of the hash.
	// Data1:           Password string used to create a symmetric key.
	// Data2:           Message string to be hashed.
	// HmacInfo:        Instance of an HMAC_INFO structure that contains 
	//                  information about the HMAC hash.
	// 
	HCRYPTPROV  hProv       = NULL;
	HCRYPTHASH  hHash       = NULL;
	HCRYPTKEY   hKey        = NULL;
	HCRYPTHASH  hHmacHash   = NULL;
	PBYTE       pbHash      = NULL;
	DWORD       dwDataLen   = 0;
	//BYTE        Data1[]     = {0x70,0x61,0x73,0x73,0x77,0x6F,0x72,0x64};
	//BYTE        Data2[]     = {0x6D,0x65,0x73,0x73,0x61,0x67,0x65};
	HMAC_INFO   HmacInfo;

	//--------------------------------------------------------------------
	// Zero the HMAC_INFO structure and use the SHA1 algorithm for
	// hashing.

	ZeroMemory(&HmacInfo, sizeof(HmacInfo));
	HmacInfo.HashAlgid = CALG_SHA1;

	//--------------------------------------------------------------------
	// Acquire a handle to the default RSA cryptographic service provider.

	if (!CryptAcquireContext(
		&hProv,                   // handle of the CSP
		NULL,                     // key container name
		NULL,                     // CSP name
		PROV_RSA_FULL,            // provider type
		CRYPT_VERIFYCONTEXT))     // no key access is requested
	{
		/*_TRACE(" Error in AcquireContext 0x%08x \n",
			GetLastError());*/
		goto ErrorExit;
	}

	//--------------------------------------------------------------------
	// Derive a symmetric key from a hash object by performing the
	// following steps:
	//    1. Call CryptCreateHash to retrieve a handle to a hash object.
	//    2. Call CryptHashData to add a text string (password) to the 
	//       hash object.
	//    3. Call CryptDeriveKey to create the symmetric key from the
	//       hashed password derived in step 2.
	// You will use the key later to create an HMAC hash object. 

	if (!CryptCreateHash(
		hProv,                    // handle of the CSP
		CALG_SHA1,                // hash algorithm to use
		0,                        // hash key
		0,                        // reserved
		&hHash))                  // address of hash object handle
	{
		/*_TRACE("Error in CryptCreateHash 0x%08x \n",
			GetLastError());*/
		goto ErrorExit;
	}

	if (!CryptHashData(
		hHash,                    // handle of the hash object
		(BYTE*)keyBytes.c_str(),                    // password to hash
		keyBytes.size(),            // number of bytes of data to add
		0))                       // flags
	{
		/*_TRACE("Error in CryptHashData 0x%08x \n", 
			GetLastError());*/
		goto ErrorExit;
	}

	// key creation based on 
	// http://mirror.leaseweb.com/NetBSD/NetBSD-release-5-0/src/dist/wpa/src/crypto/crypto_cryptoapi.c
	struct {
		BLOBHEADER hdr;
		DWORD len;
		BYTE key[1024]; // TODO might want to dynamically allocate this, Should Be Fine though
	} key_blob;

	key_blob.hdr.bType = PLAINTEXTKEYBLOB;
	key_blob.hdr.bVersion = CUR_BLOB_VERSION;
	key_blob.hdr.reserved = 0;
	/*
	* Note: RC2 is not really used, but that can be used to
	* import HMAC keys of up to 16 byte long.
	* CRYPT_IPSEC_HMAC_KEY flag for CryptImportKey() is needed to
	* be able to import longer keys (HMAC-SHA1 uses 20-byte key).
	*/
	key_blob.hdr.aiKeyAlg = CALG_RC2;
	key_blob.len = keyBytes.size();
	ZeroMemory(key_blob.key, sizeof(key_blob.key));

	assert(keyBytes.size() <= SIZEOF(key_blob.key));
	CopyMemory(key_blob.key, keyBytes.c_str(), min(keyBytes.size(), SIZEOF(key_blob.key)));

	if (!CryptImportKey(
		hProv, 
		(BYTE *)&key_blob,
		sizeof(key_blob), 
		0, 
		CRYPT_IPSEC_HMAC_KEY,
		&hKey)) 
	{
		//_TRACE("Error in CryptImportKey 0x%08x \n", GetLastError());
		goto ErrorExit;
	}

	//--------------------------------------------------------------------
	// Create an HMAC by performing the following steps:
	//    1. Call CryptCreateHash to create a hash object and retrieve 
	//       a handle to it.
	//    2. Call CryptSetHashParam to set the instance of the HMAC_INFO 
	//       structure into the hash object.
	//    3. Call CryptHashData to compute a hash of the message.
	//    4. Call CryptGetHashParam to retrieve the size, in bytes, of
	//       the hash.
	//    5. Call malloc to allocate memory for the hash.
	//    6. Call CryptGetHashParam again to retrieve the HMAC hash.

	if (!CryptCreateHash(
		hProv,                    // handle of the CSP.
		CALG_HMAC,                // HMAC hash algorithm ID
		hKey,                     // key for the hash (see above)
		0,                        // reserved
		&hHmacHash))              // address of the hash handle
	{
		/*_TRACE("Error in CryptCreateHash 0x%08x \n", 
			GetLastError());*/
		goto ErrorExit;
	}

	if (!CryptSetHashParam(
		hHmacHash,                // handle of the HMAC hash object
		HP_HMAC_INFO,             // setting an HMAC_INFO object
		(BYTE*)&HmacInfo,         // the HMAC_INFO object
		0))                       // reserved
	{
		/*_TRACE("Error in CryptSetHashParam 0x%08x \n", 
			GetLastError());*/
		goto ErrorExit;
	}

	if (!CryptHashData(
		hHmacHash,                // handle of the HMAC hash object
		(BYTE*)data.c_str(),                    // message to hash
		data.size(),            // number of bytes of data to add
		0))                       // flags
	{
		/*_TRACE("Error in CryptHashData 0x%08x \n", 
			GetLastError());*/
		goto ErrorExit;
	}

	//--------------------------------------------------------------------
	// Call CryptGetHashParam twice. Call it the first time to retrieve
	// the size, in bytes, of the hash. Allocate memory. Then call 
	// CryptGetHashParam again to retrieve the hash value.

	if (!CryptGetHashParam(
		hHmacHash,                // handle of the HMAC hash object
		HP_HASHVAL,               // query on the hash value
		NULL,                     // filled on second call
		&dwDataLen,               // length, in bytes, of the hash
		0))
	{
		/*_TRACE("Error in CryptGetHashParam 0x%08x \n", 
			GetLastError());*/
		goto ErrorExit;
	}

	pbHash = (BYTE*)malloc(dwDataLen);
	if(NULL == pbHash) 
	{
		//_TRACE("unable to allocate memory\n");
		goto ErrorExit;
	}

	if (!CryptGetHashParam(
		hHmacHash,                 // handle of the HMAC hash object
		HP_HASHVAL,                // query on the hash value
		pbHash,                    // pointer to the HMAC hash value
		&dwDataLen,                // length, in bytes, of the hash
		0))
	{
		//_TRACE("Error in CryptGetHashParam 0x%08x \n", GetLastError());
		goto ErrorExit;
	}

	for(DWORD i = 0 ; i < dwDataLen ; i++) 
	{
		hash.push_back((char)pbHash[i]);
	}

	// Free resources.
	// lol goto
ErrorExit:
	if(hHmacHash)
		CryptDestroyHash(hHmacHash);
	if(hKey)
		CryptDestroyKey(hKey);
	if(hHash)
		CryptDestroyHash(hHash);    
	if(hProv)
		CryptReleaseContext(hProv, 0);
	if(pbHash)
		free(pbHash);

	return hash;
}

systypes::SysMaps::Str2Str util::CCodecHelper::CreateApiSignatureHMACSHA1( const systypes::SysMaps::Str2Str& param, const string& serviceSharedSecret, const string& apiKey, const string& oauthToken, const string& tokenSecret /*= ""*/, const string& httpMethod /*= "GET"*/, const string& url /*= ""*/, bool bReturnOAuthParam /*= false*/ )
{
	assert(serviceSharedSecret.length() > 0);
	assert(apiKey.length() > 0);
	//assert(oauthToken.length() > 0);

	string timestamp = util::COAuthHelper::CreateTimestamp();
	string nonce = util::COAuthHelper::CreateNonce();

	systypes::SysMaps::Str2Str oauthParameters;

	oauthParameters["oauth_timestamp"] = timestamp;
	oauthParameters["oauth_nonce"] = nonce;
	oauthParameters["oauth_version"] = "1.0";
	oauthParameters["oauth_signature_method"] = "HMAC-SHA1";
	oauthParameters["oauth_consumer_key"] = apiKey;

	if (!oauthToken.empty())
	{
		oauthParameters["oauth_token"] = oauthToken;
	}

	systypes::SysMaps::Str2Str allParameters = oauthParameters;

	allParameters.insert(param.begin(), param.end());

	string normalUrl = util::COAuthHelper::NormalizeUrl(url);
	string normalizedParameters = util::COAuthHelper::NormalizeRequestParameters(allParameters);
	string signatureBase = util::COAuthHelper::ConcatenateRequestElements(httpMethod, normalUrl, normalizedParameters);

	string signature = util::COAuthHelper::CreateSignature(signatureBase, serviceSharedSecret, tokenSecret);
	allParameters["oauth_signature"] = signature;
	oauthParameters["oauth_signature"] = signature;

	if(bReturnOAuthParam)
	{
		return oauthParameters;
	}
	else
	{
		return allParameters;
	}
}

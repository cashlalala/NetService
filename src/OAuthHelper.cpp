#include "StdAfx.h"
#include "OAuthHelper.h"
#include "CodecHelper.h"
#include "UrlHelper.h"

#include <time.h>
#include <list>
#include <string>
#include <Wininet.h>

using namespace util;
using namespace std;
using namespace systypes;

#define SIZEOF(x) (sizeof(x)/sizeof(*x))

COAuthHelper::COAuthHelper(void)
{
}


COAuthHelper::~COAuthHelper(void)
{
}

string COAuthHelper::CreateTimestamp() 
{
	__time64_t utcNow;
	__time64_t ret = _time64(&utcNow);
	_ASSERTE(ret != -1);

	char buf[100] = {};
	sprintf_s(buf, SIZEOF(buf), "%I64u", utcNow);

	return buf;
}

string COAuthHelper::CreateNonce() 
{
	char ALPHANUMERIC[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string nonce;

	srand(time(NULL));

	for(int i = 0; i <= 16; ++i)
	{
		nonce += ALPHANUMERIC[rand() % (SIZEOF(ALPHANUMERIC) - 1)]; // don't count null terminator in array
	}
	return nonce;
}

string COAuthHelper::NormalizeUrl( const string& url )
{
	char scheme[1024*4] = {};
	char host[1024*4] = {};
	char path[1024*4] = {};

	URL_COMPONENTSA components = { sizeof(URL_COMPONENTSA) };

	components.lpszScheme = scheme;
	components.dwSchemeLength = SIZEOF(scheme);

	components.lpszHostName = host;
	components.dwHostNameLength = SIZEOF(host);

	components.lpszUrlPath = path;
	components.dwUrlPathLength = SIZEOF(path);

	string normalUrl = url;

	BOOL crackUrlOk = InternetCrackUrlA(url.c_str(), url.size(), 0, &components);
	_ASSERTE(crackUrlOk);
	if(crackUrlOk)
	{
		char port[10] = {};

		// The port number must only be included if it is non-standard
		if((Compare(scheme, "http", false) && components.nPort != 80) || 
			(Compare(scheme, "https", false) && components.nPort != 443))
		{
			sprintf_s(port, SIZEOF(port), ":%u", components.nPort);
		}

		// InternetCrackUrl includes ? and # elements in the path, 
		// which we need to strip off
		string pathOnly = path;
		string::size_type q = pathOnly.find_first_of("#?");
		if(q != string::npos)
		{
			pathOnly = pathOnly.substr(0, q);
		}

		normalUrl = string(scheme) + "://" + host + port + pathOnly;
	}
	return normalUrl;
}

string COAuthHelper::NormalizeRequestParameters( const SysMaps::Str2Str& requestParameters ) 
{
	list<string> sorted;
	for(SysMaps::Str2Str::const_iterator it = requestParameters.begin(); 
		it != requestParameters.end(); 
		++it)
	{
		string param = it->first + "=" + it->second;
		sorted.push_back(param);
	}
	sorted.sort();

	string params;
	for(list<string>::iterator it = sorted.begin(); it != sorted.end(); ++it)
	{
		if(params.size() > 0)
		{
			params += "&";
		}
		params += *it;
	}

	return params;
}

//string urlencode(const string &c)
//{
//	string escaped;
//	int max = c.length();
//	for(int i=0; i<max; i++)
//	{
//		if ( (48 <= c[i] && c[i] <= 57) ||//0-9
//			(65 <= c[i] && c[i] <= 90) ||//ABC...XYZ
//			(97 <= c[i] && c[i] <= 122) || //abc...xyz
//			(c[i]=='~' || c[i]=='-' || c[i]=='_' || c[i]=='.')
//			)
//		{
//			escaped.append( &c[i], 1);
//		}
//		else
//		{
//			char buffer[5] = {0};
//			sprintf_s(buffer, 5, "%%%02X", (unsigned char)(c[i]));
//			escaped.append(buffer);
//		}
//	}
//	
//	return escaped;
//}
//
//string UrlEncode( const string& url ) 
//{
//	// multiple encodings r sux
//	return urlencode((url));
//}

string COAuthHelper::ConcatenateRequestElements( const string& httpMethod, string url, const string& parameters ) 
{
	//string escapedUrl = UrlEncode(url);
	//string escapedParameters = UrlEncode(parameters);
	string escapedUrl = CUrlHelper::EncodeUrl(url);
	string escapedParameters = CUrlHelper::EncodeUrl(parameters);

	string ret = httpMethod + "&" + escapedUrl + "&" + escapedParameters;
	return ret;
}

string COAuthHelper::CreateSignature( const string& signatureBase, const string& consumerSecret, const string& requestTokenSecret ) 
{
	// URL encode key elements
	string escapedConsumerSecret = CUrlHelper::EncodeUrl(consumerSecret);
	string escapedTokenSecret = CUrlHelper::EncodeUrl(requestTokenSecret);

	string keyBytes = escapedConsumerSecret + "&" + escapedTokenSecret;
	string data = signatureBase;
	CCodecHelper* pCodecHelper = CCodecHelper::GetInstance();
	string hash = pCodecHelper->ToHMACSHA1(keyBytes, data);
	string signature = pCodecHelper->ToBase64(hash);
	return signature;
}

string COAuthHelper::BuildHeader( const SysMaps::Str2Str &parameters ) 
{
	string query;

	for(SysMaps::Str2Str::const_iterator it = parameters.begin(); 
		it != parameters.end(); 
		++it)
	{


		if(it != parameters.begin())
		{
			query += ",";
		}

		string pair;
		pair += it->first + "=\"" + CUrlHelper::EncodeUrl(it->second) + "\"";
		query += pair;
	}	
	return query;
}
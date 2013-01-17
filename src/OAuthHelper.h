#pragma once

#include "SysTypes.h"

using namespace systypes;

namespace util
{
	class COAuthHelper
	{
	public:
		COAuthHelper(void);
		~COAuthHelper(void);

		static string BuildHeader( const SysMaps::Str2Str &parameters ) ;
		static string CreateSignature( const string& signatureBase, const string& consumerSecret, const string& requestTokenSecret ) ;
		static string ConcatenateRequestElements( const string& httpMethod, string url, const string& parameters ) ;
		static string NormalizeRequestParameters( const SysMaps::Str2Str& requestParameters ) ;
		static string NormalizeUrl( const string& url );
		static string CreateNonce() ;
		static string CreateTimestamp() ;

	private:
		//---------------------------------------------------------------------------
		static bool Compare(const std::string& one, const std::string& two, bool caseSensitive)
		{
			return caseSensitive ? (_stricmp(one.c_str(), two.c_str()) == 0) : (_stricmp(one.c_str(), two.c_str()) == 0);
		}
	};
}




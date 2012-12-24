
#include <map>
#include <string>

using std::map;

struct ISocialNetworkService
{
	virtual map<string,string> PrepareParams(string szMethod, map<string,string> params, bool bSignature) = 0;

	virtual void CheckError(string szRootNode) = 0;

	/*
	* Login Functions
	*/
	virtual string GetLoginURL(string params = "") = 0;

};
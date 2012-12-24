
#include <map>
#include <string>

using std::map;

struct ISocialNetworkService
{
	virtual map<string,string> prepareParams(string szMethod, map<string,string> params, bool bSignature) = 0;
};
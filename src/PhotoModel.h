#pragma once

#include <string>
#include <map>

using std::map;
using std::string;

class CPhotoModel
{

public:
	CPhotoModel(void);
	~CPhotoModel(void);

private:
	map<string,string> m_mapPhotoModel;
};

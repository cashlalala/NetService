#pragma once
#include "IPhotoModel.h"
#include <string>

using std::string;
using namespace model;

namespace util
{
	typedef enum {
		Json,
		Xml
	} EnParser;

	struct IDataParser {
		virtual IPhotoList ParsePhotoList(string szReply) = 0;
		virtual IPhoto ParsePhoto(string szReply) = 0;
	};
}


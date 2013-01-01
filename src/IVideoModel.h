#pragma once

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{
	struct IVideoFormat{
		virtual ~IVideoFormat() {};
		int nHeight;
		int nWidth;
		string szThumbNail;
	};

	struct IVideo{
		virtual ~IVideo() {};
		string id;
		string szSource;
		string szThumbNail;
		list<IVideoFormat> listFormat;
	};

	struct IVideoList : public list<IVideo>{
		virtual ~IVideoList() {};
		string szNext;
		string szPrevious;
	};

}
#pragma once

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{
	struct IVideoFormat{
		virtual ~IVideoFormat() = 0 ;
		int nHeight;
		int nWidth;
		string szThumbNail;
	};

	inline IVideoFormat::~IVideoFormat(){};

	struct IVideo{
		virtual ~IVideo() =0;
		string id;
		string szSource;
		string szThumbNail;
		list<IVideoFormat*> listFormat;
	};

	inline IVideo::~IVideo(){};

	struct IVideoList {
		virtual ~IVideoList() =0;
		list<IVideo*> listVideo;
		string szNext;
		string szPrevious;
	};

	inline IVideoList::~IVideoList(){};

}
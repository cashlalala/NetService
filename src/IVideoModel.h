#pragma once

#include "IModel.h"

#include <string>
#include <list>

using std::list;
using std::string;

namespace model
{
	struct IVideoFormat : public IModel{
		virtual ~IVideoFormat() = 0 ;
		int nHeight;
		int nWidth;
		string szThumbNail;
	};

	inline IVideoFormat::~IVideoFormat(){};

	struct IVideo : public IModel{
		virtual ~IVideo() =0;
		string szId;
		string szSource;
		string szThumbNail;
		list<IVideoFormat*> listFormat;
	};

	inline IVideo::~IVideo()
	{
		SAFE_DELETE_LIST(list<IVideoFormat*>,listFormat)
	};

	struct IVideoList :  public IModel{
		virtual ~IVideoList() =0;
		list<IVideo*> listVideo;
		string szNext;
		string szPrevious;
	};

	inline IVideoList::~IVideoList()
	{
		SAFE_DELETE_LIST(list<IVideo*>,listVideo)
	};

}
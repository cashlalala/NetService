#pragma once
#include "IParseRuler.h"
#include "IModel.h"

#include <string>
#include <list>

using std::list;
using std::string;
using namespace util;

namespace model
{
	struct IVideoFormat : 
		public IModel, public IVideoFormatParsable
	{
		virtual ~IVideoFormat() = 0 ;
		int nHeight;
		int nWidth;
		string szThumbNail;
		virtual void AcceptVideoFormatParser(IVideoFormatParseRuler& cVideoFormatParser) {};
	};

	inline IVideoFormat::~IVideoFormat(){};

	struct IVideo : 
		public IModel, public IVideoParsable
	{
		virtual ~IVideo() =0;
		string szId;
		string szSource;
		string szThumbNail;
		list<IVideoFormat*> listFormat;
		virtual void AcceptVideoParser( IVideoParseRuler& cVideoParser ) {}
	};

	inline IVideo::~IVideo()
	{
		SAFE_DELETE_LIST(list<IVideoFormat*>,listFormat)
	};

	struct IVideoList :  
		public IPagedList<IVideo*>, public IVideoListParsable
	{
		virtual ~IVideoList() =0;
		virtual void AcceptVideoListParser( IVideoListParseRuler& cVideoListParser ) {};
	};

	inline IVideoList::~IVideoList()
	{
		//SAFE_DELETE_LIST(list<IVideo*>,listVideo)
	};

}
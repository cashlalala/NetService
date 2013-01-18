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
	struct IAlbum : 
		public IModel, public IAlbumParsable
	{
		virtual ~IAlbum() = 0;
		string szId;
		string szCoverPhotoId;
		string szThumbNail;
		string szName;
		int nCount;
		virtual void AcceptAlbumParser(IAlbumParseRuler& cAlbumParser) {};
	};

	inline IAlbum::~IAlbum(){};

	struct IAlbumList: 
		public IPagedList<model::IAlbum*>, public IAlbumListParsable
	{
		virtual ~IAlbumList() = 0;
		virtual void AcceptAlbumListParser(IAlbumListParseRuler& cAlbumListParser) {};
	};

	inline IAlbumList::~IAlbumList()
	{
	};

}
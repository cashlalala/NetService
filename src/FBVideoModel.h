#pragma once

#include "IVideoModel.h"

namespace model
{
	class CFBVideoFormat : public IVideoFormat
	{
	public:
		CFBVideoFormat(void);
		virtual ~CFBVideoFormat(void);
		string szEmbedHtml;
	};


	class CFBVideo :
		public IVideo
	{
	public:
		CFBVideo(void);
		virtual ~CFBVideo(void);
		string szEmbedHtml;
	};

	class CFBVideoList : public IVideoList
	{
	public:
		CFBVideoList(void);
		virtual ~CFBVideoList(void);

	};
}



#pragma once

#include "IVideoModel.h"

namespace model
{
	struct CFBVideoFormat : public IVideoFormat
	{
		virtual ~CFBVideoFormat(void){};
		string szEmbedHtml;
	};


	struct CFBVideo :
		public IVideo
	{
		virtual ~CFBVideo(void){};
		string szEmbedHtml;
	};

	struct CFBVideoList : public IVideoList
	{
		virtual ~CFBVideoList(void){};
	};
}



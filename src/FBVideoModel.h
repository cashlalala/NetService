#pragma once

#include "IVideoModel.h"

namespace model
{
	struct CFBVideoFormat : public IVideoFormat
	{
		virtual ~CFBVideoFormat(void){};
		string szEmbedHtml;
		void AcceptVideoFormatParser(IVideoFormatParseRuler& cVideoFormatParser) {cVideoFormatParser.Traverse(*this);}
	};


	struct CFBVideo :
		public IVideo
	{
		virtual ~CFBVideo(void){};
		string szEmbedHtml;
		void AcceptVideoParser( IVideoParseRuler& cVideoParser ) {cVideoParser.Traverse(*this);}
	};

	struct CFBVideoList : public IVideoList
	{
		virtual ~CFBVideoList(void){};
		void AcceptVideoListParser( IVideoListParseRuler& cVideoListParser ) {cVideoListParser.Traverse(*this);}
	};
}



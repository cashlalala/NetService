#pragma once

#include "IParseRuler.h"
#include <json/json.h>

namespace util
{
	class CImageListParseRuler : public IImageListParseRuler 
	{
	public:
		CImageListParseRuler();

		CImageListParseRuler(Json::Value& jvRoot);

		virtual void Traverse( CFBImageList& cFBImageList ) ;

		virtual void Traverse( CFkrImageList& cFkrImageList ) ;

		virtual void SetExecutor(Json::Value& jvRoot);
	private:
		Json::Value m_jvRoot;
	};

	class CImageParseRuler : public IImageParseRuler 
	{
	public:
		CImageParseRuler();

		CImageParseRuler(Json::Value& jvRoot);

		virtual void Traverse( CFBImage& cFBImage ) ;

		virtual void Traverse( CFkrImage& cFkrImage ) ;

		virtual void SetExecutor(Json::Value& jvRoot);
	private:
		Json::Value m_jvRoot;
	};
}
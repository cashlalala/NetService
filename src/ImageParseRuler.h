#pragma once
#include "IParser.h"
#include "IParseRuler.h"
#include <json/json.h>

namespace util
{
	class CImageListParseRuler : public IImageListParseRuler 
	{
	public:
		CImageListParseRuler();

		CImageListParseRuler(void* pExecutor);

		virtual void Traverse( CFBImageList& cFBImageList ) ;

		virtual void Traverse( CFkrImageList& cFkrImageList ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor) ;
	private:
		IParser* m_pParser;

		Json::Value m_jvRoot;
	};

	class CImageParseRuler : public IImageParseRuler 
	{
	public:
		CImageParseRuler();

		CImageParseRuler(void* pExecutor);

		virtual void Traverse( CFBImage& cFBImage ) ;

		virtual void Traverse( CFkrImage& cFkrImage ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor) ;
	private:
		IParser* m_pParser;

		Json::Value m_jvRoot;
	};
}
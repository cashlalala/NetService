#pragma once
#include "IParser.h"
#include "IParseRuler.h"
#include <json/json.h>

namespace util
{
	class CVideoFormatParseRuler : public IVideoFormatParseRuler 
	{
	public:
		CVideoFormatParseRuler();

		CVideoFormatParseRuler(void* pExecutor);

		virtual void Traverse( CFBVideoFormat& cFBVideoFormat ) ;

		virtual void Traverse( CFkrVideoFormat& cFkrVideoFormat ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor);
	private:
		IParser* m_pParser;
	};

	class CVideoListParseRuler : public IVideoListParseRuler 
	{
	public:
		CVideoListParseRuler();

		CVideoListParseRuler(void* pExecutor);

		virtual void Traverse( CFBVideoList& cFBVideoList ) ;

		virtual void Traverse( CFkrVideoList& cFkrVideoList ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor);
	private:
		IParser* m_pParser;
	};

	class CVideoParseRuler : public IVideoParseRuler 
	{
	public:
		CVideoParseRuler();

		CVideoParseRuler(void* pExecutor);

		virtual void Traverse( CFBVideo& cFBVideo ) ;

		virtual void Traverse( CFkrVideo& cFkrVideo ) ;

		virtual void SetExecutor(void* pExecutor) ;

		virtual void SetExecutor(IParser* pExecutor);
	private:
		IParser* m_pParser;
	};
}
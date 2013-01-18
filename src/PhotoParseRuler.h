#pragma once

#include "IParseRuler.h"
#include <json/json.h>
#include <string>
#include <list>

using std::string;
using std::list;

namespace util
{
	class CPhotoListParseRuler : public IPhotoListParseRuler 
	{
	public:
		CPhotoListParseRuler();

		CPhotoListParseRuler(Json::Value& jvRoot);

		virtual void Traverse( CFBPhotoList& cFBPhotoList ) ;

		virtual void Traverse( CFkrPhotoList& cFkrPhotoList ) ;

		virtual void SetExecutor(Json::Value& jvRoot) ;
	private:
		Json::Value m_jvRoot;
	};

	class CPhotoParseRuler : public IPhotoParseRuler 
	{
	public:
		CPhotoParseRuler();

		CPhotoParseRuler(Json::Value& jvRoot);

		virtual void Traverse( CFBPhoto& cFBPhoto ) ;

		virtual void Traverse( CFkrPhoto& cFkrPhoto ) ;

		virtual void SetExecutor(Json::Value& jvRoot) ;
	private:
		Json::Value m_jvRoot;
		static const list<string> S_LIST_FKRPHOTOSIZES;
	};
}
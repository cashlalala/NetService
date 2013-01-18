#pragma once

#include "IParseRuler.h"
#include <json/json.h>

namespace util
{
	class CPhotoListParseRuler : public IPhotoParseRuler 
	{
	public:
		CPhotoListParseRuler(Json::Value& jvRoot);

		virtual void Traverse( CFBPhoto& cFBPhoto ) ;

		virtual void Traverse( CFkrPhoto& cFkrPhoto ) ;
	private:
		Json::Value m_jvRoot;
	};
}
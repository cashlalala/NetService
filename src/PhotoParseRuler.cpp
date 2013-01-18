#include "stdafx.h"
#include "FkRPhotoModel.h"
#include "PhotoParseRuler.h"
#include "FlickrFields.h"


void util::CPhotoListParseRuler::Traverse( CFkrPhoto& cFkrPhoto )
{
}

void util::CPhotoListParseRuler::Traverse( CFBPhoto& cFBPhoto )
{

}

util::CPhotoListParseRuler::CPhotoListParseRuler( Json::Value& jvRoot )
{
	m_jvRoot = jvRoot;
}

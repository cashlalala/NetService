#pragma once
#include "IModel.h"
#include "IParseRuler.h"

#include <string>

using std::string;
using namespace util;

namespace model
{

	struct IError : public IModel , public util::IErrorParsable {
		virtual ~IError() = 0;
		int AcceptErrorParser(util::IErrorParseRuler& errParse) { return S_OK;};
		string szCode;
		string szMsg;
	};

	inline IError::~IError(){};
}


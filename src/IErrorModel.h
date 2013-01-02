#pragma once

#include <string>

using std::string;

namespace model
{
	struct IError {
		virtual ~IError() = 0;
		string szCode;
		string szMsg;
	};

	inline IError::~IError(){};
}


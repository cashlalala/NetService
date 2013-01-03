#pragma once
#include "IModel.h"

#include <string>

using std::string;

namespace model
{
	struct IError : public IModel {
		virtual ~IError() = 0;
		string szCode;
		string szMsg;
	};

	inline IError::~IError(){};
}


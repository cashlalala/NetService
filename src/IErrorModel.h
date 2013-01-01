#pragma once

namespace model
{
	struct IError {
		virtual ~IError(){};
		string szCode;
		string szMsg;
	};

	struct CFBError : public IError {
		virtual ~CFBError(){};
		string szType;
		string szErrSubCode;
	};
}


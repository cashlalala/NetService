#pragma once

#include <string>
#include <typeinfo>

using std::string;

#ifndef SAFE_DELETE_OBJECT
#define SAFE_DELETE_OBJECT(x) if(x) {delete x; x = NULL;}
#endif

#ifndef SAFE_DELETE_LIST
#define SAFE_DELETE_LIST(listType,listObject) \
{\
	for (listType::iterator it = listObject.begin(); it!=listObject.end();++it)\
	{\
	SAFE_DELETE_OBJECT(*it);\
	}\
	listObject.clear();\
}
#endif

namespace model
{
	struct IModel
	{
		virtual ~IModel() = 0;
		virtual string ToString()
		{
			return typeid(*this).name();
		};
	};

	inline IModel::~IModel(){};
}

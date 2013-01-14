#pragma once

#include <string>
#include <list>
#include <typeinfo>

using std::string;
using std::list;

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

	struct IPage : virtual public IModel
	{
		virtual ~IPage() = 0;
		string szNext;
		string szPrevious;
	};

	inline IPage::~IPage(){};

	template <class T>
	struct IList : virtual public IModel 
	{
		virtual ~IList() = 0;
		list<T> listOfItem;
	};

	template <class T>
	inline IList<T>::~IList()
	{
		SAFE_DELETE_LIST(list<T>,listOfItem);
	}

	template <class T>
	struct IPagedList : public IPage, public IList<T>
	{
		virtual ~IPagedList() = 0;
	};

	template <class T>
	inline IPagedList<T>::~IPagedList(){};
}

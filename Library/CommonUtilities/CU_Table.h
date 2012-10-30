#ifndef _TABLE_H_
#define _TABLE_H_
#include "CU_GrowingArray.h"
#include <bitset>

namespace CommonUtilities
{
	template <class Type,class CountType = int>
	class Table
	{
	public:
		inline Table();
		inline Table(const CountType aSize);

		inline void Init(const CountType aSize);
		inline CountType Add(const Type &aObject);

		inline void Remove(const Type &aObject);
		inline void RemoveAtIndex(const CountType aIndex);
		inline void RemoveAll();

	private:

		Type* myArray;
		bool* myFlags;
		CountType mySize;
	};
}

namespace CU = CommonUtilities;

template <class Type, class CountType> 
CommonUtilities::Table<Type,CountType>::Table()
{
	myArray = NULL;
	mySize	= 0;
}

template <class Type, class CountType> 
CommonUtilities::Table<Type,CountType>::Table(const CountType aSize)
{
	Init(aSize);
}

template <class Type, class CountType> 
void CommonUtilities::Table<Type,CountType>::Init(const CountType aSize)
{
	mySize	= aSize;
	myArray = new Type[aSize];
	myFlags = new bool[aSize];

	for (int index = 0; index < aSize; index++)
	{
		myFlags[index] = false;
	}
}

template <class Type, class CountType> 
CountType CommonUtilities::Table<Type,CountType>::Add(const Type &aObject)
{
	for (int index = 0; index < mySize; index++)
	{
		if (myFlags[index] == false)
		{
			myArray[index] = aObject;
			myFlags[index] = true;
			return index;
		}
	}
}

template <class Type, class CountType> 
void CommonUtilities::Table<Type,CountType>::Remove(const Type &aObject)
{
	for (int index = 0; index < mySize; index++)
	{
		if (myFlags[index] == true)
		{
			if (aObject == myArray[index])
			{
				RemoveAtIndex(index);
			}
		}
	}
}

template <class Type, class CountType> 
void CommonUtilities::Table<Type,CountType>::RemoveAtIndex(const CountType aIndex)
{
	myBools[aIndex] = false;
}

template <class Type, class CountType> 
void CommonUtilities::Table<Type,CountType>::RemoveAll()
{
	for (int index = 0; index < mySize; index++)
	{
		myFlags[index] = false;
	}
}

#endif
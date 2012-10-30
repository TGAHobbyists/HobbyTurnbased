#ifndef _STATIC_ARRAY_H_
#define _STATIC_ARRAY_H_
#include "CU_CommonMacros.h"
#include "dl_debug.h"

namespace CommonUtilities
{
	template <class Type,int Size>
	class StaticArray
	{
	public:
		inline StaticArray();
		inline StaticArray(const StaticArray& aStaticArray);
		inline ~StaticArray();

		inline StaticArray& operator=(const StaticArray& aStaticArray);
		inline Type& operator[](const int& aIndex);
		inline Type operator[](const int& aIndex) const;

		// Utility functions 

		inline void Insert(int aIndex,Type& aObject);
		inline void DeleteAll();
		inline int GetSize();
	private:
		Type myArray[Size];
		static const int ourLastIndex = Size - 1;
	};



}

namespace CU = CommonUtilities;

template <class Type,int Size>
CommonUtilities::StaticArray<Type,Size>::StaticArray()
{
	assert(Size > 0 && "Invalid size");
}

template <class Type,int Size>
CommonUtilities::StaticArray<Type,Size>::StaticArray(const StaticArray& aStaticArray)
{
	for (int typeIndex = 0; typeIndex < Size; typeIndex++)
	{
		myArray[typeIndex] = aStaticArray.myArray[typeIndex];
	}
}

template <class Type,int Size>
CommonUtilities::StaticArray<Type,Size>::~StaticArray()
{
	
}

template <class Type,int Size>
CommonUtilities::StaticArray<Type,Size>& CommonUtilities::StaticArray<Type,Size>::operator=(const StaticArray& aStaticArray)
{
	for (int typeIndex = 0; typeIndex < Size; typeIndex++)
	{
		myArray[typeIndex] = aStaticArray.myArray[typeIndex];
	}

	return(*this);
}

template <class Type,int Size>
Type& CommonUtilities::StaticArray<Type,Size>::operator[](const int& aIndex)
{
	assert(aIndex >= 0 && "Out of bounds");
	assert(aIndex < Size && "Out of bounds");
	return myArray[aIndex];
}

template <class Type,int Size>
Type CommonUtilities::StaticArray<Type, Size>::operator[]( const int& aIndex ) const
{
	assert(aIndex >= 0 && "Out of bounds");
	assert(aIndex < Size && "Out of bounds");
	return myArray[aIndex];
}

template <class Type,int Size>
void CommonUtilities::StaticArray<Type,Size>::Insert(int aIndex,Type& aObject)
{
	assert(aIndex >= 0 && "Out of bounds");
	assert(aIndex < Size && "Out of bounds");

	int currentIndex = ourLastIndex;
	while (currentIndex != aIndex)
	{
		myArray[currentIndex] = myArray[currentIndex-1];
		currentIndex--;
	}

	myArray[aIndex] = aObject;
}

template <class Type,int Size>
void CommonUtilities::StaticArray<Type,Size>::DeleteAll()
{
	for (int typeIndex = 0; typeIndex < Size; typeIndex++)
	{
		SAFE_DELETE(myArray[typeIndex]);
	}
}
template <class Type,int Size>
int CommonUtilities::StaticArray<Type, Size>::GetSize()
{
	return Size;
}
#endif
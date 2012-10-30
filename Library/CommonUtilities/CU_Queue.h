#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "CU_GrowingArray.h"

namespace CommonUtilities
{
	template <class Type, class CountType = int>
	class Queue
	{
	public:
		inline Queue();
		inline Queue(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline ~Queue();

		inline Queue(const Queue& aQueue);
		inline Queue& operator=(const Queue& aQueue);

		inline void Init(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline void ReInit(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline Type Pop();
		inline Type Front() const;
		__forceinline int Size() const;
		inline void Push(const Type &aValue);
		inline Type& operator[]( const int anIndex );
		inline Type PopAt( const int anIndex );

	private:
		CU::GrowingArray<Type,CountType> myArray;
	};
}

namespace CU = CommonUtilities;

template <class Type, class CountType>
CU::Queue<Type,CountType>::Queue()
{
}


template <class Type, class CountType>
CU::Queue<Type,CountType>::Queue(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag)
{
	Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template <class Type, class CountType>
CU::Queue<Type,CountType>::~Queue()
{

}

template <class Type, class CountType>
CU::Queue<Type,CountType>::Queue(const CU::Queue<Type,CountType>& aQueue)
{
	myArray = aQueue.myArray;
}

template <class Type, class CountType>
CU::Queue<Type,CountType>& CU::Queue<Type,CountType>::operator=(const CU::Queue<Type,CountType>& aQueue)
{
	myArray = aQueue.myArray;
	return *this;
}

template <class Type, class CountType>
void CU::Queue<Type,CountType>::Init(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag)
{
	myArray.Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template <class Type, class CountType>
void CU::Queue<Type,CountType>::ReInit(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true)
{
	myArray.ReInit(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template <class Type, class CountType>
Type CU::Queue<Type,CountType>::Pop()
{
	assert(myArray.Count() > 0 && "Empty");

	Type data = Front();
	for (int index = 0; index < myArray.Count()-1; index++)
	{
		myArray[index] = myArray[index+1];
	}
	myArray.RemoveCyclicAtIndex(myArray.Count()-1);
	return data;
}

template <class Type, class CountType>
Type CU::Queue<Type,CountType>::Front() const
{
	assert(myArray.Count() > 0 && "Empty");
	return myArray[0];
}

template <class Type, class CountType>
int CU::Queue<Type,CountType>::Size() const
{
	return myArray.Count();
}

template <class Type, class CountType>
void CU::Queue<Type,CountType>::Push(const Type &aValue)
{
	myArray.Add(aValue);
}

template <class Type, class CountType>
Type& CU::Queue<Type,CountType>::operator[]( const int anIndex )
{
	return myArray[anIndex];
}

template <class Type, class CountType>
Type CU::Queue<Type,CountType>::PopAt( const int anIndex )
{
	assert(myArray.Count() > anIndex && "Index higher than count!");

	Type data = myArray[anIndex];
	for (int index = anIndex; index < myArray.Count()-1; index++)
	{
		myArray[index] = myArray[index+1];
	}
	myArray.RemoveCyclicAtIndex(myArray.Count()-1);
	return data;
}


#endif
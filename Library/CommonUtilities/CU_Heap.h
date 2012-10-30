#ifndef _HEAP_H_
#define _HEAP_H_
#include <vector>
#include "CU_GrowingArray.h"
#include <cmath>

namespace CommonUtilities
{
	template <class Type,class CountType = int>
	class Heap
	{
	public:
		inline Heap();
		inline Heap(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline Heap(const std::vector<Type> &aVector);
		inline ~Heap();

		inline Heap(const Heap& aHeap);
		inline Heap& operator=(const Heap& aHeap);

		inline void Init(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline void Enqueue(const Type &someData);
		inline Type Dequeue();
		inline bool IsEmpty() const;

	private:
		inline void Swap(Type& aValue1, Type& aValue2);
		inline void MoveDown(CU::GrowingArray<Type>& anArray, int aFirstIndex, int aLastIndex);

	private:
		CU::GrowingArray<Type, CountType> myArray;
	};
}

namespace CU = CommonUtilities;

template<class Type, class CountType>
CU::Heap<Type,CountType>::Heap()
{
}

template<class Type, class CountType>
CU::Heap<Type,CountType>::Heap(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag)
{
	Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template<class Type, class CountType>
void CU::Heap<Type,CountType>::Init(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag)
{
	myArray.Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template<class Type, class CountType>
CU::Heap<Type,CountType>::Heap(const std::vector<Type> &aVector)
{
	myArray.Init(1000,1000);

	for (std::vector<Type>::size_type index = 0; index < aVector.size(); index++)
	{
		myArray.Add(aVector[index]);
	}

	for (int index = myArray.Count()-1; index >= 0; index--)
	{
		MoveDown(myArray,index,myArray.Count()-1);
	}
}

template<class Type, class CountType>
CU::Heap<Type,CountType>::~Heap()
{
	
}

template<class Type, class CountType>
CU::Heap<Type,CountType>::Heap(const CU::Heap<Type,CountType>& aHeap)
{
	myArray = aHeap.myArray;
}

template<class Type, class CountType>
CU::Heap<Type,CountType>& CU::Heap<Type,CountType>::operator=(const CU::Heap<Type,CountType>& aHeap)
{
	myArray = aHeap.myArray;
	return *this;
}

template<class Type, class CountType>
void CU::Heap<Type,CountType>::Swap(Type& aValue1, Type& aValue2)
{
	Type tmp = aValue1;
	aValue1 = aValue2;
	aValue2 = tmp;
}

template<class Type, class CountType>
void CU::Heap<Type,CountType>::Enqueue(const Type &someData)
{
	myArray.Add(someData);
	int index = myArray.Count() - 1;

	while((index > 0) && (myArray[(index-1)/2] < myArray[index]))
	{
		Swap(myArray[(index-1)/2],myArray[index]);
		index = (index-1)/2;
	}
}

template<class Type, class CountType>
Type CU::Heap<Type,CountType>::Dequeue()
{
	if (myArray.Count() == 0)
	{
		return Type();
	}

	const int lastIndexBeforeDelete = myArray.Count()-1;
	const Type returnValue = myArray[0];
	myArray[0] = myArray[lastIndexBeforeDelete];
	myArray.RemoveCyclicAtIndex(lastIndexBeforeDelete);

	MoveDown(myArray, 0, myArray.Count()-1);

	return returnValue;
}

template<class Type, class CountType>
bool CU::Heap<Type,CountType>::IsEmpty() const
{
	return (myArray.Count() == 0);
}

template<class Type, class CountType>
void CU::Heap<Type,CountType>::MoveDown(CU::GrowingArray<Type>& anArray, int aFirstIndex, int aLastIndex)
{
	int largestValue = 2*aFirstIndex+1;

	while(largestValue <= aLastIndex)
	{
		if (largestValue < aLastIndex && anArray[largestValue] < anArray[largestValue+1])
		{
			largestValue++;
		}
		if (anArray[aFirstIndex] < anArray[largestValue])
		{
			Swap(anArray[aFirstIndex],anArray[largestValue]);
			aFirstIndex = largestValue;
			largestValue = 2*aFirstIndex+1;
		}
		else
		{
			largestValue = aLastIndex+1;
		}
	}
}

#endif
#ifndef _STACK_H_
#define _STACK_H_
#include "CU_GrowingArray.h"

namespace CommonUtilities
{
	template <class Type, class CountType = int>
	class Stack
	{
	public:
		inline Stack();
		inline Stack(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline ~Stack();

		inline Stack(const Stack& aStack);
		inline Stack& operator=(const Stack& aStack);

		inline void Init(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline Type Pop();
		inline Type Top() const;
		__forceinline int Size() const;
		inline void Push(const Type &aValue);
	private:
		CU::GrowingArray<Type,CountType> myArray;
	};
}

namespace CU = CommonUtilities;

template <class Type, class CountType>
CU::Stack<Type,CountType>::Stack()
{
}

template <class Type, class CountType>
CU::Stack<Type,CountType>::Stack(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag)
{
	Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template <class Type, class CountType>
CU::Stack<Type,CountType>::~Stack()
{

}

template <class Type, class CountType>
CU::Stack<Type,CountType>::Stack(const CU::Stack<Type,CountType>& aStack)
{
	myArray = aStack.myArray;
}

template <class Type, class CountType>
CU::Stack<Type,CountType>& CU::Stack<Type,CountType>::operator=(const CU::Stack<Type,CountType>& aStack)
{
	myArray = aStack.myArray;
	return *this;
}

template <class Type, class CountType>
void CU::Stack<Type,CountType>::Init(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag)
{
	myArray.Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template <class Type, class CountType>
Type CU::Stack<Type,CountType>::Pop()
{
	assert(myArray.Count() > 0 && "Empty");

	Type data = Top();
	myArray.RemoveCyclicAtIndex(myArray.Count()-1);
	return data;
}

template <class Type, class CountType>
Type CU::Stack<Type,CountType>::Top() const
{
	const int lastIndex = myArray.Count()-1;
	//DL_ASSERT(lastIndex >= 0, "Empty");
	if( lastIndex < 0 )
	{
		return NULL;
	}
	return myArray[lastIndex];
}

template <class Type, class CountType>
int CU::Stack<Type,CountType>::Size() const
{
	return myArray.Count();
}

template <class Type, class CountType>
void CU::Stack<Type,CountType>::Push(const Type &aValue)
{
	myArray.Add(aValue);
}


#endif
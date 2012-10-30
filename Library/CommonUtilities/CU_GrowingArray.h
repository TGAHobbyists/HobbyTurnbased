#ifndef _GROWING_ARRAY_H_
#define _GROWING_ARRAY_H_
#include "CU_CommonMacros.h"
#include "DL_Debug.h"

namespace CommonUtilities
{
	template <class Type,class CountType = int>
	class GrowingArray
	{
	public:
		inline GrowingArray();
		inline GrowingArray(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline ~GrowingArray();

		inline GrowingArray(const GrowingArray& aGrowingArray);
		inline GrowingArray& operator=(const GrowingArray& aGrowingArray);

		inline void Init(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);
		inline void ReInit(const CountType aNrOfRecomendedItems, const CountType aItemIncreaseSize, const bool aUseSafeModeFlag = true);

		inline Type& operator[](const CountType& aIndex) const;

		inline void Add(const Type& aObject);
		inline void Insert(const CountType aIndex, const Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(const CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(const CountType aItemNumber);
		inline void RemoveKeepingOrder(const Type& aObject);
		inline void RemoveKeepingOrder(const CountType aItemNumber);
		inline void DeleteKeepingOrder(const Type& aObject);
		inline void DeleteKeepingOrder(const CountType aItemNumber);

		inline void RemoveAll();
		inline void DeleteAll();

		inline void Optimize();
		__forceinline CountType Count() const;

	private:
		inline void ReSize(CountType aNewSize);
		static const CountType ourItemIncreaseSizeAfterOptimzation = 1;
		CountType	myCounter;
		CountType	myAllocatedCounter;
		CountType	myItemIncreaseSize;
		Type		*myArrayPointer;
		bool		myUseSafeModeFlag;
		bool		myIsInitialized;
	};

	

	

};

namespace CU = CommonUtilities;

template <class Type, class CountType> 
CommonUtilities::GrowingArray<Type,CountType>::GrowingArray()
{
	myArrayPointer			= NULL;
	myItemIncreaseSize		= 0;
	myCounter				= 0;
	myAllocatedCounter		= 0;
	myUseSafeModeFlag		= true;
	myIsInitialized			= false;
}

template <class Type, class CountType> 
CommonUtilities::GrowingArray<Type,CountType>::GrowingArray(CountType aNrOfRecomendedItems, CountType aItemIncreaseSize, bool aUseSafeModeFlag=true)
{
	myArrayPointer			= NULL;
	myItemIncreaseSize		= 0;
	myCounter				= 0;
	myAllocatedCounter		= 0;
	myUseSafeModeFlag		= true;
	myIsInitialized			= false;

	Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
}

template <class Type, class CountType> 
CommonUtilities::GrowingArray<Type,CountType>::GrowingArray(const GrowingArray& aGrowingArray)
{
	////DL_WARNING(false, "Avoid unnecessary allocating");
	myIsInitialized = false;
	Init(aGrowingArray.myAllocatedCounter, aGrowingArray.myItemIncreaseSize, aGrowingArray.myUseSafeModeFlag);	

	if (myUseSafeModeFlag == true)
	{
		for (CountType entityIndex = 0; entityIndex < aGrowingArray.Count(); entityIndex++)
		{
			Add(aGrowingArray[entityIndex]);
		}
	}
	else
	{
		myCounter = aGrowingArray.myCounter;
		memcpy(myArrayPointer, aGrowingArray.myArrayPointer, sizeof(Type)*myCounter);
	}
}

template <class Type, class CountType> 
CommonUtilities::GrowingArray<Type,CountType>& CommonUtilities::GrowingArray<Type,CountType>::operator=(const GrowingArray& aGrowingArray)
{
	if (myAllocatedCounter < aGrowingArray.myCounter)
	{
		SAFE_DELETE_ARRAY(myArrayPointer);
		myArrayPointer		= new Type[aGrowingArray.myAllocatedCounter];	
		myItemIncreaseSize	= aGrowingArray.myItemIncreaseSize;
		myAllocatedCounter	= aGrowingArray.myAllocatedCounter;
		myUseSafeModeFlag	= aGrowingArray.myUseSafeModeFlag;
		myIsInitialized		= aGrowingArray.myIsInitialized;
		myCounter			= aGrowingArray.myCounter;
		//DL_DEBUG("Avoid unnecessary allocations!");
	}
	else
	{
		RemoveAll();
		myCounter = aGrowingArray.myCounter;
	}

	if (myUseSafeModeFlag == true)
	{
		for (CountType entityIndex = 0; entityIndex < myCounter; entityIndex++)
		{
			myArrayPointer[entityIndex] = aGrowingArray.myArrayPointer[entityIndex];
		}
	}
	else
	{
		memcpy(myArrayPointer, aGrowingArray.myArrayPointer, sizeof(Type)*myCounter);
	}

	return(*this);
}

template <class Type, class CountType> 
CommonUtilities::GrowingArray<Type,CountType>::~GrowingArray()
{
	RemoveAll();

	SAFE_DELETE_ARRAY(myArrayPointer);

	myItemIncreaseSize		= 0;
	myCounter				= 0;
	myAllocatedCounter		= 0;
	myIsInitialized			= false;
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::Init(CountType aNrOfRecomendedItems, CountType aItemIncreaseSize, bool aUseSafeModeFlag = true)
{
	assert(aNrOfRecomendedItems >= 0 && "Invalid start allocation value");
	// ITEM INCREASE SIZE 0 IS SUBSTITUTE FOR FIXEDARRAY
	assert(aItemIncreaseSize >= 0 && "Invalid inrcrease allocation value");
	assert(myIsInitialized == false && "Already initialized");

	myCounter			= 0;
	myAllocatedCounter	= aNrOfRecomendedItems;
	myArrayPointer		= new Type[myAllocatedCounter];
	myItemIncreaseSize	= aItemIncreaseSize;
	myUseSafeModeFlag	= aUseSafeModeFlag;
	myIsInitialized		= true;
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::ReInit(CountType aNrOfRecomendedItems, CountType aItemIncreaseSize, bool aUseSafeModeFlag = true)
{
	//assert(myIsInitialized == true && "Not initialized");

	if (myIsInitialized == true)
	{
		RemoveAll();
		myIsInitialized = false;
		SAFE_DELETE_ARRAY(myArrayPointer);
		Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
	}
	else
	{
		Init(aNrOfRecomendedItems, aItemIncreaseSize, aUseSafeModeFlag);
	}
}

template <class Type, class CountType> 
Type& CommonUtilities::GrowingArray<Type,CountType>::operator[](const CountType& aIndex) const
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aIndex < myCounter && "Out of bounds");
	assert(aIndex >= 0 && "Out of bounds");
	return myArrayPointer[aIndex];
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::Add(const Type& aObject)
{
	assert(myIsInitialized == true && "Not initialized");

	if (myCounter >= myAllocatedCounter)
	{
		ReSize(myAllocatedCounter + myItemIncreaseSize);
	}

	myArrayPointer[myCounter] = aObject;
	myCounter++;
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::Insert(const CountType aIndex, const Type& aObject)
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aIndex < myCounter && "Out of bounds");
	assert(aIndex >= 0 && "Out of bounds");

	if (myCounter == myAllocatedCounter)
	{
		ReSize(myAllocatedCounter + myItemIncreaseSize);
	}

	CountType currentIndex = myCounter;
	while (currentIndex != aIndex)
	{
		myArrayPointer[currentIndex] = myArrayPointer[currentIndex-1];
		currentIndex--;
	}

	myArrayPointer[aIndex] = aObject;
	myCounter++;
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::DeleteCyclic(Type& aObject)
{
	assert(myIsInitialized == true && "Not initialized");

	for (CountType entityIndex = 0; entityIndex < myCounter; entityIndex++)
	{
		if (myArrayPointer[entityIndex] == aObject)
		{
			DeleteCyclicAtIndex(entityIndex);
			break;
		}
	}
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::DeleteCyclicAtIndex(CountType aIndex)
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aIndex < myCounter && "Out of bounds");
	assert(aIndex >= 0 && "Out of bounds");

	SAFE_DELETE(myArrayPointer[aIndex]);
	myArrayPointer[aIndex] = myArrayPointer[myCounter-1];
	myCounter--;
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::RemoveCyclic(const Type& aObject)
{
	assert(myIsInitialized == true && "Not initialized");

	for (CountType entityIndex = 0; entityIndex < myCounter; entityIndex++)
	{
		if (myArrayPointer[entityIndex] == aObject)
		{
			RemoveCyclicAtIndex(entityIndex);
			break;
		}
	}
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::RemoveCyclicAtIndex(CountType aIndex)
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aIndex < myCounter && "Out of bounds");
	assert(aIndex >= 0 && "Out of bounds");

	myArrayPointer[aIndex] = myArrayPointer[myCounter-1];
	myCounter--;
}

template <class Type,class CountType>
void CommonUtilities::GrowingArray<Type, CountType>::RemoveKeepingOrder( const CountType aItemNumber )
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aItemNumber < myCounter && "Out of bounds");
	assert(aItemNumber >= 0 && "Out of bounds");

	for (int index = aItemNumber; index < myCounter; index++)
	{
		Type tempType = myArrayPointer[index + 1];
		myArrayPointer[index] = tempType;
	}
	myCounter--;
}

template <class Type,class CountType>
void CommonUtilities::GrowingArray<Type, CountType>::RemoveKeepingOrder( const Type& aObject )
{
	assert(myIsInitialized == true && "Not initialized");

	for (CountType entityIndex = 0; entityIndex < myCounter; entityIndex++)
	{
		if (myArrayPointer[entityIndex] == aObject)
		{
			RemoveKeepingOrder(entityIndex);
			break;
		}
	}
}

template <class Type,class CountType>
void CommonUtilities::GrowingArray<Type, CountType>::DeleteKeepingOrder( const CountType aItemNumber )
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aItemNumber < myCounter && "Out of bounds");
	assert(aItemNumber >= 0 && "Out of bounds");

	SAFE_DELETE(myArrayPointer[aItemNumber]);
	for (int index = aItemNumber; index < myCounter; index++)
	{
		Type tempType = myArrayPointer[index + 1];
		myArrayPointer[index] = tempType;
	}
	myCounter--;
}

template <class Type,class CountType>
void CommonUtilities::GrowingArray<Type, CountType>::DeleteKeepingOrder( const Type& aObject )
{
	assert(myIsInitialized == true && "Not initialized");

	for (CountType entityIndex = 0; entityIndex < myCounter; entityIndex++)
	{
		if (myArrayPointer[entityIndex] == aObject)
		{
			DeleteKeepingOrder(entityIndex);
			break;
		}
	}
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::RemoveAll()
{
	myCounter = 0;
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::DeleteAll()
{
	assert(myIsInitialized == true && "Not initialized");

	for (CountType typeIndex = 0; typeIndex < myCounter; typeIndex++)
	{
		SAFE_DELETE(myArrayPointer[typeIndex]);
	}
	RemoveAll();
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::Optimize()
{
	assert(myIsInitialized == true && "Not initialized");
	ReSize(myCounter);
	myItemIncreaseSize	= ourItemIncreaseSizeAfterOptimzation;
}

template <class Type, class CountType> 
CountType CommonUtilities::GrowingArray<Type,CountType>::Count() const
{
	//assert(myIsInitialized == true && "Not initialized");
	return(myCounter);
}

template <class Type, class CountType> 
void CommonUtilities::GrowingArray<Type,CountType>::ReSize(CountType aNewSize)
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aNewSize > 0 && "Invalid size");
	//DL_DEBUG("Avoid unnecessary allocations!");

	Type* newArray = new Type[aNewSize];

	if (myUseSafeModeFlag == true)
	{		
		for (CountType entityIndex = 0; entityIndex < myCounter; entityIndex++)
		{
			newArray[entityIndex] = myArrayPointer[entityIndex];
		}
	}
	else
	{
		memcpy(newArray, myArrayPointer, sizeof(Type)*myCounter);
	}

	SAFE_DELETE_ARRAY(myArrayPointer);
	myArrayPointer		= newArray;
	myAllocatedCounter	= aNewSize;
}

#endif
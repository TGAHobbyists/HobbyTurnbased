#ifndef _FIXED_ARRAY_H_
#define _FIXED_ARRAY_H_
#include "CU_CommonMacros.h"
#include "DL_Debug.h"

namespace CommonUtilities
{
	template <class Type,class CountType = unsigned int>
	class FixedArray
	{
	public:
		inline FixedArray();
		inline FixedArray(const CountType aAllocatedCounter, const bool aUseSafeModeFlag = true);
		inline ~FixedArray();

		inline FixedArray(const FixedArray& aFixedArray);
		inline FixedArray& operator=(const FixedArray& aFixedArray);

		inline void Init(const CountType aAllocatedCounter, const bool aUseSafeModeFlag = true);
		inline void ReInit(const CountType aAllocatedCounter, const bool aUseSafeModeFlag = true);

		inline Type& operator[](const CountType& aIndex) const;

		inline void Add(const Type& aObject);
		inline void Insert(const int& anArrayPosition, const Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(const CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(const CountType aItemNumber);

		inline void RemoveAll();
		inline void DeleteAll();

		__forceinline CountType Count() const;

	private:
		CountType	myCounter;
		CountType	myAllocatedCounter;
		Type		*myArrayPointer;
		bool		myUseSafeModeFlag;
		bool		myIsInitialized;
	};
};

template <class Type, class CountType> 
CommonUtilities::FixedArray<Type,CountType>::FixedArray()
{
	myArrayPointer			= NULL;
	myCounter				= 0;
	myAllocatedCounter		= 0;
	myUseSafeModeFlag		= true;
	myIsInitialized			= false;
}

template <class Type, class CountType> 
CommonUtilities::FixedArray<Type,CountType>::FixedArray(CountType aAllocatedCounter, bool aUseSafeModeFlag=true)
{
	myArrayPointer			= NULL;
	myCounter				= 0;
	myAllocatedCounter		= 0;
	myUseSafeModeFlag		= true;
	myIsInitialized			= false;

	Init(aAllocatedCounter, aUseSafeModeFlag);
}

template <class Type, class CountType> 
CommonUtilities::FixedArray<Type,CountType>::FixedArray(const FixedArray& aFixedArray)
{
	//DL_WARNING(false, "Avoid unnecessary allocating");
	myIsInitialized = false;
	Init(aFixedArray.myCounter, aFixedArray.myUseSafeModeFlag);	

	if (myUseSafeModeFlag == true)
	{
		for (CountType entityIndex = 0; entityIndex < aFixedArray.Count(); entityIndex++)
		{
			Add(aFixedArray[entityIndex]);
		}
	}
	else
	{
		myCounter = aFixedArray.myCounter;
		memcpy(myArrayPointer, aFixedArray.myArrayPointer, sizeof(Type)*myCounter);
	}
}

template <class Type, class CountType> 
CommonUtilities::FixedArray<Type,CountType>& CommonUtilities::FixedArray<Type,CountType>::operator=(const FixedArray& aFixedArray)
{
	if (myUseSafeModeFlag == true)
	{
		for (CountType entityIndex = 0; entityIndex < myCounter; entityIndex++)
		{
			myArrayPointer[entityIndex] = aFixedArray.myArrayPointer[entityIndex];
		}
	}
	else
	{
		memcpy(myArrayPointer, aFixedArray.myArrayPointer, sizeof(Type)*myCounter);
	}

	return(*this);
}

template <class Type, class CountType> 
CommonUtilities::FixedArray<Type,CountType>::~FixedArray()
{
	RemoveAll();

	SAFE_DELETE_ARRAY(myArrayPointer);

	myCounter				= 0;
	myAllocatedCounter		= 0;
	myIsInitialized			= false;
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::Init(CountType aAllocatedCounter, bool aUseSafeModeFlag = true)
{
	assert(aAllocatedCounter >= 0 && "Do not create a FixedArray with size 0 or less");
	assert(myIsInitialized == false &&  "Already initialized");

	myCounter			= 0;
	myAllocatedCounter	= aAllocatedCounter;
	myArrayPointer		= new Type[myAllocatedCounter];
	myUseSafeModeFlag	= aUseSafeModeFlag;
	myIsInitialized		= true;
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::ReInit(CountType aAllocatedCounter, bool aUseSafeModeFlag = true)
{
	assert(myIsInitialized == true && "Not initialized");

	if (myIsInitialized == true)
	{
		RemoveAll();
		myIsInitialized = false;
		Init(aAllocatedCounter, aUseSafeModeFlag);
	}
}

template <class Type, class CountType> 
Type& CommonUtilities::FixedArray<Type,CountType>::operator[](const CountType& aIndex) const
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aIndex < myCounter && "Out of bounds");
	assert(aIndex >= 0 && "Out of bounds");
	return myArrayPointer[aIndex];
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::Add(const Type& aObject)
{
	assert(myIsInitialized == true && "Not initialized");

	if (myCounter == myAllocatedCounter)
	{
		assert( myCounter >= myAllocatedCounter && "Too much items" );
	}
	else
	{
		myArrayPointer[myCounter] = aObject;
		myCounter++;
	}
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::Insert(const int& anArrayPosition, const Type& aObject)
{
	assert(myIsInitialized == true && "Not initialized");

	if (myCounter == myAllocatedCounter)
	{
		assert( myCounter >= myAllocatedCounter && "Too much items" );
	}
	
	if(anArrayPosition >= 0 &&  anArrayPosition < myAllocatedCounter)
	{
		myArrayPointer[anArrayPosition] = aObject;
	}
	else
	{
		assert( 0 && "TRYING TO USE INDEX OUTSIDE OF ARRAY" );
	}
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::DeleteCyclic(Type& aObject)
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
void CommonUtilities::FixedArray<Type,CountType>::DeleteCyclicAtIndex(CountType aIndex)
{
	assert(myIsInitialized == true &&  "Not initialized");
	assert(aIndex < myCounter && "Out of bounds");
	assert(aIndex >= 0 && "Out of bounds");

	SAFE_DELETE(myArrayPointer[aIndex]);
	myArrayPointer[aIndex] = myArrayPointer[myCounter-1];
	myCounter--;
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::RemoveCyclic(const Type& aObject)
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
void CommonUtilities::FixedArray<Type,CountType>::RemoveCyclicAtIndex(CountType aIndex)
{
	assert(myIsInitialized == true && "Not initialized");
	assert(aIndex < myCounter && "Out of bounds");
	assert(aIndex >= 0 && "Out of bounds");

	myArrayPointer[aIndex] = myArrayPointer[myCounter-1];
	myCounter--;
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::RemoveAll()
{
	myCounter = 0;
}

template <class Type, class CountType> 
void CommonUtilities::FixedArray<Type,CountType>::DeleteAll()
{
	assert(myIsInitialized == true && "Not initialized");

	for (CountType typeIndex = 0; typeIndex < myCounter; typeIndex++)
	{
		SAFE_DELETE(myArrayPointer[typeIndex]);
	}
	RemoveAll();
}

template <class Type, class CountType> 
CountType CommonUtilities::FixedArray<Type,CountType>::Count() const
{
	assert(myIsInitialized == true && "Not initialized");
	return(myCounter);
}
#endif//_FIXED_ARRAY_H_
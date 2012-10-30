#ifndef _STRING_HASH_TABLE_H_
#define _STRING_HASH_TABLE_H_
#include <string>
#include "CU_StaticArray.h"
#include "CU_DoubleLinkedList.h"
#include "StringToInt.h"

namespace CommonUtilities
{
	template<class Type>
	struct HashTablePair
	{
		Type myData;
#ifdef STORE_STRING
		std::string myString;
#endif
		unsigned int myKey;
	};

	template<class Type>
	class HashTable
	{
	public:
		inline HashTable();
		inline ~HashTable();

		inline HashTable(const HashTable& aHashTable);
		inline HashTable& operator=(const HashTable& aHashTable);

		inline unsigned int Add(const std::string& aString, const Type& someData);
		inline void Remove(const unsigned int aKey);
		inline void RemoveAll();

		inline Type operator[](const unsigned int aKey);

		inline Type Get(const unsigned int aKey);

#ifdef STORE_STRING
		inline std::string GetString(const unsigned int aKey);
#endif

	private:
		inline HashTablePair<Type> GetHashTablePair(const unsigned int aKey);

	private:
		static const int ourTableSize = 1000;
		CU::StaticArray<DoubleLinkedList<HashTablePair<Type>>,ourTableSize> myArray;
	};

	template<class Type>
	HashTable<Type>::HashTable()
	{

	}

	template<class Type>
	HashTable<Type>::~HashTable()
	{

	}

	template<class Type>
	HashTable<Type>::HashTable(const HashTable& aHashTable)
	{
		myArray	= aHashTable.myArray;
	}

	template<class Type>
	HashTable<Type>& HashTable<Type>::operator=(const HashTable& aHashTable)
	{
		myArray	= aHashTable.myArray;
		return *this;
	}

	template<class Type>
	unsigned int HashTable<Type>::Add(const std::string& aString, const Type& someData)
	{
		unsigned int key = S2I(aString.c_str());
		unsigned int index = key % ourTableSize;

		if (myArray[index].GetFirstNode() != NULL)
		{
			DoubleLinkedListNode<HashTablePair<Type>>* currentNode = myArray[index].GetFirstNode();
			bool dataAlreadyExists = false;
			bool keyAlreadyExists = false;

			while(currentNode != NULL)
			{
				if (currentNode->GetValue().myKey == key)
				{
					if (currentNode->GetValue().myData == someData)
					{
						dataAlreadyExists = true;
					}
					keyAlreadyExists = true;
				}

				currentNode = currentNode->GetNextNode();
			}


			if (dataAlreadyExists == true)
			{
				assert(false && "Data already exists. No need to store duplicates.");
				return key;
			}
			else
				if (keyAlreadyExists == true)
				{
					assert(false && "Key already exists but the data is not the same. Fix it!");
					return key;
				}
		}

		HashTablePair<Type> pair;
		pair.myData		= someData;
		pair.myKey		= key;

#ifdef STORE_STRING
		pair.myString	= aString;
#endif

		myArray[index].InsertNode(pair);

		return key;
	}

	template<class Type>
	void HashTable<Type>::RemoveAll()
	{
		for (int index = 0; index < ourTableSize; index++)
		{
			while(myArray[index].GetFirstNode() != NULL)
			{
				myArray[index].DeleteNode(myArray[index].GetFirstNode());
			}
		}
	}

	template<class Type>
	void HashTable<Type>::Remove(const unsigned int aKey)
	{
		unsigned int index = aKey % ourTableSize;

		DoubleLinkedListNode<HashTablePair<Type>>* currentNode = myArray[index].GetFirstNode();

		while(currentNode != NULL)
		{
			if (currentNode->GetValue().myKey == aKey)
			{
				myArray[index].DeleteNode(currentNode);
				return;
			}

			currentNode = currentNode->GetNextNode();
		}
	}

	template<class Type>
	HashTablePair<Type> HashTable<Type>::GetHashTablePair(const unsigned int aKey)
	{
		unsigned int index = aKey % ourTableSize;

		DoubleLinkedListNode<HashTablePair<Type>>* currentNode = myArray[index].GetFirstNode();

		while(currentNode != NULL)
		{
			if (currentNode->GetValue().myKey == aKey)
			{
				return currentNode->GetValue();
			}

			currentNode = currentNode->GetNextNode();
		}

		//DL_ASSERT(false, "Object with key not found");
		return HashTablePair<Type>();
	}

#ifdef STORE_STRING
	template<class Type>
	std::string HashTable<Type>::GetString(const unsigned int aKey)
	{
		return GetHashTablePair(aKey).myString;
	}
#endif

	template<class Type>
	Type HashTable<Type>::Get(const unsigned int aKey)
	{
		return GetHashTablePair(aKey).myData;
	}

	template<class Type>
	Type HashTable<Type>::operator[](const unsigned int aKey)
	{
		return GetHashTablePair(aKey).myData;
	}
}

namespace CU = CommonUtilities;

#endif
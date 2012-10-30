#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <vector>

template <class Type>
class DoubleLinkedList;

template <class Type>
class DoubleLinkedListNode
{
public:
	inline DoubleLinkedListNode();
	inline DoubleLinkedListNode(const Type &aValue);

	inline void InsertBefore(DoubleLinkedListNode<Type>* aNode);
	inline void InsertAfter(DoubleLinkedListNode<Type>* aNode);
	inline void Delete();

	inline DoubleLinkedListNode<Type>* GetPreviousNode() const;
	inline DoubleLinkedListNode<Type>* GetNextNode() const;
	inline Type GetValue() const;

	inline void AddList(DoubleLinkedList<Type>* aList = NULL);
private:
	inline DoubleLinkedList<Type>* GetList() const;
public:
	DoubleLinkedList<Type>* myList;
	DoubleLinkedListNode<Type> *myPreviousNode;
	DoubleLinkedListNode<Type> *myNextNode;
	Type myValue;
};

template <class Type>
DoubleLinkedListNode<Type>::DoubleLinkedListNode()
{
	myPreviousNode	= NULL;
	myNextNode		= NULL;
	myList			= NULL;
}

template <class Type>
DoubleLinkedListNode<Type>::DoubleLinkedListNode(const Type &aValue)
{
	myPreviousNode	= NULL;
	myNextNode		= NULL;
	myList			= NULL;
	myValue			= aValue;
}

template <class Type>
void DoubleLinkedListNode<Type>::InsertBefore(DoubleLinkedListNode<Type>* aNode)
{
	if (myList != NULL)
	{
		if (aNode->GetList() == NULL)
		{
			aNode->AddList(myList);
			myList->NotifyNodeAddedBefore(aNode, this);
		}
	}

	aNode->myPreviousNode = myPreviousNode;
	aNode->myNextNode = this;

	if (myPreviousNode != NULL)
	{
		myPreviousNode->myNextNode = aNode;
	}
	
	myPreviousNode = aNode;
}

template <class Type>
void DoubleLinkedListNode<Type>::InsertAfter(DoubleLinkedListNode<Type>* aNode)
{
	if (myList != NULL)
	{
		if (aNode->GetList() == NULL)
		{
			aNode->AddList(myList);
			myList->NotifyNodeAddedAfter(aNode, this);
		}
	}

	aNode->myPreviousNode = this;
	aNode->myNextNode = myNextNode;

	if (myNextNode != NULL)
	{
		myNextNode->myPreviousNode = aNode;
	}

	myNextNode = aNode;
}

template <class Type>
void DoubleLinkedListNode<Type>::Delete()
{
	if (myList != NULL)
	{
		myList->NotifyNodeRemoved(this);
	}

	if (myPreviousNode != NULL)
	{
		myPreviousNode->myNextNode = myNextNode;
	}

	if (myNextNode != NULL)
	{
		myNextNode->myPreviousNode = myPreviousNode;
	}

	delete this;
}

template <class Type>
DoubleLinkedListNode<Type>* DoubleLinkedListNode<Type>::GetPreviousNode() const
{
	return myPreviousNode;
}

template <class Type>
DoubleLinkedListNode<Type>* DoubleLinkedListNode<Type>::GetNextNode() const
{
	return myNextNode;
}

template <class Type>
Type DoubleLinkedListNode<Type>::GetValue() const
{
	return myValue;
}

template <class Type>
void DoubleLinkedListNode<Type>::AddList(DoubleLinkedList<Type>* aList)
{
	assert(aList != NULL && "aList == NULL");
	assert(myList == NULL && "myList != NULL");
	myList = aList;
}

template <class Type>
DoubleLinkedList<Type>* DoubleLinkedListNode<Type>::GetList() const
{
	return myList;
}

template <class Type>
class DoubleLinkedList
{
public:
	DoubleLinkedList();
	DoubleLinkedListNode<Type>* GetFirstNode();
	DoubleLinkedListNode<Type>* GetLastNode();
	void InsertNodeBeforeNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert);
	void InsertNodeAfterNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert);
	void InsertNodeSorted(DoubleLinkedListNode<Type>* aNodeToInsert);
	void InsertNodeSorted(const Type &aValueToInsert);
	void InsertNode(DoubleLinkedListNode<Type>* aNodeToInsert);
	void InsertNode(const Type &aValueToInsert);
	void DeleteNode(const Type &aValue);
	void DeleteNode(DoubleLinkedListNode<Type>* aNode);
	DoubleLinkedListNode<Type>* Find(const Type &aValue);
	void NotifyNodeRemoved(DoubleLinkedListNode<Type>* aNode);
	void NotifyNodeAddedAfter(DoubleLinkedListNode<Type>* aAddedNode, DoubleLinkedListNode<Type>* aTargetNode);
	void NotifyNodeAddedBefore(DoubleLinkedListNode<Type>* aAddedNode, DoubleLinkedListNode<Type>* aTargetNode);
private:
	DoubleLinkedListNode<Type>* myHead;
	DoubleLinkedListNode<Type>* myTail;
};

template <class Type>
DoubleLinkedList<Type>::DoubleLinkedList()
{
	myHead = NULL;
	myTail = NULL;
}

template <class Type>
DoubleLinkedListNode<Type>* DoubleLinkedList<Type>::GetFirstNode()
{
	return myHead;
}

template <class Type>
DoubleLinkedListNode<Type>* DoubleLinkedList<Type>::GetLastNode()
{
	return myTail;
}

template <class Type>
void DoubleLinkedList<Type>::InsertNodeBeforeNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert)
{
	aNodeToInsert->AddList(this);
	aNode->InsertBefore(aNodeToInsert);

	if (aNode == myHead)
	{
		myHead = aNodeToInsert;
	}
}

template <class Type>
void DoubleLinkedList<Type>::InsertNodeAfterNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert)
{
	aNodeToInsert->AddList(this);
	aNode->InsertAfter(aNodeToInsert);

	if (aNode == myTail)
	{
		myTail = aNodeToInsert;
	}
}

template <class Type>
void DoubleLinkedList<Type>::InsertNodeSorted(DoubleLinkedListNode<Type>* aNodeToInsert)
{
	assert(aNodeToInsert != NULL && "Node to insert == NULL");

	if (myHead == NULL)
	{
		myHead = aNodeToInsert;
		myTail = aNodeToInsert;
		aNodeToInsert->AddList(this);
		return;
	}
	else
	{
		DoubleLinkedListNode<Type>* node = myHead;

		for (;;)
		{
			if (node->GetValue() > aNodeToInsert->GetValue())
			{
				InsertNodeBeforeNode(node, aNodeToInsert);

				if (node == myHead)
				{
					myHead = aNodeToInsert;
				}

				return;
			}

			if (node == myTail)
			{
				InsertNodeAfterNode(node, aNodeToInsert);
				myTail = aNodeToInsert;
				return;
			}

			node = node->GetNextNode();
		}
	}
}

template <class Type>
void DoubleLinkedList<Type>::InsertNodeSorted(const Type &aValueToInsert)
{
	InsertNodeSorted(new DoubleLinkedListNode<Type>(aValueToInsert));
}

template <class Type>
void DoubleLinkedList<Type>::InsertNode(DoubleLinkedListNode<Type>* aNodeToInsert)
{
	assert(aNodeToInsert != NULL && "aNodeToInsert == NULL");

	if (myHead == NULL)
	{
		myHead = aNodeToInsert;
		myTail = aNodeToInsert;
		aNodeToInsert->AddList(this);
		return;
	}
	else
	{
		InsertNodeAfterNode(myTail, aNodeToInsert);
	}
}

template <class Type>
void DoubleLinkedList<Type>::InsertNode(const Type &aValueToInsert)
{
	InsertNode(new DoubleLinkedListNode<Type>(aValueToInsert));
}

template <class Type>
void DoubleLinkedList<Type>::DeleteNode(DoubleLinkedListNode<Type>* aNode)
{
	aNode->Delete();
}

template <class Type>
void DoubleLinkedList<Type>::DeleteNode(const Type &aValue)
{
	DoubleLinkedListNode<Type>* found = Find(aValue);
	
	while (found != NULL)
	{
		DeleteNode(found);
		found = Find(aValue);
	}
}

template <class Type>
DoubleLinkedListNode<Type>* DoubleLinkedList<Type>::Find(const Type &aValue)
{
	DoubleLinkedListNode<Type>* node = myHead;

	while(node != NULL)
	{
		if (node->GetValue() == aValue)
		{
			return node;
		}
		node = node->GetNextNode();
	}

	return NULL;
}

template <class Type>
void DoubleLinkedList<Type>::NotifyNodeRemoved(DoubleLinkedListNode<Type>* aNode)
{
	if (aNode == myHead)
	{
		myHead = aNode->GetNextNode();
	}

	if (aNode == myTail)
	{
		myTail = aNode->GetPreviousNode();
	}
}

template <class Type>
void DoubleLinkedList<Type>::NotifyNodeAddedBefore(DoubleLinkedListNode<Type>* aAddedNode, DoubleLinkedListNode<Type>* aTargetNode)
{
	if (aTargetNode == myHead)
	{
		myHead = aAddedNode;
	}
}

template <class Type>
void DoubleLinkedList<Type>::NotifyNodeAddedAfter(DoubleLinkedListNode<Type>* aAddedNode, DoubleLinkedListNode<Type>* aTargetNode)
{
	if (aTargetNode == myTail)
	{
		myTail = aAddedNode;
	}
}

#endif
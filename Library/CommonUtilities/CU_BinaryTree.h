#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include "CU_Stack.h"
#include "DL_Debug.h"

template<class Type>
class BinaryTree;

namespace CommonUtilities
{
	template<class Type>
	class BinaryTreeNode
	{
	public:
		inline BinaryTreeNode();
		inline BinaryTreeNode(const Type &aValue);
		inline ~BinaryTreeNode();

		inline void SetValue(const Type &aValue);
		inline Type GetValue() const;

		inline CU::BinaryTreeNode<Type>* GetRight() const;
		inline CU::BinaryTreeNode<Type>* GetLeft() const;

		inline void SetRight(CU::BinaryTreeNode<Type>* aNode);
		inline void SetLeft(CU::BinaryTreeNode<Type>* aNode);

		inline void Print() const;

		inline bool HasChildren() const;

		inline bool IsConnected() const;
		inline void Connect(BinaryTree<Type>* aTree);
		inline void Disconnect();
	private:
		inline BinaryTreeNode(const CU::BinaryTreeNode<Type>& aNode);
	public:
		Type myValue;
		BinaryTree<Type>* myTree;
		CU::BinaryTreeNode<Type>* myLeft;
		CU::BinaryTreeNode<Type>* myRight;
	};
}

namespace CU = CommonUtilities;

template<class Type>
CU::BinaryTreeNode<Type>::BinaryTreeNode()
{
	myLeft	= NULL;
	myRight	= NULL;
	myTree	= NULL;
}

template<class Type>
CU::BinaryTreeNode<Type>::BinaryTreeNode(const Type &aValue)
{
	myLeft	= NULL;
	myRight	= NULL;
	myTree	= NULL;
	SetValue(aValue);
}

template<class Type>
CU::BinaryTreeNode<Type>::~BinaryTreeNode()
{
	if (myTree != NULL)
	{
		myTree->DeleteNode(this);
	}
}

template<class Type>
void CU::BinaryTreeNode<Type>::SetValue(const Type &aValue)
{
	myValue = aValue;
}

template<class Type>
Type CU::BinaryTreeNode<Type>::GetValue() const
{
	return myValue;
}

template<class Type>
CU::BinaryTreeNode<Type>* CU::BinaryTreeNode<Type>::GetLeft() const
{
	return myLeft;
}

template<class Type>
CU::BinaryTreeNode<Type>* CU::BinaryTreeNode<Type>::GetRight() const
{
	return myRight;
}

template<class Type>
void CU::BinaryTreeNode<Type>::SetLeft(CU::BinaryTreeNode<Type>* aNode)
{
	myLeft = aNode;
}

template<class Type>
void CU::BinaryTreeNode<Type>::SetRight(CU::BinaryTreeNode<Type>* aNode)
{
	myRight = aNode;
}

template<class Type>
void CU::BinaryTreeNode<Type>::Print() const
{
	std::cout<<myValue<<std::endl;
}

template<class Type>
bool CU::BinaryTreeNode<Type>::HasChildren() const
{
	if (myRight == NULL)
	{
		if (myLeft == NULL)
		{
			return false;
		}
	}

	return true;
}

template<class Type>
bool CU::BinaryTreeNode<Type>::IsConnected() const
{
	return myTree != NULL;
}

template<class Type>
void CU::BinaryTreeNode<Type>::Connect(BinaryTree<Type>* aTree)
{
	if (aTree != NULL)
	{
		myTree = aTree;
	}
}

template<class Type>
void CU::BinaryTreeNode<Type>::Disconnect()
{
	if (myTree != NULL)
	{
		myTree = NULL;
		delete this;
	}
}

namespace CommonUtilities
{
	template<class Type>
	class BinaryTree
	{
	public:
		inline BinaryTree();
		inline ~BinaryTree();

		inline BinaryTree(const BinaryTree& aBinaryTree);
		inline BinaryTree& operator=(const BinaryTree& aBinaryTree);

		inline CU::BinaryTreeNode<Type>* GetRootNode() const;
		inline CU::BinaryTreeNode<Type>* Find(Type aValue) const;

		inline bool InsertNode(CU::BinaryTreeNode<Type>* aNode);
		inline bool InsertNode(Type aValueToInsert);

		inline void DeleteNode(CU::BinaryTreeNode<Type>* aNode);
		inline void DeleteNode(Type aValueToDelete);

		inline void PostOrderTraverse(void) const;
		inline void InOrderTraverse(void) const;

	private:
		inline void DeleteByMerging(CU::BinaryTreeNode<Type>*& aNode);

	private:
		CU::BinaryTreeNode<Type>* myRootNode;
		int myCounter;
	};
}

template<class Type>
CU::BinaryTree<Type>::BinaryTree()
{
	myRootNode = NULL;
	myCounter = 0;
}

template<class Type>
CU::BinaryTree<Type>::~BinaryTree()
{
}

template<class Type>
CU::BinaryTree<Type>::BinaryTree(const BinaryTree& aBinaryTree)
{
	myRootNode = NULL;
	myCounter = 0;

	Stack<CU::BinaryTreeNode<Type>*> stack(aBinaryTree.myCounter,1);
	CU::BinaryTreeNode<Type>* node = aBinaryTree.GetRootNode();

	while(node != NULL)
	{
		while(node != NULL)
		{
			if (node->GetRight() != NULL)
			{
				stack.Push(node->GetRight());
			}

			stack.Push(node);
			node = node->GetLeft();
		}

		node = stack.Pop();

		while (stack.Size() > 0 && node->GetRight() == NULL)
		{
			InsertNode(node->GetValue());
			node = stack.Pop();
		}

		InsertNode(node->GetValue());

		if (stack.Size() > 0)
		{
			node = stack.Pop();
		}
		else
		{
			node = NULL;
		}
	}
}

template<class Type>
CU::BinaryTree<Type>& CU::BinaryTree<Type>::operator=(const BinaryTree& aBinaryTree)
{
	Stack<CU::BinaryTreeNode<Type>*> stack(aBinaryTree.myCounter,1);
	CU::BinaryTreeNode<Type>* node = aBinaryTree.GetRootNode();

	while(node != NULL)
	{
		while(node != NULL)
		{
			if (node->GetRight() != NULL)
			{
				stack.Push(node->GetRight());
			}

			stack.Push(node);
			node = node->GetLeft();
		}

		node = stack.Pop();

		while (stack.Size() > 0 && node->GetRight() == NULL)
		{
			InsertNode(node->GetValue());
			node = stack.Pop();
		}

		InsertNode(node->GetValue());

		if (stack.Size() > 0)
		{
			node = stack.Pop();
		}
		else
		{
			node = NULL;
		}
	}

	return *this;
}

template<class Type>
CU::BinaryTreeNode<Type>* CU::BinaryTree<Type>::GetRootNode() const
{
	return myRootNode;
}

template<class Type>
bool CU::BinaryTree<Type>::InsertNode(CU::BinaryTreeNode<Type>* aNode)
{
	DL_ASSERT(aNode != NULL, "aNode == NULL");

	if (Find(aNode->GetValue()) == NULL)
	{
		if (aNode->HasChildren() == false)
		{
			CU::BinaryTreeNode<Type>* currentNode = GetRootNode();
			CU::BinaryTreeNode<Type>* previousNode = NULL;

			while(currentNode != NULL)
			{
				previousNode = currentNode;

				if (currentNode->GetValue() < aNode->GetValue())
				{
					currentNode = currentNode->GetRight();
				}
				else
				{
					currentNode = currentNode->GetLeft();
				}
			}

			if (myRootNode == NULL)
			{
				myRootNode = aNode;
			}
			else
			{
				if (previousNode->GetValue() < aNode->GetValue())
				{
					previousNode->SetRight(aNode);
				}
				else
				{
					previousNode->SetLeft(aNode);
				}
			}

			aNode->Connect(this);
			myCounter++;
			return true;
		}
	}

	return false;
}

template<class Type>
bool CU::BinaryTree<Type>::InsertNode(Type aValueToInsert)
{
	CU::BinaryTreeNode<Type> *newNode = new CU::BinaryTreeNode<Type>(aValueToInsert);
	bool isInserted = InsertNode(newNode);

	if (isInserted == false)
	{
		delete newNode;
	}

	return isInserted;
}

template<class Type>
void CU::BinaryTree<Type>::DeleteNode(CU::BinaryTreeNode<Type>* aNode)
{
	CU::BinaryTreeNode<Type>* parentNode = NULL;
	CU::BinaryTreeNode<Type>* currentNode = GetRootNode();

	while(currentNode != NULL)
	{
		if (currentNode == aNode)
		{
			break;
		}

		parentNode = currentNode;

		if (currentNode->GetValue() < aNode->GetValue())
		{
			currentNode = currentNode->GetRight();
		}
		else
		{
			currentNode = currentNode->GetLeft();
		}
	}

	if (currentNode != NULL && currentNode == aNode)
	{
		if (currentNode == GetRootNode())
		{
			DeleteByMerging(myRootNode);
		}
		else
		{
			if (parentNode->GetLeft() == currentNode)
			{
				DeleteByMerging(parentNode->myLeft);
			}
			else
			{
				DeleteByMerging(parentNode->myRight);
			}
		}

		myCounter--;
	}
}

template<class Type>
void CU::BinaryTree<Type>::DeleteNode(Type aValueToDelete)
{
	CU::BinaryTreeNode<Type>* parentNode = NULL;
	CU::BinaryTreeNode<Type>* currentNode = GetRootNode();

	while(currentNode != NULL)
	{
		if (currentNode->GetValue() == aValueToDelete)
		{
			break;
		}

		parentNode = currentNode;

		if (currentNode->GetValue() < aValueToDelete)
		{
			currentNode = currentNode->GetRight();
		}
		else
		{
			currentNode = currentNode->GetLeft();
		}
	}

	if (currentNode != NULL && currentNode->GetValue() == aValueToDelete)
	{
		if (currentNode == GetRootNode())
		{
			DeleteByMerging(myRootNode);
		}
		else
		{
			if (parentNode->GetLeft() == currentNode)
			{
				DeleteByMerging(parentNode->myLeft);
			}
			else
			{
				DeleteByMerging(parentNode->myRight);
			}
		}

		myCounter--;
	}
}

template<class Type>
void CU::BinaryTree<Type>::DeleteByMerging(CU::BinaryTreeNode<Type>*& aNode)
{
	CU::BinaryTreeNode<Type>* tmp = aNode;
	
	if (aNode != NULL) 
	{
		if (aNode->GetRight() == NULL)
		{
			aNode = aNode->GetLeft();
		}
		else 
		{
			if (aNode->GetLeft() == NULL)
			{
				aNode = aNode->GetRight();
			}
			else 
			{
				tmp = aNode->GetLeft();

				while (tmp->GetRight() != NULL)
				{
					tmp = tmp->myRight;
				}

				tmp->myRight = aNode->myRight;
				tmp = aNode;
				aNode = aNode->myLeft;
				
				tmp->Disconnect();
			}
		}
	}
}

template<class Type>
CU::BinaryTreeNode<Type>* CU::BinaryTree<Type>::Find(Type aValue) const
{
	CU::BinaryTreeNode<Type>* node = GetRootNode();

	while(node != NULL)
	{
		if (node->GetValue() == aValue)
		{
			return node;
		}
		else
		{
			if (aValue < node->GetValue())
			{
				node = node->GetLeft();
			}
			else
			{
				node = node->GetRight();
			}
		}
	}

	return NULL;
}

template<class Type>
void CU::BinaryTree<Type>::PostOrderTraverse(void) const
{
	CU::Stack<CU::BinaryTreeNode<Type>*> stack(myCounter,1);
	CU::BinaryTreeNode<Type>* currentNode = GetRootNode();
	CU::BinaryTreeNode<Type>* previousNode = GetRootNode();

	while (currentNode != NULL)
	{
		for (; currentNode->GetLeft() != NULL; currentNode = currentNode->GetLeft())
		{
			stack.Push(currentNode);
		}

		while (currentNode != NULL && (currentNode->GetRight() == NULL || currentNode->GetRight() == previousNode))
		{
			currentNode->Print();
			previousNode = currentNode;

			if (stack.Size() == 0)
			{
				return;
			}

			currentNode = stack.Pop();
		}

		stack.Push(currentNode);
		currentNode = currentNode->GetRight();
	}
}

template<class Type>
void CU::BinaryTree<Type>::InOrderTraverse(void) const
{
	Stack<CU::BinaryTreeNode<Type>*> stack(myCounter,1);
	CU::BinaryTreeNode<Type>* node = GetRootNode();

	while(node != NULL)
	{
		while(node != NULL)
		{
			if (node->GetRight() != NULL)
			{
				stack.Push(node->GetRight());
			}

			stack.Push(node);
			node = node->GetLeft();
		}

		node = stack.Pop();

		while (stack.Size() > 0 && node->GetRight() == NULL)
		{
			node->Print();
			node = stack.Pop();
		}

		node->Print();

		if (stack.Size() > 0)
		{
			node = stack.Pop();
		}
		else
		{
			node = NULL;
		}
	}
}

#endif
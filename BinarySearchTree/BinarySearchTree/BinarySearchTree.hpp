#pragma once
#include<iostream>
using namespace std;

template<class T>
struct BSTNode
{
	BSTNode(const T& data)
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _data(data)
	{}

	BSTNode<T>* _pLeft;
	BSTNode<T>* _pRight;
	T _data;
};


template<class T>
class BSTree
{
	typedef BSTNode<T> Node;
	typedef Node* PNode;

public:
	BSTree()
		: _pRoot(nullptr)
	{}

	bool Insert(const T& data)
	{
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}

		//找到插入的位置
		PNode pCur = _pRoot;
		PNode pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;
			if (data > pCur->_data)
				pCur = pCur->_pRight;
			else if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else
				return false;
		}

		//插入节点
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		return true;
	}

	bool Erase(const T& data)
	{
		//找待删除的节点
		PNode pCur = _pRoot;
		PNode pParent = nullptr;
		while (pCur)
		{
			if (data == pCur->_data)
				break;
			else if (data < pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}

		//未找到
		if (nullptr == pCur)
			return false;

		//删除该节点
		//只有右孩子
		if (nullptr == pCur->_pLeft)
		{
			//删除根节点，根节点只有右孩子
			if (nullptr == pParent)
			{
				_pRoot = pCur->_pRight;
				delete pCur;
			}
			//删除非根节点
			else
			{
				//删除的是父节点的左孩子节点
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pRight;
				//删除的是父节点的右孩子节点
				else
					pParent->_pRight = pCur->_pRight;

				delete pCur;
			}
				
		}
		//只有左孩子
		else if (nullptr == pCur->_pRight)
		{
		   //删除根节点,根节点只有左孩子
			if (nullptr == pParent)
			{
				_pRoot = pCur->_pLeft;
				delete pCur;
			}
			else
			{
				//删除非根节点，且该节点只有左孩子
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pLeft;
				else
					pParent->_pRight = pCur->_pLeft;

				delete pCur;
			}
		}
		else
		{
			//左右孩子都存在--在右子树中找最小的节点
			PNode pDelete = pCur->_pRight;
			pParent = pCur;
			while (pDelete->_pLeft)
			{
				pParent = pDelete;
				pDelete = pDelete->_pLeft;
			}

			pCur->_data = pDelete->_data;
			if (pDelete == pParent->_pLeft)
				pParent->_pLeft = pDelete->_pRight;
			else
				pParent->_pRight = pDelete->_pRight;

			delete pDelete;
		}

		return true;
	}

	PNode Find(const T& data)
	{
		PNode pCur = _pRoot;
		while (pCur)
		{
			if (data == pCur->_data)
				return pCur;
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
			else
				pCur = pCur->_pLeft;
		}

		return nullptr;
	}

	PNode MostLeft()
	{
		if (nullptr == _pRoot)
			return nullptr;

		PNode pCur = _pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}

	PNode MostRight()
	{
		if (nullptr == _pRoot)
			return nullptr;

		PNode pCur = _pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur; ` 
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}

	void Clear()
	{
		_Destroy(_pRoot);
	}

private:
	void _InOrder(PNode pRoot)
	{
		if (pRoot == nullptr)
			return;
		_InOrder(pRoot->_pLeft);
		cout << pRoot->_data << " ";
		_InOrder(pRoot->_pRight);
	}

	void _Destroy(PNode& pRoot)
	{
		if (nullptr == pRoot)
			return;
		_Destroy(pRoot->_pLeft);
		_Destroy(pRoot->_pRight);
		delete pRoot;
		pRoot = nullptr;
	}

private:
	PNode _pRoot;
};


void TestBSTree()
{
	int array[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> t;
	for (auto e : array)
		t.Insert(e);
	t.InOrder();
	cout << endl;

	t.Erase(2);
	t.InOrder();
	cout << endl;
	t.Erase(6);
	t.InOrder();
	cout << endl;
	t.Erase(5);
	t.InOrder();
	cout << endl;

	t.Clear();
	t.InOrder();
}
#pragma once
#include<iostream>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value)
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _data(key, value)
	, _bf(0)
	{}

	AVLTreeNode<K, V>* _pLeft;
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pParent;
	pair<K, V> _data;
	int _bf;      //平衡因子
};



template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
	typedef Node* PNode;

public:
	AVLTree()
		:_pRoot(nullptr)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(key, value);
			return true;
		}

		//找到插入得位置
		PNode pCur = _pRoot;
		PNode pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;
			if (key < pCur->_data.first)
				pCur = pCur->_pLeft;
			else if (key > pCur->_data.first)
				pCur = pCur->_pRight;
			else
				return false;
		}

		//插入节点
		pCur = new Node(key, value);
		if (pCur->_data.first < pParent->_data.first)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;

		//更新节点的平衡因子
		while (pParent)
		{
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			if (pParent->_bf == 0)
				break;
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{
				//树的高度增加了，并向上更新
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{
				//pParent的平衡因子2 或者-2，以pParent为为根的AVL树的平衡性被破坏了
				//以pParent为根的树进行旋转处理
				if (2 == pParent->_bf)
				{
					if (1 == pCur->_bf)
						RotateL(pParent);
					else
						RotateRL(pParent);
				}
				else
				{
					//pParent->_bf == -2
					if (-1 == pCur->_bf)
						RotateR(pParent);
					else
						RotateLR(pParent);
				}
				break;
			}
		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}

	~AVLTree()
	{
		_Destroy(_pRoot);
	}

	bool IsBalanceTree()
	{
		return _IsBalanceTree(_pRoot);
	}

private:
	void RotateL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;
		pSubR->_pLeft = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;

		if (nullptr == pPParent)
			_pRoot = pSubR;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}

		pSubR->_bf = pParent->_bf = 0;
	}

	void RotateR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		if (nullptr == pPParent)
			_pRoot = pSubL;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
		pParent->_bf = pSubL->_bf = 0;
	}

	void RotateLR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;

		RotateL(pParent->_pLeft);
		RotateR(pParent);

		if (1 == bf)
			pSubL->_bf = -1;
		else if (-1 == bf)
			pParent->_bf = 1;
	}

	void RotateRL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;

		RotateR(pParent->_pRight);
		RotateL(pParent);

		if (1 == bf)
			pParent->_bf = -1;
		else if (-1 == bf)
			pSubR->_bf = 1;
	}

	void _InOrder(PNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data.first << " " << pRoot->_data.second << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	void _Destroy(PNode pRoot)
	{
		if (pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}

	size_t Height(PNode pRoot)
	{
		if (pRoot == nullptr)
			return 0;
		size_t leftHeight = Height(pRoot->_pLeft);
		size_t rightHeight = Height(pRoot->_pRight);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool _IsBalanceTree(PNode pRoot)
	{
		if (nullptr == pRoot)
			return true;
		size_t leftHeight = Height(pRoot->_pLeft);
		size_t rightHeight = Height(pRoot->_pRight);
		int diff = rightHeight - leftHeight;
		if (abs(diff) >= 2 || diff != pRoot->_bf)
			return false;
		return _IsBalanceTree(pRoot->_pLeft) && _IsBalanceTree(pRoot->_pRight);
	}

private:
	PNode _pRoot;
};


void TestAVLTree()
{
	//int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> t;
	for (auto e : array)
		t.Insert(e, e);
	t.InOrder();
	cout << endl;

	if (t.IsBalanceTree())
		cout << "is" << endl;
	else
		cout << "no" << endl;
}
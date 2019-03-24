#pragma once
#include<iostream>
using namespace std;

#if 0
enum Color
{
	RED,
	BLACK
};

template<class V>
struct RBTreeNode
{

	RBTreeNode(const V& data = V(), Color color = RED)
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _data(data)
	, _color(color)
	{}

	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _data;
	Color _color;
};


template<class V>
class RBTree
{
	typedef RBTreeNode<V> Node;
	typedef Node* PNode;

public:
	RBTree()
	{
		_pHead = new Node();
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	~RBTree()
	{
		_Destroy(GetRoot());
	}

	bool Insert(const V& data)
	{
		PNode& _pRoot = GetRoot();
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data, BLACK);
			_pRoot->_pParent = _pHead;
			return true;
		}
		else
		{
			//按照二叉搜索树的性质插入节点
			PNode pCur = _pRoot;
			PNode pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_data)
					pCur = pCur->_pLeft;
				else if (data > pCur->_data)
					pCur = pCur->_pRight;
				else
					return false;
			}

			//插入节点
			pCur = new Node(data);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;

			//更新节点颜色,新插入的节点颜色为红色
			//pParent节点颜色如果为红色，违反性质三：不能有连在一起的红色节点
			while (_pHead != pParent && RED == pParent->_color)
			{
				PNode grandParent = pParent->_pParent;
				if (pParent == grandParent->_pLeft)
				{
					PNode uncle = grandParent->_pRight;
					//情况一：
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandParent->_color = RED;
						pCur = grandParent;
						pParent = pCur->_pParent;
					}
					else
					{
						//叔叔节点不存在 || 叔叔节点存在&&黑色
						if (pCur == pParent->_pRight)
						{
							//情况三
							RotateL(pParent);
							swap(pCur, pParent);
						}

						//情况二
						grandParent->_color = RED;
						pParent->_color = BLACK;
						RotateR(grandParent);
					}
				}
				else
				{
					PNode uncle = grandParent->_pLeft;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandParent->_color = RED;
						pCur = grandParent;
						pParent = pCur->_pParent;
					}
					else
					{
						if (pCur == pParent->_pLeft)
						{
							//情况三
							RotateR(pParent);
							swap(pCur, pParent);
						}

						grandParent->_color = RED;
						pParent->_color = BLACK;
						RotateL(grandParent);
					}
				}
			}
		}

		_pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}

	bool IsValidRBTree()
	{
		PNode pRoot = GetRoot();
		if (pRoot == nullptr)
			return true;
		if (pRoot->_color != BLACK)
		{
			cout << "违反性质1：根节点不为黑色" << endl;
			return false;
		}

		//获取一条路径中黑色节点个数
		size_t blackCount = 0;
		PNode pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
				blackCount++;

			pCur = pCur->_pLeft;
		}

		size_t pathBlackCount = 0;
		return _IsValidRBTree(pRoot, blackCount, pathBlackCount);
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

		if (_pHead == pPParent)
			_pHead->_pParent = pSubR;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
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

		PNode _pRoot = GetRoot();
		if (_pHead == pPParent)
			_pHead->_pParent = pSubL;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}

	PNode& GetRoot()
	{
		return _pHead->_pParent;
	}

	PNode LeftMost()
	{
		PNode pCur = GetRoot();
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}

	PNode RightMost()
	{
		PNode pCur = GetRoot();
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur;
	}

	void _InOrder(PNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	void _Destroy(PNode& pRoot)
	{
		if (pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}



	bool _IsValidRBTree(PNode pRoot, size_t blackCount, size_t pathBlackCount)
	{
		if (nullptr == pRoot)
			return true;

		if (BLACK == pRoot->_color)
			pathBlackCount++;

		PNode pParent = pRoot->_pParent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}

		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlackCount != blackCount)
			{
				cout << "违反性质四：路径中黑色节点个数不同" << endl;
				return false;
			}
		}

		return _IsValidRBTree(pRoot->_pLeft, blackCount, pathBlackCount) &&
			_IsValidRBTree(pRoot->_pRight, blackCount, pathBlackCount);
	}
private:
	PNode _pHead;
};

void TestRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int> t;
	for (auto e : array)
		t.Insert(e);
	t.InOrder();

	if (t.IsValidRBTree())
		cout << "is" << endl;
	else
		cout << "no" << endl;
}


#endif



enum Color
{
	RED,
	BLACK
};

template<class V>
struct RBTreeNode
{

	RBTreeNode(const V& data = V(), Color color = RED)
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _data(data)
	, _color(color)
	{}

	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _data;
	Color _color;
};


template<class V>
struct RBTreeIterator
{
	typedef RBTreeNode<V> Node;
	typedef Node* PNode;
	typedef RBTreeIterator<V> Self;

	RBTreeIterator(PNode pNode = nullptr)
		: _PNode(pNode)
	{}

	RBTreeIterator(const Self& s)
		:_PNode(s._PNode)
	{}

	V& operator*()
	{
		return _PNode->_data;
	}

	V* operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		Increasement();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Increasement();
		return temp;
	}

	Self& operator--()
	{
		Decreasement();
		return *this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		Decreasement();
		return temp;
	}

	void Increasement()
	{
		if (_PNode->_pRight)
		{
			_PNode = _PNode->_pRight;
			while (_PNode->_pLeft)
				_PNode = _PNode->_pLeft;
		}
		else
		{
			PNode pParent = _PNode->_pParent;
			while (_PNode == pParent->_pRight)
			{
				_PNode = pParent;
				pParent = _PNode->_pParent;
			}
			
			//根节点没有右孩子
			if (_PNode->_pRight != pParent)
				_PNode = pParent;
		}
	}

	void Decreasement()
	{
		if (_PNode == _PNode->_pParent->_pParent && RED == _PNode->_color)
		{
			_PNode = _PNode->_pRight;
		}
		if (_PNode->_pLeft)
		{
			_PNode = _PNode->_pLeft;
			while (_PNode->_pRight)
				_PNode = _PNode->_pRight;
		}
		else
		{
			PNode pParent = _PNode->_pParent;
			while (_PNode == pParent->_pLeft)
			{
				_PNode = pParent;
				pParent = _PNode->_pParent;
			}

			_PNode = pParent;
		}

	}

	bool operator!=(const Self& s)const 
	{
		return _PNode != s._PNode;
	}

	bool operator==(const Self& s)const
	{
		return _PNode == s._PNode;
	}

	PNode _PNode;
};


template<class V, class keyOfValue>
class RBTree
{
	typedef RBTreeNode<V> Node;
	typedef Node* PNode;
public:typedef RBTreeIterator<V> Iterator;

public:
	RBTree()
		: _size(0)
	{
		_pHead = new Node();
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	Iterator Begin()
	{
		return Iterator(_pHead->_pLeft);
	}

	Iterator End()
	{
		return Iterator(_pHead);
	}

	~RBTree()
	{
		_Destroy(GetRoot());
	}

	pair<Iterator, bool> Insert(const V& data)
	{
		PNode pNewNode = nullptr;
		PNode& _pRoot = GetRoot();
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data, BLACK);
			_pRoot->_pParent = _pHead;
			++_size;
			return make_pair(Iterator(_pRoot), true);
		}
		else
		{
			//按照二叉搜索树的性质插入节点
			PNode pCur = _pRoot;
			PNode pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (keyOfValue()(data) < keyOfValue()(pCur->_data))
					pCur = pCur->_pLeft;
				else if (keyOfValue()(data) > keyOfValue()(pCur->_data))
					pCur = pCur->_pRight;
				else
					return make_pair(Iterator(pCur), false);
			}

			//插入节点
			pCur = new Node(data);
			pNewNode = pCur;
			if (keyOfValue()(data) < keyOfValue()(pParent->_data))
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;

			//更新节点颜色,新插入的节点颜色为红色
			//pParent节点颜色如果为红色，违反性质三：不能有连在一起的红色节点
			while (_pHead != pParent && RED == pParent->_color)
			{
				PNode grandParent = pParent->_pParent;
				if (pParent == grandParent->_pLeft)
				{
					PNode uncle = grandParent->_pRight;
					//情况一：
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandParent->_color = RED;
						pCur = grandParent;
						pParent = pCur->_pParent;
					}
					else
					{
						//叔叔节点不存在 || 叔叔节点存在&&黑色
						if (pCur == pParent->_pRight)
						{
							//情况三
							RotateL(pParent);
							swap(pCur, pParent);
						}

						//情况二
						grandParent->_color = RED;
						pParent->_color = BLACK;
						RotateR(grandParent);
					}
				}
				else
				{
					PNode uncle = grandParent->_pLeft;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandParent->_color = RED;
						pCur = grandParent;
						pParent = pCur->_pParent;
					}
					else
					{
						if (pCur == pParent->_pLeft)
						{
							//情况三
							RotateR(pParent);
							swap(pCur, pParent);
						}

						grandParent->_color = RED;
						pParent->_color = BLACK;
						RotateL(grandParent);
					}
				}
			}
		}

		_pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		++_size;
		return make_pair(Iterator(pNewNode), true);
	}

	bool Empty()const 
	{
		return _size == 0;
	}

	size_t Size()const
	{
		return _size;
	}

	Iterator Find(const V& key)
	{
		PNode pCur = GetRoot();
		while (pCur)
		{
			if (keyOfValue()(key) == keyOfValue()(pCur->_data))
				return Iterator(pCur);
			else if (keyOfValue()(key) < keyOfValue()(pCur->_data))
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}

		return this->End();
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}

	bool IsValidRBTree()
	{
		PNode pRoot = GetRoot();
		if (pRoot == nullptr)
			return true;
		if (pRoot->_color != BLACK)
		{
			cout << "违反性质1：根节点不为黑色" << endl;
			return false;
		}

		//获取一条路径中黑色节点个数
		size_t blackCount = 0;
		PNode pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
				blackCount++;

			pCur = pCur->_pLeft;
		}

		size_t pathBlackCount = 0;
		return _IsValidRBTree(pRoot, blackCount, pathBlackCount);
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

		if (_pHead == pPParent)
			_pHead->_pParent = pSubR;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
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

		PNode _pRoot = GetRoot();
		if (_pHead == pPParent)
			_pHead->_pParent = pSubL;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}

	PNode& GetRoot()
	{
		return _pHead->_pParent;
	}

	PNode LeftMost()
	{
		PNode pCur = GetRoot();
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}

	PNode RightMost()
	{
		PNode pCur = GetRoot();
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur;
	}

	void _InOrder(PNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	void _Destroy(PNode& pRoot)
	{
		if (pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}



	bool _IsValidRBTree(PNode pRoot, size_t blackCount, size_t pathBlackCount)
	{
		if (nullptr == pRoot)
			return true;

		if (BLACK == pRoot->_color)
			pathBlackCount++;

		PNode pParent = pRoot->_pParent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}

		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlackCount != blackCount)
			{
				cout << "违反性质四：路径中黑色节点个数不同" << endl;
				return false;
			}
		}

		return _IsValidRBTree(pRoot->_pLeft, blackCount, pathBlackCount) &&
			_IsValidRBTree(pRoot->_pRight, blackCount, pathBlackCount);
	}
private:
	PNode _pHead;
	size_t _size;
};

#if 0
void TestRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int> t;
	for (auto e : array)
		t.Insert(e);
	t.InOrder();

	if (t.IsValidRBTree())
		cout << "is" << endl;
	else
		cout << "no" << endl;

	RBTree<int>::Iterator it = t.Begin();
	while (it != t.End())
	{
		++it;
	}
	cout << endl;
}

#endif

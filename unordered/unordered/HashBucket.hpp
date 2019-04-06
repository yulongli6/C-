#pragma once

#include<iostream>
#include<vector>
#include"Common.h"
using namespace std;

template<class V>
struct HashNode
{
	HashNode(const V& data = V())
		:	_pNext(nullptr)
		, _data(data)
	{}
	HashNode<V>* _pNext;
	V _data;
};

template<class V, class K, class KOFV, class KTOINT>
class HashBucket;

template<class V, class K, class KOFV, class KTOINT>
struct HashBucketIterator
{
	typedef HashBucketIterator<V, K, KOFV, KTOINT> self;
	typedef HashNode<V> Node;
	typedef Node* pNode;
public:
	HashBucketIterator(HashBucket<V, K, KOFV, KTOINT>* pHb, pNode pnode = nullptr)
		: _pHb(pHb)
		, _pNode(pnode)
	{}

	HashBucketIterator(const self& s)
		: _pHb(s._pHb)
		, _pNode(s._pNode)
	{}

	V& operator*()
	{
		return _pNode->_data;
	}

	V* operator->()
	{
		return &(operator*());
	}

	self& operator++()
	{
		Next();
		return *this;
	}

	self operator++(int)
	{
		self temp(*this);
		Next();
		return temp;
	}

	bool operator!=(const self& s)const
	{
		return _pNode != s._pNode;
	}

	bool operator==(const self& s)const
	{
		return _pNode == s._pNode;
	}
private:
	void Next()
	{
		if (_pNode->_pNext)
			_pNode = _pNode->_pNext;
		else
		{
			size_t bucketNo = _pHb->HashFunc(KOFV()(_pNode->_data)) + 1;
			for (; bucketNo < _pHb->_table.capacity(); ++bucketNo)
			{
				_pNode = _pHb->_table[bucketNo];
				if (_pNode)
					return;
			}

			_pNode = nullptr;
		}
	}
private:
	pNode _pNode;
	HashBucket<V, K, KOFV, KTOINT>* _pHb;
};

//v:哈希桶中的元素-----key  <key， value>
//KOFV:从V中提取key的方法
//KTOINT：将key转换为整形
template<class V, class K, class KOFV, class KTOINT>
class HashBucket
{
	friend  HashBucketIterator<V, K, KOFV, KTOINT>;
	typedef HashNode<V> Node;
	typedef Node* pNode;
	typedef HashBucket<V, K, KOFV, KTOINT> self;
public:
	typedef  HashBucketIterator<V, K, KOFV, KTOINT> Iterator;
public:
	HashBucket(size_t capacity = 10)
		: _size(0)
	{
		_table.resize(capacity/*GetNextPrime(capacity)*/);
	}

	~HashBucket()
	{
		Clear();
	}

	Iterator Begin()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			if (_table[bucketNo])
				return Iterator(this, _table[bucketNo]);
		}
		return End();
	}

	Iterator End()
	{
		return Iterator(this, nullptr);
	}

	pair<Iterator, bool> InsertUnique(const V& data)
	{
		_CheckCapacity();

		//1.计算哈希桶号
		size_t bucketNo = HashFunc(KOFV()(data));

		//检测key是否存在
		pNode pCur = _table[bucketNo];
		while (pCur)
		{
			if (KOFV()(data) == KOFV()(pCur->_data))
				return make_pair(Iterator(this, pCur), false);
			pCur = pCur->_pNext;
		}

		//插入节点
		pCur = new Node(data);
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		_size++;
		return make_pair(Iterator(this, pCur), true);
	}

	size_t EraseUnique(const K& key)
	{
		//计算哈希桶桶号
		size_t bucketNo = HashFunc(key);

		//在bucketNo桶中找key
		pNode pCur = _table[bucketNo];
		pNode pPre = nullptr;
		while (pCur)
		{
			if (key == KOFV()(pCur->_data))
			{
				if (pPre == nullptr)
					_table[bucketNo] = pCur->_pNext;
				else
					pPre->_pNext = pCur->_pNext;
				delete pCur;
				_size--;
				return 1;
			}
			else
			{
				pPre = pCur;
				pCur = pCur->_pNext;
			}
		}
		return 0;
	}

	bool InsertEqual(const V& data)
	{
		_CheckCapacity();
		size_t bucketNo = HashFunc(KOFV()(data));

		pNode pNewNode = new Node(data);
		pNode pCur = _table[bucketNo];
		while (pCur)
		{
			if (KOFV()(data) == KOFV()(pCur->_data))
			{
				break;
			}
			else
				pCur = pCur->_pNext;
		}

		if (pCur == nullptr)
		{
			pNewNode->_pNext = _table[bucketNo];
			_table[bucketNo] = pNewNode;
		}
		else
		{
			pNewNode->_pNext = pCur->_pNext;
			pCur->_pNext = pNewNode;
		}

		_size++;
		return true;
	}

	//删除所有值为key的元素
	bool EraseEqual(const K& key)
	{
		size_t bucketNo = HashFunc(key);
		size_t oldSize = _size;
		pNode pCur = _table[bucketNo];
		pNode pPre = nullptr;
		while (pCur)
		{
			if (key == KOFV()(pCur->_data))
			{
				if (pPre == nullptr)
				{
						_table[bucketNo] = pCur->_pNext;
						delete pCur;
						pCur = _table[bucketNo];
				}
				else
				{
					pPre->_pNext = pCur->_pNext;
					delete pCur;
					pCur = pPre->_pNext;
				}
				_size--;
			}
			else
			{
				pPre = pCur;
				pCur = pCur->_pNext;
			}
		}

		return oldSize != _size;
	}

	Iterator Find(const K& key)
	{
		size_t bucketNo = HashFunc(key);
		pNode pCur = _table[bucketNo];
		while (pCur)
		{
			if (key == KOFV()(pCur->_data))
				return Iterator(this, pCur);
			pCur = pCur->_pNext;
		}
		return Iterator(this, nullptr);
	}

	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	size_t Count(const K& key)
	{
		size_t bucketNo = HashFunc(key);
		pNode pCur = _table[bucketNo];
		size_t count = 0;
		while (pCur)
		{
			if (key == KOFV()(pCur->_data))
				count++;
			pCur = pCur->_pNext;
		}
		return count;
	}

	void Clear()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			pNode pCur = _table[bucketNo];
			while (pCur)
			{
				_table[bucketNo] = pCur->_pNext;
				delete pCur;
				pCur = _table[bucketNo];
			}
		}
	}

	void Swap(self& hb)
	{
		this->_table.swap(hb._table);
		swap(this->_size, hb._size);
	}

	size_t BucketCount()const
	{
		return _table.capacity();
	}

	size_t BucketSize(size_t bucketNo)
	{
		size_t count = 0;
		pNode pCur = _table[bucketNo];
		while (pCur)
		{
			count++;
			pCur = pCur->_pNext;
		}

		return count;
	}

	void PrintHashBucket()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			cout << "_table[" << bucketNo << "]:";
			pNode pCur = _table[bucketNo];
			while (pCur)
			{
				cout << pCur->_data << "--->";
				pCur = pCur->_pNext;
			}
			cout << "NULL" << endl;
		}
	}
private:
	void _CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			self newHb(GetNextPrime(_size));

			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				pNode pCur = _table[i];
				while (pCur)
				{	
					_table[i] = pCur->_pNext;
					//不好，节点重复重建
					//newHb.InsertEqual(pCur->_data);
					size_t bucketNo = newHb.HashFunc(KOFV()(pCur->_data));

					pNode pPos = newHb._table[bucketNo];
					while (pPos)
					{
						if (KOFV()(pPos->_data) == KOFV()(pCur->_data))
							break;
						pPos = pPos->_pNext;
					}
					if (pPos == nullptr)
					{
						pCur->_pNext = newHb._table[bucketNo];
						newHb._table[bucketNo] = pCur;
					}
					else
					{
						pCur->_pNext = pPos->_pNext;
						pPos->_pNext = pCur;
					}

					++newHb._size;
					pCur = _table[i];
				}
			}

			Swap(newHb);
		}
	}

	size_t HashFunc(const K& key)
	{
		return (KTOINT()(key)) % _table.capacity();
	}
private:
	vector<pNode> _table;
	size_t _size;   //哈希桶中有效元素的个数
};

struct KeyOfValue
{
	int operator()(int key)
	{
		return key;
	}
};

#if 0
void Test1()
{
	HashBucket<int, int, KeyOfValue, KTOINTDef<int>> hb;
	hb.InsertUnique(1);
	hb.InsertUnique(2);
	hb.InsertUnique(3);
	hb.InsertUnique(4);
	hb.InsertUnique(1);
	hb.InsertUnique(1);
	hb.InsertUnique(5);
	cout << hb.Size() << endl;
	cout << hb.BucketSize(1) << endl;
	cout << hb.BucketCount() << endl;
	cout << hb.Count(1) << endl;
	hb.PrintHashBucket();
	cout << "========================================" << endl;

	hb.InsertUnique(19);
	hb.InsertUnique(25);
	hb.InsertUnique(34);
	hb.InsertUnique(44);
	hb.InsertUnique(100);
	hb.InsertUnique(15);
	cout << hb.Size() << endl;
	cout << hb.BucketSize(1) << endl;
	cout << hb.BucketCount() << endl;
	cout << hb.Count(1) << endl;
	hb.PrintHashBucket();
	

	auto it = hb.Begin();
	while (it != hb.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

}
void Test2()
{
	HashBucket<int, int, KeyOfValue, KTOINTDef<int>> hb;
	hb.InsertEqual(1);
	hb.InsertEqual(2);
	hb.InsertEqual(3);
	hb.InsertEqual(4);
	hb.InsertEqual(1);
	hb.InsertEqual(1);
	hb.InsertEqual(5);
	cout << hb.Size() << endl;
	cout << hb.BucketSize(1) << endl;
	cout << hb.BucketCount() << endl;
	cout << hb.Count(1) << endl;
	hb.PrintHashBucket();
	cout << "========================================" << endl;

	hb.InsertEqual(19);
	hb.InsertEqual(25);
	hb.InsertEqual(34);
	hb.InsertEqual(44);
	hb.InsertEqual(100);
	hb.InsertEqual(15);
	cout << hb.Size() << endl;
	cout << hb.BucketSize(1) << endl;
	cout << hb.BucketCount() << endl;
	cout << hb.Count(1) << endl;
	hb.PrintHashBucket();
	cout << "=============================" << endl;
	hb.EraseEqual(1);
	hb.PrintHashBucket();

	auto it = hb.Begin();
	while (it != hb.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

}

#endif
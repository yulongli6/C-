#pragma once

#include"HashBucket.hpp"
#include<assert.h>
//#include<utility>

template<class K>
class unorderedmultiSet
{
	typedef K ValueType;
	struct KeyOfValue
	{
		const K& operator()(const ValueType& data)
		{
			return data;
		}
	};
	typedef HashBucket<ValueType, K, KeyOfValue, KTOINTDef<int>> HashBucket;
	typename typedef HashBucket::Iterator Iterator;
public:
	unorderedmultiSet()
		:_hb()
	{}

	Iterator Begin()
	{
		return _hb.Begin();
	}

	Iterator End()
	{
		return _hb.End();
	}

	size_t Size()const
	{
		return _hb.Size();
	}

	bool Empty()const
	{
		return _hb.Empty();
	}

	Iterator Find(const K& key)
	{
		return _hb.Find(key);
	}

	size_t Count(const K& key)
	{
		return _hb.Count(key);
	}

	size_t BucketCount()const
	{
		return _hb.BucketCount();
	}

	size_t BucketSize(size_t n)
	{
		return _hb.BucketSize(n);
	}

	Iterator Insert(const ValueType& value)
	{
		return _hb.InsertEqual(value);
	}

	size_t Erase(const K& key)
	{
		return _hb.EraseEqual(key);
	}
private:
	HashBucket _hb;
};

void TestunorderedmultiSet()
{
	int array[] = { 4, 3, 0, 9, 1, 7, 2, 8, 5, 6, 9, 9, 9 };
	unorderedmultiSet<int> m;
	for (auto e : array)
		m.Insert(e);

	cout << m.Size() << endl;

	cout << m.BucketCount() << endl;
	cout << m.BucketSize(10) << endl;

	auto it = m.Begin();
	while (it != m.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	m.Insert(1);
	cout << m.Size() << endl;

	m.Erase(1);
	it = m.Begin();
	while (it != m.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

#pragma once

#include"HashBucket.hpp"
#include<assert.h>
//#include<utility>

template<class K, class V>
class unorderedMap
{
	typedef pair<K, V> ValueType;
	struct KeyOfValue
	{
		const K& operator()(const ValueType& data)
		{
			return data.first;
		}
	};
	typedef HashBucket<ValueType, K, KeyOfValue, KTOINTDef<int>> HashBucket;
	typename typedef HashBucket::Iterator Iterator;
public:
	unorderedMap()
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

	V& operator[](const K& key)
	{
		Iterator it = _hb.Find(key);
		assert(it != End());
		return it->second;
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

	pair<Iterator, bool>Insert(const ValueType& value)
	{
		return _hb.InsertUnique(value);
	}

	size_t Erase(const K& key)
	{
		return _hb.EraseUnique(key);
	}
private:
	HashBucket _hb;
};




#if 0
void TestunorderMap()
{
	int array[] = { 4, 3, 0, 9, 1, 7, 2, 8, 5, 6 };
	unorderedMap<int, int> m;
	for (auto e : array)
		m.Insert(std::make_pair(e, e));

	cout << m.Size() << endl;

	cout << m.BucketCount() << endl;
	cout << m.BucketSize(10) << endl;
	cout << m[1] << endl;
	auto it = m.Begin();
	while (it != m.End())
	{
		cout << it->first << "--->" << it->second << endl;
		it++;
	}
	cout << endl;

	m.Insert(make_pair(1, 10));
	cout << m.Size() << endl;

	m.Erase(1);
	it = m.Begin();
	while (it != m.End())
	{
		cout << it->first << "--->" << it->second << endl;
		it++;
	}
	cout << endl;
}

#endif
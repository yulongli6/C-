#include"RBTree.hpp"

template<class K>
class my_set
{
	struct keyOfValue
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
	typedef RBTree<K, keyOfValue> RBT;
public:
	typename typedef RBT::Iterator Iterator;
public:
	my_set()
		:_t()
	{}

	Iterator Begin()
	{
		return _t.Begin();
	}

	Iterator End()
	{
		return _t.End();
	}

	bool Empty()const
	{
		return _t.Empty();
	}

	size_t Size()const
	{
		return _t.Size();
	}

	pair<Iterator, bool> Insert(const K& key)
	{
		return _t.Insert(key);
	}

	// ±º‰∏¥‘”∂» O(logN)
	Iterator Find(const K& key)
	{
		return _t.Find(key);
	}

private:
	RBT _t;
};


void my_setTest()
{
	my_set<int> s;
	int array[] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9 };
	for (auto e : array)
		s.Insert(e);

	cout << s.Size() << endl;

	if (s.Find(5) != s.End())
		cout << "is" << endl;
	else
		cout << "is not" << endl;
	auto it = s.Begin();
	while (it != s.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

}
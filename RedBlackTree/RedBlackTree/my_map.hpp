#include"RBTree.hpp"



template<class K, class V>
class my_map
{
	typedef pair<K, V> valueType;
	
	struct keyOfValue
	{
		const K& operator()(const valueType& Pair)
		{
			return Pair.first;
		}
	};
	typedef RBTree<valueType, keyOfValue> RBT;

public:
	//当成静态成员变量变量
	typename typedef RBT::Iterator Iterator;
public:
	my_map()
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

	bool Empty()
	{
		return _t.Empty();
	}

	size_t Size()
	{
		return _t.Size();
	}

	V& operator[](const K& key)
	{
		return (*((this->Insert(make_pair(key, V()))).first)).second;
	}

	Iterator Find(const K& key)
	{
		return _t.Find(make_pair(key, V()));
	}

	pair<Iterator, bool>Insert(const valueType& data)
	{
		return _t.Insert(data);
	}

private:
	RBT _t;
};


void my_mapTest()
{
  my_map<int, int> m;
  int array[] = { 9, 1, 2, 3, 0, 8, 7, 5, 6, 4 };
  for (auto e : array)
	  m.Insert(make_pair(e, e));
  cout << m.Size() << endl;

  cout << m[5] << endl;

  if (m.Find(8) != m.End())
	  cout << "8 is in map" << endl;
  else
	  cout << "8 is not in map" << endl;
  auto it = m.Begin();
  while (it != m.End())
  {
	  cout << it->first << "--->" << it->second << endl;
	  ++it;
  }
}
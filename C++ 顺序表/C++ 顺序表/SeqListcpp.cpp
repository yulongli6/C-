#define _CRT_SECURE_NO_DEPRECATE 1

#include<assert.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

template<class T>
class SeqList
{
	friend ostream& operator<<(ostream& _cout, const SeqList<T>& s)
	{
		for (size_t i = 0; i < s._size; ++i)
			_cout << s._pArray[i] << " ";
		return _cout;
	}

	friend void PrintSeqList(const SeqList<T>& s)
	{
		cout << s << endl;
	}
public:
	//构造函数
	SeqList(size_t capacity = 10)
		:_pArray(new T[capacity + 3])
		,_size(0)
		,_capacity(capacity + 3)
	{}

	//拷贝构造函数
	SeqList(const SeqList& s)
	{
		_pArray = new T[s._size];
		memcpy(_pArray, s._pArray, sizeof(T)*s._size);
		_size = s._size;
		_capacity = s._size;
	}

	SeqList& operator=(const SeqList& s)
	{
		if (*this != s)
		{
			T* temp = new T[s._size];
			memcpy(temp, s._pArray, sizeof(T)*s._size);
			delete[] _pArray;
			_pArray = temp;
			_size = s._size;
			_capacity = s._size;
		}

		return *this;
	}


	T& operator[](size_t index)
	{
		assert(index < _capacity);
		return _pArray[index];
	}

	const T& operator[](size_t index)const
	{
		assert(index < _capacity);
		return _pArray[index];
	}

	

	//析构函数
	~SeqList()
	{
		delete[] _pArray;
		_pArray = nullptr;
	}

/**************************************************************************/

	void PushBack(const T& data)
	{
		_CheckCapacity();
		_pArray[_size++] = data;
	}

	void PopBack()
	{
		_size--;
	}


	//指定位置插入元素
	void Insert(size_t pos, const T& data)
	{
		assert(pos <= _size);
		_CheckCapacity();
		for (size_t i = _size; i > pos; --i)
			_pArray[i] = _pArray[i - 1];
		_pArray[pos] = data;
		_size++;
	}

	//删除指定位置元素
	void _Erase(size_t pos)
	{
		assert(pos <= _size);
		for (size_t i = pos; i < _size; ++i)
			_pArray[i] = _pArray[i + 1];
		_size--;
	}


	//查找元素：好到返回下标，找不到返回-1；
	int Find(const T& data)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_pArray[i] == data)
				return i;
		}
		return -1;
	}


	//删除指定的元素中的第一个
	void Remove(const T& data)
	{
		int pos = Find(data);
		if (pos == -1)
			return -1;
		Erase(pos);
	}

	void RemoveAll(const T& data)
	{
		size_t i = 0;
		size_t j = 0;
		for (; i < _size; ++i)
		{
			if (_pArray[i] != data)
				_pArray[j++] = _pArray[i];
		}
		_size = j;
	}



	size_t Size()
	{
		return _size;
	}

	size_t Capacity()
	{
		return _capacity;
	}

	/**************************迭代器**********************************/
	T* begin()
	{
		return _pArray;
	}

	T* end()
	{
		return _pArray + (_size - 1);
	}
private:
	void _CheckCapacity()
	{
		size_t newCapacity = 2 * _capacity;
		if (_size >= _capacity)
		{
			T* temp = new T[newCapacity];
			for (size_t i = 0; i < _size; ++i){
				temp[i] = _pArray[i];
			}

			delete[] _pArray;
			_pArray = temp;
			_capacity = newCapacity;
		}
	}
private:
	T* _pArray;
	size_t _size;
	size_t _capacity;
};




int main()
{
	SeqList<int> s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.Insert(2, 10);
	cout << s1 << endl;
	s1.PopBack();
	s1.PopBack();
	
	SeqList<double> s2;
	s2.PushBack(1.0);
	s2.PushBack(1.1);
	s2.PushBack(1.2);
	s2.PushBack(1.3);


	SeqList<int> s3(s1);
	SeqList<double> s4 = s2;
	cout << s3[0] << endl;
	cout << s3.Find(1) << endl;
	return 0;
}

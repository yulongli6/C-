#define _CRT_SECURE_NO_DEPRECATE 1

#include<assert.h>
#include<iostream>
using namespace std;

template<class T>
class SList;

template<class T>
class ListNode
{
	friend SList<T>;
public:
	ListNode(const T& data)
		: _next(nullptr)
		, _data(data)
	{}

	T& Getdate()
	{
		return _data;
	}

	ListNode<T>* Getnext()
	{
		return _next;
	}
private:
	T _data;
	ListNode<T>* _next;
};


template <class T>
class SList
{
	friend ostream& operator<<(ostream& _cout, SList<T>& s)
	{
		for (ListNode<T>* cur = s._head; cur != nullptr; cur = cur->Getnext())
			_cout << cur->Getdate() << "--->";
		return _cout;
	}
public: 
	SList()
		:_head(nullptr)
		,_tail(nullptr)
	{}

	SList(const SList<T>& s)
		:_head(nullptr)
		,_tail(nullptr)
	{
		if (!s._head)
			return;
		ListNode<T>* cur(s._head);
		while (cur)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}


	/*SList<T>& operator=(const SList<T>& s)
	{
		if (this != &s){
			~SList();
			ListNode<T>* cur = s._head;
			while (cur)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}*/

	SList<T> operator=(SList<T> s)
	{
		swap(_head, s._head);
		swap(_tail, s._tail);
		return *this;
	}


	~SList()
	{
		ListNode<T>* cur = _head;
		while (cur)
		{
			ListNode<T>* del = cur;
			cur = cur->_next;
			delete del;
			del = nullptr;
		}
	}


	/*******************************链表操作********************************************/
	//尾插
	void PushBack(const T& data)
	{
		ListNode<T>* node = new ListNode<T>(data);
		if (!_head){
			_head = node;
			_tail = node;
		}
		else
		{
			_tail->_next = node;
			_tail = node;
		}
	}

	//尾删
	void PopBack()
	{
		if (_head == nullptr)
			cout << "empty" << endl;
		else if (_head == _tail)
		{
			delete _tail;
			_head = _tail = nullptr;
		}
		else
		{
			ListNode<T>* cur = _head;
			while (cur->_next != _tail)
			{
				cur = cur->_next;
			}
			delete _tail;
			_tail = cur;
			_tail->_next = nullptr;
		}
	}

	//头插
	void PushFront(const T& data)
	{
		ListNode<T>* node = new ListNode<T>(data);
		if (_head == nullptr)
			_head = _tail = node;
		else
		{
			node->_next = _head;
			_head = node;
		}
	}


	//头删
	void PopFront()
	{
		if (_head == nullptr)
			return;
		else if (_head == _tail)
		{
			delete _tail;
			_tail = _head = nullptr;
		}
		else
		{
			ListNode<T>* del = _head;
			_head = del->_next;
			delete del;
			del = nullptr;
		}
	}

	//指定节点前插入
	void Insert(ListNode<T>* pos, const T& data)
	{
		assert(pos);
		ListNode<T>* node = new ListNode<T>(data);
		ListNode<T>* cur = _head;
		if (_head == _tail)
			PushFront(data);
		else{
			while (cur->_next != pos)
				cur = cur->_next;
			node->_next = pos;
			cur->_next = node;
		}
	}


	//删除指定节点
	void Erase(ListNode<T>* pos)
	{
		assert(pos);
		if (_head == _tail)
			PopFront();
		else
		{
			ListNode<T>* cur = _head;
			while (cur->_next != pos)
				cur = cur->_next;
			cur->_next = pos->_next;
			delete pos;
			pos = nullptr;
		}
	}


	//查找
	ListNode<T>* Find(const T& data)
	{
		ListNode<T>* cur = _head;
		while (cur)
		{
			if (cur->_data == data)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return nullptr;
	}

	//打印
	void PrintSList()
	{
		cout << *this << "nullptr" << endl;
	}


private:
	ListNode<T>* _head;
	ListNode<T>* _tail;
};




int main()
{
	SList<int> s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	SList<int> s2(s1);

	s1 = s2;
	/**************************************************************/
	SList<char> s3;
	s3.PushBack('a');
	s3.PushBack('b');
	s3.PushBack('c');
	s3.PushBack('d');
	s3.PushBack('e');
	s3.PopBack();
	s3.PopBack();
	cout << s3 << "nullptr" << endl;
	s3.PushFront('f');
	s3.PushFront('f');
	s3.PushFront('f');
	cout << s3 << "nullptr" << endl;
	s3.PopFront();
	s3.PopFront();
	s3.PopFront();
	cout << s3 << "nullptr" << endl;

	ListNode<char>* pos = s3.Find('b');
	cout << pos << endl;
	s3.Insert(pos, 'f');
	cout << s3 << "nullptr" << endl;
	s3.Erase(pos);
	cout << s3 << "nullptr" << endl;
	s3.PrintSList();
	return 0;
}
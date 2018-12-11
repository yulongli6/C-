#pragma once

#include<iostream>
using namespace std;

namespace bit
{
template<class T>
    struct list_node
{
public:
    list_node(const T& value = T())
        : pre(nullptr)
          , next(nullptr)
          , val(value)
    {}

    list_node<T>* pre;
    list_node<T>* next;
    T val;
};

template<class T>
struct list_iterator
{
    typedef list_iterator<T> self;

    list_iterator(list_node<T>* pNode = nullptr)
        :_pNode(pNode)
    {}

    list_iterator(const self& s)
        :_pNode(s._pNode)
    {}


    T& operator*()
    {
        return _pNode->val;
    }


    T* operator->()
    {
        return (&(operator*()));
    }


    self& operator++()
    {
        _pNode = _pNode->next;
        return *this;
    }

    self operator++(int)
    {
        self stemp(*this);
        _pNode = _pNode->next;

        return stemp;
    }


    self& operator--()
    {
        _pNode = _pNode->pre;
        return *this;
    }

    self operator--(int)
    {
        self stemp(*this);
        _pNode = _pNode->pre;

        return stemp;
    }

    bool operator!=(const self& s)
    {
        return _pNode != s._pNode;
    }



    bool operator ==(const self& s)
    {
        return _pNode == s._pNode;
    }



    list_node<T>* _pNode;
};

template<class T>
class reverse_list_iterator
{
    typedef list_node<T> node;
    typedef node* PNode;
    typedef reverse_list_iterator<T> self;
public:
    reverse_list_iterator(PNode pNode = nullptr)
        :_pNode(pNode)
    {}

    reverse_list_iterator(const self& s)
        :_pNode(s._pNode)
    {}

    T& operator*()
    {
        PNode* pNode = _pNode;
        pNode = pNode->pre;
        return pNode->val;
    }

    T* operator->()
    {
        return &(operator*());
    }

    self& operator++()
    {
        _pNode = _pNode->pre;
        return *this;
    }

    self operator++(int)
    {
        self temp(*this);
        _pNode = _pNode->pre;
        return temp;
    }

    self& operator--()
    {
        _pNode = _pNode->next;
        return *this;
    }

    self operator--(int)
    {
        self temp(*this);
        _pNode = _pNode->next;
        return temp;
    }

    bool operator!=(const self& s)
    {
        return _pNode != s._pNode;
    }


    bool operator==(const self& s)
    {
        return _pNode == s._pNode;
    }
private:
    PNode _pNode;

};

template<class T>
class list
{
    typedef list_node<T> node;
    typedef node* pNode;
public:
    typedef list_iterator<T>  iterator;
    typedef const list_iterator<T>  const_iterator;
    typedef reverse_list_iterator<T> reverse_iterator;
    typedef const reverse_list_iterator<T> const_reverse_iterator;
public:
    list()
    {
        createhead();
        _pHead->next = _pHead->pre = _pHead;
    }

    list(int n, const T& val)
    {
        createhead();
        for(size_t i = 0;i < n; ++i)
            push_back(val);
    }

    template<class Input_iterator>
        list(Input_iterator first, Input_iterator last)
        {
            createhead();
            while(first != last)
                push_back(*first++);
        }

    list(const list<T>& l)
    {
        createhead();
        for(const auto& e : l)
            push_back(e);
    }


    list<T>& operator=(const list<T>& l)
    {

        for(const auto& e : l)
            push_back(e);
    }



    ~list()
    {
        clear();
        delete _pHead;
        _pHead = nullptr;
    }
    /////////////////////////////////////////////////////////////////////
    //iterator
    //
    iterator begin()
    {
        return iterator(_pHead->next);
    }


    const_iterator begin()const
    {
        return iterator(_pHead->next);
    }


    iterator end()
    {
        return iterator(_pHead);
    }


    const_iterator end()const
    {
        return iterator(_pHead);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(_pHead);
    }

    const_reverse_iterator rbegin()const
    {
        return reverse_iterator(_pHead);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(_pHead->next);
    }

    const_reverse_iterator rend()const
    {
        return reverse_iterator(_pHead->next);
    }
    /////////////////////////////////////////////////////////////////////
    //capacity

    size_t size()const
    {
        size_t count = 0;
        pNode cur = _pHead->next;
        while(cur != _pHead)
        {
            count++;
            cur = cur->next;
        }

        return count;
    }


    void resize(size_t n, const T& val = T())
    {
        size_t size = this->size();
        if(n > size)
        {
            for(size_t i = size; i < n; ++i)
                push_back(val);
        }
        else
        {
            for(size_t i = n; i < size; ++i)
                pop_back();
        }
    }

    bool empty()
    {
        return _pHead = _pHead->next;
    }
    //////////////////////////////////////////////////////////////////////
    //acess

    T& front()
    {
        return _pHead->next->val;
    }

    const T& front()const
    {
        return _pHead->next->val;
    }

    T& back()
    {
        return _pHead->pre->val;
    }

    const T& back()const
    {
        return _pHead->pre->val;
    }

    //////////////////////////////////////////////////////////////////////
    //modify
    
    template <class InputIterator>
    void assign ( InputIterator first, InputIterator last)
    {
        clear();
        insert(end(), first, last);
    }
    void assign ( int n, const T& u  )
    {
        clear();
        while(n--)
            push_back(u);
    }

    void push_back(const T& val)
    {
        insert(_pHead, val);
    }

    void pop_back()
    {
        erase(--end());
    }

    void push_front(const T& val)
    {
        insert(begin(), val);
    }

    void pop_front()
    {
        erase(begin());
    }

    iterator insert(iterator position, const T& val)
    {
        pNode pNewNode = new node(val);
        pNode pos = position._pNode;

        pNewNode->next = pos;
        pNewNode->pre = pos->pre;

        pos->pre->next = pNewNode;
        pos->pre = pNewNode;

        return iterator(pNewNode);
    }


    void insert (iterator position, int n, const T& val)
    {
        pNode pNewNode;
        while(n--)
        {

            pNewNode = new node(val);
            pNode pos = position._pNode;

            pNewNode->next = pos;
            pNewNode->pre = pos->pre;

            pos->pre->next = pNewNode;
            pos->pre = pNewNode;
        }


    }
    template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            pNode pNewNode;
            pNode pos = position._pNode;
            InputIterator it;
            for(it = first; it != last; ++it)
            {
                pNewNode = new node(*first++);

                pNewNode->next = pos;
                pNewNode->pre = pos->pre;
                pos->pre->next = pNewNode;
                pos->pre = pNewNode;
            }
        }


    iterator erase(iterator position)
    {
        pNode pos = position._pNode;
        if(_pHead == pos)
            return iterator(_pHead);

        pNode pRet = pos->next;
        pos->pre->next = pos->next;
        pos->next->pre = pos->pre;

        delete pos;
        return iterator(pRet);
    }

    iterator erase(iterator first, iterator last)
    {
        iterator it = first;
        while(it != last)
        {
            iterator temp = it;
            ++it;
            erase(temp);
        }

    }
    void swap(list<T>& l)
    {
        swap(_pHead, l._pHead);

    }
    void clear()
    {
        //头删
        pNode cur = _pHead->next;
        while(cur != _pHead)
        {
            _pHead->next = cur->next;
            delete cur;
            cur = _pHead->next;
        }

        _pHead->next = _pHead->pre = _pHead;
    }
    ////////////////////////////////////////////////////////////////////////
    //Operations
    void splice(iterator position, list<T>& x  )
    {
        pNode pos = position._pNode;
        insert(pos, x.begin(),x.end());
        x.clear();
    }

    void splice(iterator position, list<T>& x, iterator i)
    {
        pNode pos = position._pNode;
        insert(pos, *i);
        x.erase(i);
    }

    void splice(iterator position, list<T>& x, iterator first, iterator last)
    {
        pNode pos = position._pNode;
        insert(pos, first, last);
        x.erase(first, last);
    }


    void remove ( const T& value  )
    {
        list<int>::iterator it = begin();
        while(it != end())
        {
            list<int>::iterator temp = it;
            ++it;
            if(*temp == value)
                erase(temp);

        }
    }


private:
    void createhead()
    {
        _pHead = new node();
        _pHead->next = _pHead->pre = _pHead;
    }
private:
    pNode _pHead;
};
}


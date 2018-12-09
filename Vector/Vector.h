#pragma once
#include <iostream>
using namespace std;
#include<string.h>
namespace bit
{
template<class T>
    class Vector
{
public:
    typedef T* Iterator; 
    typedef const T* const_Iterator;
public:
    Vector()
        : _start(nullptr)
          , _finish(nullptr)
          , _endOfStorage(nullptr)
    {}

    Vector(size_t n, const T& val = T())
        : _start(new T[n])
          , _finish(_start + n)
          , _endOfStorage(_start + n)
    {
        for(size_t i = 0; i < n; ++i)
        {
            _start[i] = val;
        }
    }

    Vector(T* first, T* last)
    {
        size_t size = last - first;
        _start = new T[size];
        memcpy(_start, first, sizeof(T)*size);
        _finish = _endOfStorage = _start + size;

    }

    Vector(const Vector<T>& v)
    {
        size_t size = v._finish - v._start;
        _start = new T[size];
        memcpy(_start, v._start, sizeof(T)*size);
        _finish = _endOfStorage = _start + size;
    }

    Vector<T>& operator=(const Vector<T>& v)
    {
        if(this != &v)
        {
            size_t size = v._finish - v._start;
            size_t _size = _finish - _start;
            if(size > _size)
                Reserve(size);
            memcpy(_start, v._start, sizeof(T)*size);
            _finish = _endOfStorage = _start + size;
        }
        return *this;
    }

    ~Vector()
    {
        if(_start)
        {
            delete[] _start;
            _start = _finish = _endOfStorage = nullptr;
        }
    }
    ///////////////////////////Iterator////////////////////////////
    Iterator begin()
    {
        return _start;
    }

    Iterator end()
    {
        return _finish;
    }

    const_Iterator begin()const
    {
        return _start;
    }

    const_Iterator end()const
    {
        return _finish;
    }
    //////////////////////////acess///////////////////////////////////////
    //
    T& Front()
    {
        return _start[0];
    }

    const T& Front()const
    {
        return _start[0];
    }

    T& Back()
    {
        return *(_finish - 1);
    }

    const T& Back()const
    {
        return *(_finish - 1);
    }

    T& operator[](size_t index)
    {
        return _start[index];
    }

    const T& operator[](size_t index)const
    {
        return _start[index];
    }


    ////////////////////////capacity/////////////////////////////
    //
    size_t Size()
    {
        return _finish - _start;
    }

    size_t Capacity()
    {
        return _endOfStorage - _start;
    }

    void Clear()
    {
        _finish = _start;
    }

    bool Empty()
    {
        return _start = _finish;
    }
    void Resize(size_t n, const T& val = T())
    {
        size_t oldSize = Size();
        if(n < oldSize)
            _finish = _start + n;
        else
        {
            size_t oldCapacity = Capacity();
            if(n > oldCapacity)
                Reserve(n);
            for(size_t i = oldSize; i < n; ++i)
                *_finish++ = val;

        }
    }

    void Reserve(size_t n)
    {
        if(n > Capacity())
        {
            size_t oldSize = Size();
            T* temp = new T[n];
            memcpy(temp, _start, sizeof(T)*oldSize);
            delete[] _start;
            _start = temp;
            _finish = _start + oldSize;
            _endOfStorage = _start + n;
        }
    }
    //////////////////////////////////////moduify////////////////////////////
    //
    //
    void PushBack(const T& data)
    {
        if(Size() == Capacity())
            Reserve(2*Capacity()+3);
        *_finish++ = data;
    }

    void PopBack()
    {
        --_finish;
    }

    Iterator Insert(Iterator pos, const T& data)
    {
        size_t _pos = pos - _start;
        if(_finish == _endOfStorage)
            Reserve(2*Capacity() + 3);
        size_t size = _finish - _start;
        for(size_t i = size -1; i >= _pos; --i )
            _start[i + 1] = _start[i];
        _start[_pos]= data;
        _finish++;
        return begin();
    }

    void Insert(Iterator pos, int n, const T& data)
    {
        size_t _pos = pos - _start;
        size_t size = Size();
        size_t capacity =Capacity();
        if(size + n > capacity)
            Reserve(2 *size + n);
        Vector temp(size - _pos);
        size_t j = 0;
        for(size_t i = _pos; i < size; ++i )
            temp._start[j++] = _start[i];
        for(size_t i = _pos;i <_pos +n; i++)
        {
            _start[i] = data;
        }
        j = 0;
        for(size_t i = _pos + n; i < Capacity(); ++i)
            _start[i] = temp._start[j];
        _finish += n;
    }

    template<class InputIterator>
        void Insert(Iterator pos, InputIterator first, InputIterator last)
        {
            size_t _pos = pos  - _start;
            size_t size = Size();
            size_t capacity = Capacity();
            size_t n = last - first;
            if(size + n > capacity)
                Reserve(2*capacity + n);
            for(size_t i = size -1; i >= _pos; --i )
                _start[i + n] = _start[i];
            for(size_t i = 0;i < n; i++)
            {
                _start[_pos + i] = first[i];
            }
            _start += n;
        }

    Iterator Erase ( Iterator pos)
    {
        size_t _pos = pos - _start;
        size_t size = Size();
        for(size_t i = _pos; i < size; ++i)
        {
            _start[i] = _start[i + 1];
        }
        _finish--;
        return begin();
    }
    Iterator Erase ( Iterator first, Iterator last)
    {
        size_t n = last -first;
        size_t pos = first -_start;
        for(size_t i = pos; i < Size() - n; ++i)
        {
            _start[i] = _start[i + n];
        }

        _finish -= n;
        return begin();
    }
    template <class InputIterator>
        void Assign ( InputIterator first, InputIterator last  )
        {
            size_t n = last - first;
            if(n > Capacity())
                Reserve(n);
            for(size_t i = 0; i < Size(); i++)
            {
                _start[i] = first[i];
            }
            _finish = _start + n;
        }
    void Assign (  int n, const T& u  )
    {
        if(n > Capacity())
            Reserve(n);
        for(size_t i = 0; i < Size(); ++i)
        {
            _start[i] = u;
        }
        _finish = _start + n;

    }



private:
    T* _start;        //_array
    T* _finish;       //_size
    T* _endOfStorage;
};
}

#include<climits>
#include <iostream>
#include<assert.h>
#include<string.h>
using namespace std;


class String
{
public:
    typedef char* Iterator;
    typedef const char* const_Iterator;
    ////////////////////构造对象/////////////////
    //用一个字符串构造对象
    String()
        : _capacity(0)
        , _size(10)
    {
        _str = new char[_capacity + 1];
    }

    String(const char* str)
        :_capacity(strlen(str))
        ,_size(_capacity)
    {
        if(nullptr == str)
            str = " ";
        _str = new char[_size + 1];
        strcpy(_str, str);
    }

    //用一个字符串前n个字符构造对象
    String(const char* str, size_t n)
    {
        assert(str);
        size_t len = strlen(str);
        if(n > len)
            n = len;

        _str = new char[n + 1];
        memcpy(_str, str, n);

        _capacity = n;
        _size = n;
        _str[_size] = '\0';
    }

    String(const String& s, size_t pos, size_t n = npos)
    {
        size_t len = strlen(s._str) - pos;
        if((int)n == -1)
            n = len;
        if(n > len)
            n = len;
        _str = new char[n + 1];

        memcpy(_str, s._str + pos, n);

        _capacity = n;
        _size = n;
        _str[_size] = '\0';
    }

    String(size_t n, char c)
        :_capacity(n)
        ,_size(0)
    {
        _str = new char[_capacity + 1];
        while(_size <= _capacity)
            _str[_size++] = c;
    }
    //拷贝构造函数
    String(const String& s)
        : _str(new char[s._size + 1])
        , _capacity(s._size)
        , _size(s._size)
    {
        strcpy(_str, s._str);
    }
    //运算符重载
    String& operator=(const String& s)
    {
        if(this != &s)
        {
            char* pstr = new char[s._capacity + 1];
            strcpy(pstr, s._str);
            delete[] _str;
            _str = pstr;
            _capacity = s._capacity;
            _size = s._size;
        }

        return *this;
    }


    //析构函数
    ~String()
    {
        if(_str)
        {
            delete[] _str;
            _str = nullptr;
            _capacity = 0;
            _size = 0;
        }
    }
    ////////////////////Iterator//////////////////
    
    Iterator Begin()
    {
        return _str;
    }

    const_Iterator Begin()const
    {
        return _str;
    }
    
    Iterator End()
    {
        return _str + _size;
    }

    const_Iterator End()const
    {
        return _str + _size;
    }

    Iterator rBegin()
    {
        return End();
    }

    Iterator rEnd()
    {
        return Begin();
    }

    ///////////////////Capacity////////////////
    
    size_t Size() const
    {
        return _size;
    }

    size_t Length() const
    {
        return _size;
    }

    size_t Max_Size()const
    {
        string s;
        return s.max_size();
    }
    
    void Resize(size_t n, char c = '0')
    {
        if(n <= _size)
        {
            _size = n;
        }
        else
        {
            if(n > _size)
            {
                char* pstr = new char[2 * n + 1];
                strcpy(pstr, _str);
                delete[] _str;
                _str = pstr;
                _capacity = 2 * n;
            }

            memset(_str+_size,c,n-_size);
            _size = n;
        }
        _str[_size] = '\0';
    }
    
    size_t Capacity()const
    {
        return _capacity;
    }

    void Reserve(size_t res_arg = 0)
    {
        if(res_arg > _capacity)
        {
            char* pstr = new char[res_arg + 1];
            strcpy(pstr, _str);
            
            delete[] _str;
            _str = pstr;
            _capacity = res_arg;
        }
    }
    
    void Clear()
    {
        _size = 0;
        _str[0] = '\0';
    }

    bool Empty()
    {
        return 0 == _size;
    }


///////////////////////////元素访问////////////////////////////

    char& operator[](size_t index)
    {
        assert(index < _size);
        return _str[index];
    }

    const char& operator[](size_t index)const
    {
        assert(index < _size);
        return _str[index];
    }

    /////////////////////运算符重载///////////////////////////
    
    friend ostream& operator<<(ostream& _cout, const String& s)
    {
        _cout << s._str;
        return _cout;
    }

    friend istream& operator>>(istream& _cin, const String& s)
    {
        _cin >> s._str;
        return _cin;
    }
    /////////////////////对象修改操作/////////////////////////
    
    String& operator+=(char c)
    {
        PushBack(c);
        return *this;
    }

    String& operator+=(const String& s)
    {
        if(s._size > _capacity - _size)
            Reserve(s._size + _capacity * 2);
        strcat(_str,s._str);
        _size += s._size;

        return *this;
    }

    String& operator+=(const char* str)
    {
        size_t len = strlen(str);
        if(len > _capacity - _size)
            Reserve(len + _capacity * 2);

        strcat(_str, str);
        _size += len;
        
        return *this;
    }

    void PushBack(char c)
    {
        
        if(_size == _capacity)
            Reserve(_capacity * 1.5);
        _str[_size++] = c;
        _str[_size] = '\0';
    }

    void PopBack()
    {
        _size--;
    }
    
    void Insert(Iterator p, size_t n, char c)
    {
        String temp;
        for(Iterator it = Begin(); it < End(); it++)
        {
            if(it == p)
                while(n--)
                {
                    temp += c;
                }
            else
                temp += *it;
        }
        temp[_size] = '\0';
        *this = temp;
    }

    String& Append(const String& s)
    {
        *this += s;
        return *this;
    }

    String& Append(const String& s, size_t pos, size_t n)
    {
        String pstr = s.Substr(pos,n);
        *this += pstr;
        return *this;
    }

    String& Append(const char* str, size_t n)
    {
        size_t len = strlen(str);
        if(n > len)
            n = len;
        if(n > _capacity - _size)
            Reserve(n + _capacity * 1.5);
        memcpy(_str + _size, str, n);

        _size += n;
        _str[_size] = '\0';
    }

    String& Append(const char* str)
    {
        *this += str;
        return *this;
    }

    String& Append(size_t n, char c)
    {
        while(--n)
            PushBack(c);
        return *this;
    }

    void Swap(String& s)
    {
        swap(_str, s._str);
        swap(_size, s._size);
        swap(_capacity, s._capacity);
    }
//////////////////////字符串操作//////////////////////////////////
    
    
    const char* C_str()const
    {
        return _str;
    }

    size_t Find(const String& s, size_t pos = 0)
    {

    }

    size_t Find(char c, size_t pos = 0)const 
    {
        for(size_t i = pos; i < _size; ++i)
        {
            if(c == _str[i])
                return i;
        }

        return npos;
    }

    String Substr(size_t pos = 0, size_t n = npos)const
    {
        size_t len = strlen(_str + pos);
        if(n > len)
            n = len;
        return String(_str + pos, n);

    }

private:
    char* _str;
    size_t _capacity;
    size_t _size;
    static const size_t npos;
};

const size_t String::npos = -1;


int main()
{
    String s1("hello world ");
    String s2("i love you");
    cout << s1 << endl;
    s1.Insert(s1.Begin()+6,3,'@');
    cout << s1 << endl;
    
    
    cout << s1.Capacity()<<" "<<s1.Size()<<endl;
    String s3(s1, 12);
    cout << s3 << endl;
    cout << s3.Capacity()<<" "<<s3.Size()<<endl;
    return 0;
}

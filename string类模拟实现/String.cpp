#include<climits>
#include<vector>
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
        : _capacity(10)
        , _size(0)
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
        assert(pos < _size);
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
    bool operator>(const String& s)
    {
        if(strcmp(_str, s._str) > 0)
            return true;
        return false;
    }

    bool operator<(const String& s)
    {
        if(strcmp(_str, s._str) < 0)
            return true;
        return false;
    }

    bool operator>=(const String& s)
    {
        if(strcmp(_str, s._str) >= 0)
            return true;
        return false;
    }

    bool operator<=(const String& s)
    {
        if(strcmp(_str, s._str) <= 0)
            return true;
        return false;
    }

    bool operator==(const String& s)
    {
        if(strcmp(_str, s._str) == 0)
            return true;
        return false;
    }

    bool operator!=(const String& s)
    {
        if(strcmp(_str, s._str) != 0)
            return true;
        return false;
    }


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
            {
                while(n--)
                {
                    temp += c;
                }
                temp += *it;
            }
            else
                temp += *it;
        }
        this->Clear();
        *this = temp;
    }

    Iterator Insert ( Iterator p, char c  )
    {
        if(_size +1 == _capacity)
            Reserve(_capacity * 1.5);
        for(Iterator it = End(); it >= p; --it)
        {
            *(it + 1) = *it;
        }
        *p = c;
        return Begin();
    }

    String& Insert(size_t pos1, size_t n, char c)
    {
        String temp;
        for(size_t i = 0; i < _size; ++i)
        {
            if(pos1 == i)
            {
                while(n--)
                {
                    temp += c;
                }
                temp += _str[i];
            }
            else
                temp += _str[i];
        }
            this->Clear();
            *this = temp;
            return *this;
            
    }

    String& Insert(size_t pos1, const char* str)
    {
        String temp;
        for(size_t i = 0; i < _size; ++i)
        {
            if(i == pos1)
            {
                temp += str;
                temp += _str[i];
            }
            else
                temp += _str[i];
        }
        
        return *this = temp;
    }

    String& Insert ( size_t pos1, const char* s, size_t n )
    {
        String temp;
        for(size_t i = 0; i < _size; ++i)
        {
            if(i == pos1)
            {
                size_t j = 0;
                while(n--)
                    temp += s[j++];
                temp += _str[i];
            }
            else
                temp += _str[i];
        }
        return *this = temp;
    }


    String& Insert ( size_t pos1, const String& s  )
    {
        String temp;
        for(size_t i =0; i < _size; ++i)
        {
            if(i == pos1)
            {
                temp += s;
                temp += _str[i];
            }
            else
                temp += _str[i];
        }
        return *this = temp;
    }



    String& Insert ( size_t pos1, const String& s, size_t pos2, size_t n)
    {
        String temp;
        String sub;
        sub = s.Substr(pos2, n);
        for(size_t i =0;i< _size; ++i)
        {
            if(i == pos1)
            {
                temp += sub;
                temp += _str[i];
            }
            else
                temp += _str[i];
        }
        return *this = temp;
    }

    String& Erase ( size_t pos = 0, size_t n = npos  )
    {
        assert(pos < _size);
        if(n > _size - pos)
        {
            n = _size - pos;
            _str[pos] = '\0';
            _size = pos;
            return *this;
        }
        else
        {
            for(size_t i = pos; i <_size - n; ++i)
            {
                _str[i] = _str[i + n];
            }
            _str[_size - n] = '\0'; 
            _size -= n;
            return *this;
        }
    }


    Iterator Erase ( Iterator position  )
    {
        assert(position < End());
        for(Iterator it = position; it < End(); it++)
            *it = *(it + 1);
        _size--;
        return Begin();
    }

    //[first, last]
    Iterator Erase ( Iterator first, Iterator last  )
    {
        assert(first < last);
        size_t n = last - first + 1; 
        for(Iterator it = first;it <= End()- n; it++)
            *it = *(it + n);
        _size -= n;
        return Begin();
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



    String& Assign ( const String& s)
    {
        if(_capacity < s._capacity)
        {
            char* temp = new char[s._capacity + 1];
            strcpy(temp, s._str);
            delete[] _str;
            _str = temp;
            _size = s._size;
            _capacity = s._capacity;
        }
        else
        {
            strcpy(_str, s._str);
            _size = s._size;
        }
        return *this;
    }

    String& Assign ( const String& s, size_t pos, size_t n  )
    {
        String temp = s.Substr(pos, n);
        Assign(temp);
        return *this;
    }

    String& Assign ( const char* s, size_t n  )
    {
        String temp(s);
        temp = temp.Substr(0,n);
        Assign(temp);
        return *this;
    }

    String& Assign ( const char* s  )
    {
        String temp(s);
        Assign(temp);
        return *this;
    }

    String& Assign ( size_t n, char c  )
    {
        Clear();
        while(n--)
        {
            PushBack(c);
        }

        return *this;
    }

    
    String& Replace ( size_t pos1, size_t n1,const String& s)
    {
        Erase(pos1, n1);
        Insert(pos1, s);
        return *this;
    }

    String& Replace(Iterator i1, Iterator i2, const String& s)
    {
        Erase(i1, i2);
        size_t pos = i1 - Begin();
        Insert(pos,s);
        return *this;
    }

    String& Replace (size_t pos1, size_t n1, const String& s, size_t pos2, size_t n2)
    {
        Erase(pos1, n1);
        String temp = s.Substr(pos2, n2);
        Insert(pos1, temp);
        return *this;
    }

    String& Replace (size_t pos1, size_t n1,const char* str, size_t n2)
    {
        Erase(pos1, n1);
        Insert(pos1, str, n2);
        return *this;
    }

    String& Replace (Iterator i1, Iterator i2, const char* str, size_t n2)
    {
        Erase(i1, i2);
        size_t pos = i1 - Begin();
        Insert(pos, str, n2);
        return *this;
    }


    String& Replace (size_t pos1, size_t n1,   const char* str)
    {
        Erase(pos1, n1);
        Insert(pos1,str);
        return *this;
    }
    String& Replace ( Iterator i1, Iterator i2, const char* str)
    {
        Erase(i1, i2);
        size_t pos = i1 - Begin();
        Insert(pos,str);
        return *this;
    }
    String& Replace ( size_t pos1, size_t n1,   size_t n2, char c  )
    {
        Erase(pos1, n1);
        Insert(pos1, n2, c);
        return *this;
    }
    String& Replace ( Iterator i1, Iterator i2, size_t n2, char c  )
    {
        Erase(i1, i2);
        size_t pos = i1 -Begin();
        Insert(pos, n2, c);
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

    const char* Data() const
    {
        return _str;
    }

    size_t Copy(char* s, size_t n, size_t pos = 0)
    {
        assert(pos < _size);
        if(n > _size - pos)
            n = _size - pos;
        size_t j = 0;
        for(size_t i = pos; i < pos + n; ++i)
            s[j++] = _str[i];
        return n;
    }

    
    size_t Find ( const String& s, size_t pos = 0  ) const
    {
        assert(pos < _size);
        if(char* index = strstr(_str+pos, s._str))
            return index - Begin();
        return npos;
            
    }
    size_t Find( const char* str, size_t pos, size_t n  ) const
    {
        assert(pos < _size);
        if(n > strlen(str))
            n = strlen(str);
        String temp(str);
        temp = temp.Substr(0,n);
        if(char* index = strstr(_str+pos, temp._str))
            return index - Begin();
        return npos;
    }
    size_t Find ( const char* s, size_t pos = 0  ) const
    {
        
        assert(pos < _size);
        if(char* index = strstr(_str+pos, s))
            return index - Begin();
        return npos;
            
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

    size_t Rfind ( const String& s, size_t pos = npos  ) const;
    size_t Rfind ( const char* str, size_t pos, size_t n  ) const;
    size_t Rfind ( const char* str, size_t pos = npos  ) const;

    size_t Rfind ( char c, size_t pos = npos  ) const
    {
        if(pos > _size -1)
            pos = _size -1;
        for(int i = pos; i >= 0; --i)
        {
            if(_str[i] == c)
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

    int Compare ( const String& s  ) const
    {
        const_Iterator it1 = Begin(); 
        const_Iterator it2 = s.Begin();
        while(*it1 == *it2 && *it1&&*it2)
        {
            if(*it1 == '\0' || *it2 == '\0')
                return 0;
            it1++;
            it2++;
        }
        if(*it1 > *it2)
            return 1;
        if(*it1 < *it2)
            return -1;
    }
    int Compare ( const char* s  ) const
    {
        return strcmp(_str, s);
    }
    int Compare ( size_t pos1, size_t n1, const String& s  ) const
    {
        String temp = Substr(pos1, n1);
        return strcmp(temp._str,s._str);
    }
    int Compare ( size_t pos1, size_t n1, const char* s ) const
    {

        String temp = Substr(pos1, n1);
        return strcmp(temp._str,s);
    }
    int Compare ( size_t pos1, size_t n1, const String& s, size_t pos2, size_t n2  ) const
    {
        String temp1 = Substr(pos1, n1);
        String temp2 = s.Substr(pos2, n2);
        return strcmp(temp1._str, temp2._str);
    }
    int Compare ( size_t pos1, size_t n1, const char* s, size_t n2 ) const
    {
        String temp1 = Substr(pos1, n1);
        String temp2(s, n2);
        return strcmp(temp1._str, temp2._str);
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
    String s1("hello world i love you");
    String s2("hello");
    cout << s2.Compare(0,5,"hello world", 5)<<endl;
    
    return 0;

}

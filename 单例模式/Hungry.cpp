/*恶汉模式--单例模式*/
#include<iostream>
using namespace std;

class Singleton
{
public:
    static Singleton& GetInstance()
    {
        return _ps;
    }
private:
    Singleton(){};
    Singleton(const Singleton& s) = delete;
    Singleton& operator=(Singleton const&);
    static Singleton _ps ;
};

Singleton Singleton::_ps;

int main()
{
    cout << &Singleton::GetInstance() << endl;
    cout << &Singleton::GetInstance() << endl;
    return 0;
}

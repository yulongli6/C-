/*
 *单例模式---单例模式---懒汉模式式
 */
#include<mutex>
#include<thread>
#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton* GetInstance()
    {
        if(nullptr == _ps){
            _mutex.lock();
            if(nullptr == _ps){
                _ps = new Singleton();
                cout << "test" << endl;
            }
            _mutex.unlock();
        }
        return _ps;
    }

public:
    class GC
    {
    public:
        ~GC(){
            if(nullptr != _ps){
                delete _ps;
                _ps = nullptr;
            }
        }
    };
private:
    Singleton(){};
    Singleton(const Singleton&);
    static Singleton* volatile  _ps;
    static mutex _mutex;
    static GC _gc;
};

Singleton* volatile Singleton::_ps = nullptr;
mutex Singleton::_mutex;
Singleton::GC _gc;

void Func()
{
    Singleton::GetInstance();
}

int main()
{
    thread t1(Func,10);
    thread t2(Func,10);
    t1.join();
    t2.join();
    return 0;
}


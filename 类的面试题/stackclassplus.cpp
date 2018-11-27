#include <iostream>
using namespace std;

class Test
{
public:
    Test(int data)
        :_data(data)
    {
        cout << "Test():"<<this<<endl;
    }
private:
    void* operator new(size_t);
private:
    int _data;
};

Test t(1);//还可以在全局变量区创建，不太满足只能在栈上创建对象。

int main()
{
    return 0;
}


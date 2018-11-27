#include<iostream>
using namespace std;

class Test
{
public:
    static Test CreateInstance(int date)
    {
        return Test(date);
    }
    ~Test()
    {
        cout << "~Test():" << this << endl;
    }
private:
    Test(int date)
        :_date(date)
    {
        cout << "Test():" << this <<endl;
    }
private:
    int _date;
};

int main()
{
    Test t(Test::CreateInstance(10));
    return 0;
}

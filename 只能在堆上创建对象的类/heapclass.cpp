#include <iostream>
using namespace std;

class Test
{
public:
    static Test* CreateInstance(int date)
    {
        return new Test(date);
    }
private:
    Test(int date)
        :_date(date)
    {
        cout << "Test():" << this << endl;
    }
    Test(const Test& t);/*c++98*/
    //Test(const Test& t) = delete;/*c++11*/
private:
    int _date;
};
int main()
{
    Test* pt; 
    pt = Test::CreateInstance(10);
    delete pt;
    return 0;
}


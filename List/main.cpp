#include <iostream>
#include<list>
using namespace std;
#include"List.h"

template<class T>
void PrintList(const bit::list<T>& l)
{
    for(const auto e : l)
        cout << e << " ";
    cout << endl;
}

int main()
{
    bit::list<int> l1;
    //bit::list<int> l2(10, 5);
    //PrintList(l2);

    list<int> l{1,2,3,4,5};

    bit::list<int> l3(l.begin(),l.end());
    PrintList(l3);
    return 0;
}


#include <iostream>
#include<vector>
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
    bit::list<int> l2(10, 5);
    PrintList(l2);

    vector<int> v{1,2,3,4,5,6};
    bit::list<int> l1(v.begin(), v.end());
    PrintList(l1);

    bit::list<int>::iterator it = l1.begin();
    bit::list<int>::iterator it1 = l1.begin();
    int n = 3;
    while(n--)
        ++it;
    n = 5;
    while(n--)
        ++it1;
    l2.splice(l2.end(), l1);
    PrintList(l2);
    l2.remove(5);
    PrintList(l2);
    return 0;
}


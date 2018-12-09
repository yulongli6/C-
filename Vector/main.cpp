#include<iostream>
using namespace std;
#include"Vector.h"
template<class T>
void PrintVector(bit::Vector<T>& v)
{
    for(auto e : v)
        cout << e << " ";
    cout << endl;
}



int main()
{
    string s("asdf");
    bit::Vector<int> v1(10, 5);
    bit::Vector<int> v2(5, 4);
    PrintVector(v1); 
    PrintVector(v2); 

    v1.Assign((size_t)2 , 100);
    PrintVector(v1); 
    v1.Insert(v1.begin(), 10, 5); 
    PrintVector(v1); 
    cout << v1.Capacity()<< " " << v1.Size()<<endl;
    cout << v2.Capacity()<< " " << v2.Size()<<endl;
    return 0;
}

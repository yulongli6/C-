#define _CRT_SECURE_NO_DEPRECATE 1
#include<iostream>
using namespace std;

#if 0
int Add(int a = 10, int b = 10, int c = 10)
{
	return a + b + c;
}


int main()
{
	cout << Add() << endl;
	cout << Add(1) << endl;
	cout << Add(1, 2) << endl;
	cout << Add(1, 2, 3) << endl;
	return 0;
}
#endif


#include<stdio.h>
namespace N1
{
	int  a = 20;
	int  Add(int left, int right)
	{
		return left + right;
	}
}
using namespace N1;
int main()
{
	printf("%d\n", a);    //想打印出20
	printf("%d\n", N1::a);//想打印出20
	Add(1, 2);
	return 0;
}

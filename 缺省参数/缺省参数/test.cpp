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

#if 0
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

int& Add(int a, int b)
{
	int c = a + b;
	return c;
}
int main()
{
	int ret = Add(1, 2);
	Add(3, 4);
	cout << "Add(1, 2) is :" << ret << endl;
	return 0;
}

#include <time.h>
struct A
{
	int a[100000];
};
void TestFunc1(A* a)
{}
void TestFunc2(A& a)
{}
void TestRefAndPtr()
{
	A a;
	// 以指针作为函数参数
	size_t begin1 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc1(&a);
	size_t end1 = clock();
	// 以引用作为函数参数
	size_t begin2 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc2(a);
	size_t end2 = clock();
	// 分别计算两个函数运行结束后的时间
	cout << "TestFunc1(int*)-time:" << end1 - begin1 << endl;
	cout << "TestFunc2(int&)-time:" << end2 - begin2 << endl;
}
// 运行多次，检测指针和引用在传参方面的效率区别
int main()
{
	for (int i = 0; i < 10; ++i)
	{
		TestRefAndPtr();
	}

	return 0;
}
#endif
#include <time.h>
struct A
{
	int a[100000];
};
A a;
A* TestFunc1()
{
	return &a;
}
A& TestFunc2()
{
	return a;
}
void TestReturnByRefPtr()
{
	// 以指针作为函数的返回值类型
	size_t begin1 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// 以引用作为函数的返回值类型
	size_t begin2 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// 计算两个函数运算完成之后的时间
	cout << "TestFunc1 time:" << end1 - begin1 << endl;
	cout << "TestFunc2 time:" << end2 - begin2 << endl;
}
// 测试运行10次，指针和引用作为返回值效率方面的区别
int main()
{
	for (int i = 0; i < 10; ++i)
		TestReturnByRefPtr();
	return 0;
}
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
	printf("%d\n", a);    //���ӡ��20
	printf("%d\n", N1::a);//���ӡ��20
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
	// ��ָ����Ϊ��������
	size_t begin1 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc1(&a);
	size_t end1 = clock();
	// ��������Ϊ��������
	size_t begin2 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc2(a);
	size_t end2 = clock();
	// �ֱ���������������н������ʱ��
	cout << "TestFunc1(int*)-time:" << end1 - begin1 << endl;
	cout << "TestFunc2(int&)-time:" << end2 - begin2 << endl;
}
// ���ж�Σ����ָ��������ڴ��η����Ч������
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
	// ��ָ����Ϊ�����ķ���ֵ����
	size_t begin1 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// ��������Ϊ�����ķ���ֵ����
	size_t begin2 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// �������������������֮���ʱ��
	cout << "TestFunc1 time:" << end1 - begin1 << endl;
	cout << "TestFunc2 time:" << end2 - begin2 << endl;
}
// ��������10�Σ�ָ���������Ϊ����ֵЧ�ʷ��������
int main()
{
	for (int i = 0; i < 10; ++i)
		TestReturnByRefPtr();
	return 0;
}
#define _CRT_SECURE_NO_DEPRECATE 1

#include<iostream>
using namespace std;


int main()
{
	string s1(100,'h');
	string s2(s1);
	cout << s1.capacity() << endl;
	cout << s2.capacity() << endl;
	cout << s1.size() << endl;
	cout << s2.size() << endl;

	string s3("hello");
	s3.push_back('a');
	s3.swap(s2);
	return 0;
}
#pragma once
#include<iostream>
using namespace std;
class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
	friend istream& operator>>(istream& _cin, Date& d);
public:
	//构造函数
	Date(int year = 2000, int month = 2, int day = 25);
	//拷贝构造函数
	Date(const Date& d);
	//赋值运算符重载
	Date& operator=(const Date& d);
	//判断是否为闰年
	bool IsLeapYear()const;
	//运算符重载
	Date operator+(int days);//日期+天数
	Date operator-(int days);//日期-天数
	int operator-(const Date& d);//日期-日期
	Date& operator++();//前置++
	Date operator++(int);//后置++
	Date& operator--();//前置--
	Date operator--(int);//后置--
	bool operator>(const Date& d)const;//比较日期大小
	bool operator>=(const Date& d)const;//
	bool operator<(const Date& d)const;//
	bool operator<=(const Date& d)const;//
	bool operator==(const Date& d)const;//
	bool operator!=(const Date& d)const;//
private:
	int _year;
	int _month;
	int _day;
};
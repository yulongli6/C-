#pragma once
#include<iostream>
using namespace std;
class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
	friend istream& operator>>(istream& _cin, Date& d);
public:
	//���캯��
	Date(int year = 2000, int month = 2, int day = 25);
	//�������캯��
	Date(const Date& d);
	//��ֵ���������
	Date& operator=(const Date& d);
	//�ж��Ƿ�Ϊ����
	bool IsLeapYear()const;
	//���������
	Date operator+(int days);//����+����
	Date operator-(int days);//����-����
	int operator-(const Date& d);//����-����
	Date& operator++();//ǰ��++
	Date operator++(int);//����++
	Date& operator--();//ǰ��--
	Date operator--(int);//����--
	bool operator>(const Date& d)const;//�Ƚ����ڴ�С
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
#define _CRT_SECURE_NO_DEPRECATE 1

#include "Date.h"
#include "assert.h"

Date::Date(int year, int month, int day) 
	:_year(year),
	 _month(month),
     _day(day)
{
	_year = year;
	_month = month;
	_day = day;
}

Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}


bool _IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
		return true;
	}
	return false;
}

bool Date::IsLeapYear()const
{
	return _IsLeapYear(this->_year);
}

int _GetDayOfMonth(int year, int month)
{
	assert(month > 0 && month < 13);
	static int array[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (_IsLeapYear(year) && month == 2){
		return array[month] + 1;
	}
	else return array[month];
}


ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

istream& operator>>(istream& _cin, Date& d)
{
	_cin >> (d._year);
	_cin >> d._month;
	_cin >> d._day;

	return _cin;
}


Date& Date::operator=(const Date& d)
{
	if (this != &d){
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}


bool Date::operator==(const Date& d)const
{
	return this->_year == d._year
		&& this->_month == d._month
		&& this->_day == d._day;
}

bool Date::operator!=(const Date& d)const
{
	return !(*this == d);
	
}

bool Date::operator>(const Date& d)const
{
	if ((this->_year > d._year)
		|| (this->_year == d._year && this->_month > d._month)
		|| (this->_year == d._year && this->_month == d._month && this->_day > d._day)){
		return true;
	}
	else return false;

}

bool Date::operator>=(const Date& d)const
{
	return operator>(d) || operator==(d);
}

bool Date::operator<(const Date& d)const
{
	if ((this->_year < d._year)
		|| (this->_year == d._year && this->_month < d._month)
		|| (this->_year == d._year && this->_month == d._month && this->_day < d._day)){
		return true;
	}
	else return false;
}

bool Date::operator<=(const Date& d)const
{
	return operator<(d) || operator==(d);
}

Date Date::operator+(int days)
{
	if (days < 0){
		return *this - (0 - days);
	}
	Date ret = *this;
	ret._day += days;
	while (ret._day > _GetDayOfMonth(ret._year, ret._month)){
		ret._day -= _GetDayOfMonth(ret._year, ret._month);
		ret._month++;
		if (ret._month > 12){
			ret._year++;
			ret._month = 1;
		}
	}
	return ret;
}

Date Date::operator-(int days)
{
	if (days < 0){
		return *this +(0 - days);
	}
	Date ret = *this;
	ret._day -= days;
	while (ret._day < 0){
		ret._day += _GetDayOfMonth(ret._year, ret._month);
		ret._month--;
		if (ret._month < 1){
			ret._year--;
			ret._month = 12;
		}
	}
	return ret;
}


int Date::operator-(const Date& d)
{
	Date minDate(*this);
	Date maxDate(d);
	if (minDate > maxDate){
		swap(minDate, maxDate);
	}
	int count = 0; 
	while (minDate != maxDate){
		count++;
		++minDate;
	}
	return count;
	/*int ret = 0;
	Date A = d;
	if (*this > d){
		while (!(this->_year == A._year
			&& this->_month == A._month
			&& this->_day == A._day)){
			A._day++;
			ret++;
			if (A._day > _GetDayOfMonth(A._year, A._month)){
				A._month++;
				A._day = 1;
				if (A._month > 12){
					A._year++;
					A._month = 1;
				}
			}
		}
	}
	else{
		while (!(this->_year == A._year
			&& this->_month == A._month
			&& this->_day == A._day)){
			A._day--;
			ret--;
			if (A._day < 1){
				A._month--;
				if (A._month < 1){
					A._year--;
					A._month = 12;
				}
				A._day = _GetDayOfMonth(A._year, A._month);
			}
		}
	}
	return ret;*/
}

Date& Date::operator++()
{
	*this = *this + 1;
	/*this->_day++;
	if (this->_day > 
		_GetDayOfMonth(this->_year, this->_month)){
		this->_month++;
		if (this->_month > 12){
			this->_year++;
			this->_month = 1;
		}
		this->_day = 1;
	}*/
	return *this;
}

Date Date::operator++(int)
{
	Date ret = *this;
	/*this->_day++;
	if (this->_day >
		_GetDayOfMonth(this->_year, this->_month)){
		this->_month++;
		if (this->_month > 12){
			this->_year++;
			this->_month = 1;
		}
		this->_day = 1;
	}*/
	++*this;
	return ret;
}

Date& Date::operator--()
{
	*this = *this - 1;
	/*this->_day--;
	if (this->_day < 1){
		this->_month--;
		this->_day = _GetDayOfMonth(this->_year, this->_month);
		if (this->_month < 1){
			this->_year--;
			this->_month = 12;
		}
	}*/
	return *this;
}

Date Date::operator--(int)
{
	Date ret = *this;
	/*this->_day--;
	if (this->_day < 1){
		this->_month--;
		this->_day = _GetDayOfMonth(this->_year, this->_month);
		if (this->_month < 1){
			this->_year--;
			this->_month = 12;
		}
	}*/
	--*this;
	return ret;
}
/*
 *  DateTime.cpp
 *
 *  COSC 052 Summer 2014
 *  Project #3
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on: JUL 29, 2914
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#include <iostream>
#include "DateTime.h"

/*****************************************************
 *                                                   *
 *         class Date implementation details         *
 *                                                   *
 *****************************************************/

istream& operator>>(istream &input, Date &d) {
	char ch1, ch2;
	string remainder;
	
	input >> setw(2) >> d.dd >> ch1 >> setw(2) >> d.mm
	>> ch2 >> setw(4) >> d.yyyy;
	
	return input;
}

ostream& operator<<(ostream &output, const Date &d) {
	output << setfill('0') << setw(4) << d.yyyy << "-" << setw(2)
	<< d.mm << "-" << setw(2) << d.dd;
	
	return output;
}

Date::Date(int year, int month, int day) {
#ifdef DEBUG_DATE
	cout << "Entered constructor Date::Date(int, int, int)" << endl;
#endif
	
	setDate(year, month, day);
	
#ifdef DEBUG_DATE
	cout << "Date is " << setfill('0') << setw(4) << yyyy << "-"
	<< setw(2) << mm << "-" << setw(2) << dd << endl;
	cout << "Exiting constructor Date::Date(int, int, int)" << endl;
#endif
}

Date::Date(const Date &d) {
#ifdef DEBUG_DATE
	cout << "Entered constructor Date::Date(const Date&)" << endl;
#endif
	
	setDate(d);
	
#ifdef DEBUG_DATE
	cout << "Date is " << setfill('0') << setw(4) << yyyy << "-"
	<< setw(2) << mm << "-" << setw(2) << dd << endl;
	cout << "Exiting constructor Date::Date(const Date&)" << endl;
#endif
}

void Date::setDate(int year, int month, int day) {
  yyyy = year;
	
  if (yyyy <= 6) {
    yyyy = yyyy + 2000;
  }
  else if (yyyy >= 28 && yyyy <= 99) {
    yyyy = yyyy + 1900;
  }
  else {
  }
	
  mm = month;
  dd = day;
}

void Date::setDate(const Date &d) {
  yyyy = d.yyyy;
	
  if (yyyy <= 6) {
    yyyy = yyyy + 2000;
  }
  else if (yyyy >= 28 && yyyy <= 99) {
    yyyy = yyyy + 1900;
  }
  else {
  }
	
  mm = d.mm;
  dd = d.dd;
}

bool Date::operator==(const Date &rhsObj) const {
	if (yyyy == rhsObj.getYear() && mm == rhsObj.getMonth()
			&& dd == rhsObj.getDay()) {
		return true;
	}
	else {
		return false;
	}
}

bool Date::operator!=(const Date &rhsObj) const {
	return !(*this == rhsObj);
}

bool Date::operator<=(const Date &rhsObj) const {
  return !(rhsObj < *this);
}

bool Date::operator<(const Date &rhsObj) const {
  if ((yyyy < rhsObj.getYear() ||
			(mm < rhsObj.getMonth() && yyyy == rhsObj.getYear())) ||
			(dd < rhsObj.getDay() && mm == rhsObj.getMonth()
			 && yyyy == rhsObj.getYear())) {
		return true;
	}
  else {
    return false;
  }
}


bool Date::operator>=(const Date &rhsObj) const {
	return !(*this < rhsObj);
}

bool Date::operator>(const Date &rhsObj) const {
	return rhsObj < *this;
}

const Date& Date::operator=(const Date &rhsObj) {
	// Not a self assignment, OK to proceed
  if(this != &rhsObj) {
    yyyy = rhsObj.getYear();
    mm = rhsObj.getMonth();
    dd = rhsObj.getDay();
  }
	
  return rhsObj;
} // END class Date implementation

/*****************************************************
 *                                                   *
 *         class Time implementation details         *
 *                                                   *
 *****************************************************/

std::istream& operator>>(std::istream &input, Time &t) {
	char ch;
	input >> setw(2) >> t.hh >> ch >> setw(2)
	>> t.mm;
	
	return input;
}

std::ostream& operator<<(std::ostream &output, const Time &t) {
	output << setfill('0') << setw(2) << t.hh << ":" << setw(2)
	<< t.mm;
	
	return output;
}

Time::Time(int hour, int minute) {
#ifdef DEBUG_DATE
	cout << "Entered constructor Time::Time(int, int, int)" << endl;
#endif
	
	setTime(hour, minute);
	
#ifdef DEBUG_DATE
	cout << "Exiting constructor Time::Time(int, int)" << endl;
#endif
}

void Time::setTime(int hour, int minute) {
	hh = hour;
	mm = minute;
}

const Time& Time::operator=(const Time &rhsObj) {
	// Not a self assignment, okay to proceed
	if (this != &rhsObj) {
		hh = rhsObj.hh;
		mm = rhsObj.mm;
	}
	
	return rhsObj;
} // END class Time implementation
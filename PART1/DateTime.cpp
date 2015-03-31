/*
 *  DateTime.cpp
 *
 *  COSC 052 Summer 2014
 *  Project #1
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on:  JUL 14, 2014
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#include <iostream>
#include <iomanip>
#include "DateTime.h"

/*****************************************************
 *                                                   *
 *       class Date implementation details           *
 *                                                   *
 *****************************************************/

std::istream& operator>>(std::istream &input, Date &d) {
  char ch1, ch2;
  std::string remainder;

  // Extract data and store corresponding values into yyyy, mm and dd
  // Read in and discard delimiting characters
  input >> std::setw(2) >> d.dd >> ch1 >> std::setw(2) >> d.mm >> ch2
	>> std::setw(4) >> d.yyyy;

  return input;
}

std::ostream& operator<<(std::ostream &output, const Date &d) {
  output << std::setfill('0') << std::setw(4) << d.yyyy << "-"
	 << std::setw(2) << d.mm << "-" << std::setw(2) << d.dd;

  return output;
}

Date::Date(int year, int month, int day) {
#ifdef DEBUG_DATE
  std::cout << "Entered constructor Date::Date(int, int, int)" << std::endl;
#endif

  setDate(year, month, day);

#ifdef DEBUG_DATE
  std::cout << "Date is " << std::setfill('0') << std::setw(4) << yyyy << "-"
	    << std::setw(2) << mm << "-" << std::setw(2) << dd << std::endl;
  std::cout << "Exiting constructor Date::Date(int, int, int)" << std::endl;
#endif
}

Date::Date(const Date &d) {
#ifdef DEBUG_DATE
  std::cout << "Entered constructor Date::Date(const Date&)" << std::endl;
#endif

  setDate(d);

#ifdef DEBUG_DATE
  std::cout << "Date is " << std::setfill('0') << std::setw(4) << yyyy << "-"
	    << std::setw(2) << mm << "-" << std::setw(2) << dd << std::endl;
  std::cout << "Exiting constructor Date::Date(const Date&)" << std::endl;
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
    yyyy = yyyy;
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
    yyyy = yyyy;
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
  if ((yyyy < rhsObj.getYear() || mm < rhsObj.getMonth()
      && yyyy == rhsObj.getYear()) || (dd < rhsObj.getDay()
				       && mm == rhsObj.getMonth()
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
  if(this != &rhsObj) {
    // Not a self assignment, OK to proceed
    yyyy = rhsObj.getYear();
    mm = rhsObj.getMonth();
    dd = rhsObj.getDay();
  }
  return rhsObj;
}

/*****************************************************
 *                                                   *
 *       class Time implementation details           *
 *                                                   *
 *****************************************************/

std::istream& operator>>(std::istream &input, Time &t) {
  char ch;

  input >> std::setw(2) >> t.hh; // Extract the hours and store them in data
                                 // member hh
  input >> ch;                   // Extract and discard the delimiting
                                 // character
  input >> std::setw(2) >> t.mm; // Extract the minutes and store them in data
                                 // member mm

  return input;
}

std::ostream& operator<<(std::ostream &output, const Time &t) {
  output << std::setfill('0');
  output << std::setw(2) << t.hh << ":";
  output << std::setw(2) << t.mm;

  return output;
}

Time::Time(int hour, int minute) {
#ifdef DEBUG_DATE
  std::cout << "Entered constructor Time::Time(int, int, int)" << std::endl;
#endif

  setTime(hour, minute);
    
#ifdef DEBUG_DATE
  std::cout << "Exiting constructor Time::Time(int, int)" << std::endl;
#endif
}

void Time::setTime(int hour, int minute) {
  hh = hour;
  mm = minute;
}

const Time& Time::operator=(const Time &rhsObj) {
  if (this != &rhsObj) {
      // Not a self assignment, OK to proceed
      hh = rhsObj.hh;
      mm = rhsObj.mm;
    }
    
  return rhsObj;
}

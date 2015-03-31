/*
 *  DateTime.h
 *
 *  COSC 052 Summer 2014
 *  Project #3
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on: JUL 29, 2014
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#ifndef COSC0525Summer2014P3_Date_h
#define COSC0525Summer2014P3_Date_h

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setfill;
using std::string;
using std::ifstream;
using std::ostream;
using std::istream;

//#define DEBUG_DATE = 1

class Date {
	friend istream& operator>>(istream&, Date&);
	friend ostream& operator<<(ostream&, const Date&);
private:
	int mm;				// Two digit integer for the month
	int dd;				// Two digit integer for the day
	int yyyy;			// Four digit integer for the year
public:
	Date(int = 1821, int = 7, int = 13);		// Default constructor
	Date(const Date&);											// Copy constructor
	
	// Setters to set Date members to values passed in
	void setDate(int, int, int);
	void setDate(const Date&);
	
	// In-line getters to return Date members
	int getDay() const { return dd; }
	int getMonth() const { return mm; }
	int getYear() const { return yyyy; }
	
	// Overloaded operators
	bool operator==(const Date&) const;
	bool operator!=(const Date&) const;
	bool operator<=(const Date&) const;
	bool operator<(const Date&) const;
	bool operator>=(const Date&) const;
	bool operator>(const Date&) const;
	
	// Overloaded assignment operator
	const Date& operator=(const Date&);
};// END class Date

class Time {
	friend istream& operator>>(istream&, Time&);
	friend ostream& operator<<(ostream&, const Time&);
private:
	int hh;				// Two digit integer for hour of day
	int mm;				// Two digit integer for minute of day
public:
	Time(int = 0, int = 0);									// Default constructor

	// Setter to set Time members to values passed in
	void setTime(int, int);

	// In-line getters to return Time members
	int getHour() const { return hh; }
	int getMinute() const { return mm; }

	// Overloaded assignment operator
	const Time& operator=(const Time&);
}; // END class Time
#endif
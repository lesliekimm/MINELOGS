/*
 *  DateTime.h
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

#ifndef COSC52Summer2014P1_Date_h
#define COSC52Summer2014P1_Date_h

#include <iostream>
#include <iomanip>

//#define DEBUG_DATE = 1

class Date {
  friend std::istream& operator>>(std::istream &, Date &);
  // Overloaded stream extraction operator.
  // Postcondition: Extracts values for each data member from
  // the input stream. Format of the data in the stream
  // is assumed to be: dd:mm:yy
  // The delimiting characters are read and discarded.
  // The dash is read and discared.

  friend std::ostream& operator<<(std::ostream &, const Date &);
  // Overloaded stream insertion operator.
  // Postcondition: The date is output to the stream. Delimiting
  // characters are replaced and the dash is added
  // between the year, month and day sections. The result
  // is a date value output in the format yyyy-mm-dd.

private:
  int mm;            // Two digit integer for the month.
  int dd;            // Two digit integer for the day.
  int yyyy;          // Four digit integer for the year.

public:
  Date(int = 1821, int = 7, int = 13);
  // Constructor with parameters, with default values.
  // This constructor calls member function setDate()
  // and passes the same arguments as were passed in to
  // the constructor, function setDate() updates the data members.
  // Postcondition: Sets the values of mm, dd and yyyy
  // according to the values of the arguments passed in.
  // If no values are passed, this acts as the default constructor
  // and year is set to 1821, month is set to 07 and day is set to 13.

  Date(const Date&);
  // Constructor with reference parameter
  // This constructor calls the setDate(const Date&) function
  // using a refrence parameter to update the data members.
  // Postconditon: Sets the values of mm, dd and yyyy
  // according to the values of the Date object passed in.

  void setDate(int, int, int);
  // Function sets the value of the object data members,
  // can be called directly or by a constructor.
  // Postcondition: Data members are set to the values
  // of the respective arguments passed in.

  void setDate(const Date&);
  // Function sets the value of the object data members,
  // can be called directly or by a constructor.
  // Postcondition: Data members are set to the values
  // of the respective arguments passed in.

  int getDay() const {
    return dd;
  }
  // In-line function to return the day value.
  // Postcondition: The value of the data member dd is returned.

  int getMonth() const {
    return mm;
  }
  // In-line function to return the month value.
  // Postcondition: The value of the data member mm is returned.

  int getYear() const {
    return yyyy;
  }
  // In-line function to return the year value.
  // Postcondition: The value of the year value yyyy is returned.

  bool operator==(const Date&) const;
  // Overloaded assignment operator
  // Postcondition: Compares whether left Date object is equal
  // to the right Date object

  bool operator!=(const Date&) const;
  // Overloaded assignment operator
  // Postcondition: Compares whether left Date object does not
  // equal the right Date object

  bool operator<=(const Date&) const;
  // Overloaded assignment operator
  // Postcondition: Compares whether left Date object is before or
  // the same date as the right Date object

  bool operator<(const Date&) const;
  // Overloaded assignment operator
  // Postcondition: Compares if left Date object is before the
  // right Date object

  bool operator>=(const Date&) const;
  // Overloaded assignment operator
  // Postcondition: Compares if left Date object is the same date
  // or after the right Date object

  bool operator>(const Date&) const;
  // Overloaded assignment operator
  // Postcondition: Compares if left Date object is after the
  // right Date object

  const Date& operator=(const Date&);
  // Overloaded assignment operator
  // Postcondition: The values of right Date object's
  // data members are copied to the respective data
  // members of the left Date object.

}; // END class Date

class Time {
  friend std::istream& operator>>(std::istream &, Time &);
  // Overloaded stream extraction operator.
  // Postcondition: Extracts values for each data member from
  // the input stream. Format of the data in the stream
  // is assumed to be: hh:mm:ss.sssZ
  // The delimiting characters are read and discarded.
  // The decimal point is read and discarded. The fractional
  // seconds are stored as an integer.

  friend std::ostream& operator<<(std::ostream &, const Time &);
  // Overloaded stream insertion operator.
  // Postcondition: The time is output to the steam. Delimiting
  // characters are replaced and the decimal point is added
  // between the seconds and fraction sections. The result
  // is a time value output in the same format as was read in.

private:
  int hh;     // Two digit integer for hour of day
  int mm;     // Two digit integer for minute of day

public:
  Time(int = 0, int = 0);
  // Constructor with parameters, with default values
  // This constructor calls the member function setTime()
  // and passes the same arguments as were passed in to
  // the constructor, function setTime() updates the data members.
  // Postcondition: Sets the values of hh and mm
  // according to the values of the arguments passed in.
  // If no values are passed, this acts as the default constructor
  // all integer data members are set to zero.

  void setTime(int, int);
  // Function to set the values of the object data members,
  // can be called directly or by a constructor.
  // Postcondition: Data members are set to the values
  // of the respective arguments passed in.

  int getHour() const {
    return hh;
  }
  // In-line function to return the hour value.
  // Postcondtion: The value of data member hh is retured.

  int getMinute() const {
    return mm;
  }
  // In-line function to return the minute value.
  // Postcondtion: The value of data member mm is retured.

  const Time& operator=(const Time&);
  // Overloaded assignment operator.
  // Postcondtion: The values of right hand side object's
  // data members are copied to the respective data
  // members of the left hand side object.
}; // END class Time

#endif

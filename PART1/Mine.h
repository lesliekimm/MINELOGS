/*
 *  mine.h
 *
 *  COSC 052 Summer 2014
 *  Project #2
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on: JUL 22, 2014
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#ifndef COSC052Summer2014P02v01_mine_h
#define COSC052Summer2014P02v01_mine_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include "DateTime.h"

//#define DEBUG_FILE_OPENING

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::istream;
using std::cin;
using std::vector;

const int FIELD_COUNT = 18;
const int FIELD_SIZE[FIELD_COUNT] = {6, 41, 30, 30, 50, 63, 12, 23, 2, 2, 25, 9,
				     7, 11, 20, 10, 31, 1};

enum {MINE_ID, MINE_NAME, CONTACT_TITLE, NEAREST_TOWN, BUSINESS_NAME, STREET,
      PO_BOX, CITY, STATE_ABBR, FIPS_CODE, STATE_NAME, ZIP_CODE, POSTAL_CODE,
      MINE_TYPE_CODE, MINE_STATUS, MINE_STATUS_DATE, MINE_SIC_CODE,
      MINE_COAL_METAL_IND};

/***************************************************************************
 *                                                                         *
 *                     struct FIPS_stateCode definition                    *
 *                                                                         *
 ***************************************************************************/

struct FIPS_stateCode {
  friend std::istream& operator>>(std::istream&, FIPS_stateCode&);
    
  string numericCode;
  string alphaCode;
  string stateName;
    
  FIPS_stateCode(string= "", string = "", string = "");
  FIPS_stateCode(FIPS_stateCode &);
  ~FIPS_stateCode();
    
  // Overloaded assignment operator
  const FIPS_stateCode& operator=(const FIPS_stateCode&);
};

/***************************************************************************
 *                                                                         *
 *                   class FIPS_stateReference definition                  *
 *                                                                         *
 ***************************************************************************/

class FIPS_stateReference {
  friend std:: ostream& operator<<(ostream&, const FIPS_stateReference&);
    
private:
  FIPS_stateCode *FIPSstateCodeList;
  int codeCount;
public:
  FIPS_stateReference();
  FIPS_stateReference(ifstream&);
  ~FIPS_stateReference();
    
  string getNumericCode(string) const;
  string getAlphaCode(string) const;
  string getStateName(string) const;
  void loadFipsFile(std::ifstream&);
  FIPS_stateCode* getFipsCodePointer(string) const;
  int getCodeCount() const;
};

/***************************************************************************
 *                                                                         *
 *                       struct MineRecord definition                      *
 *                                                                         *
 ***************************************************************************/

struct MineRecord {
  string dataField[FIELD_COUNT];
    
  // Date adjusted to our Date class format
  Date adjustedDate;
    
  // Pointer to FIPS code object
  FIPS_stateCode *fipsPtr;
    
  // Default constructor
  MineRecord(const FIPS_stateReference&, string = "");
};

/***************************************************************************
 *                                                                         *
 *                          class Mine definition                          *
 *                                                                         *
 ***************************************************************************/

class Mine {
private:
  string mineID;
  string mineName;
  string nearestTown;
  string mineStatus;
  Date mineStatusDate;
  FIPS_stateCode* addressFipsCode;
  string addressZipCode;
public:
  // Default constructor
  Mine(string = "", string = "", string = "", string = "",
       Date = Date(1864, 1, 1), FIPS_stateCode* = NULL, string = "");
  // Destructor
  ~Mine();
    
  string getMineID() const { return mineID; }
  string getMineName() const { return mineName; }
  string getNearestTown() const { return nearestTown; }
  string getMineStatus() const { return mineStatus; }
  Date getStatusDate() const { return mineStatusDate; }
  FIPS_stateCode* getAddressFipsCode() const { return addressFipsCode; }
  string getAddressZip() const { return addressZipCode; }
  
  // Prints executive report of mine record
  void execReport1() const;
}; // END class Mine defition

/***************************************************************************
 *                                                                         *
 *                     class AbandonedMine definition                      *
 *                                                                         *
 ***************************************************************************/

class AbandonedMine : public Mine {
public:
  // Default constructor
  AbandonedMine();
  // Convert constructor
  AbandonedMine(MineRecord&);
  // Destructor
  ~AbandonedMine();
}; // END class AbandonedMine definition

/***************************************************************************
 *                                                                         *
 *                      class WorkingMine definition                       *
 *                                                                         *
 ***************************************************************************/

class WorkingMine : public Mine {
private:
  string contactTitle;
  string businessName;
  string addressStreet;
  string addressCity;
  string primarySicCode;
  char flagMetalCoal;
public:
  // Default constructor
  WorkingMine();
  // Convert constructor
  WorkingMine(MineRecord&);
  // Destructor
  ~WorkingMine();
    
  string getContactTitle() const { return contactTitle; }
  string getBusinessName() const { return businessName; }
  string getAddressStreet() const { return addressStreet; }
  string getAddressCity() const { return addressCity; }
  string getPrimarySicCode() const { return primarySicCode; }
  char getFlagMetalCoal() const { return flagMetalCoal; }
  
  // Prints out executive report of working mines
  void execReport1() const;
};
#endif

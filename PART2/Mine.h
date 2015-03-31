/*
 *  Mine.h
 *
 *  COSC 052 Summer 2014
 *  Project #3
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on: JUL 29, 2014
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assisstance on this project.
 */

#ifndef COSC052Summer2014P3_mine_h
#define COSC052Summer2014P3_mine_h

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "DateTime.h"

//#define DEBUG_FILE_OPENING

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ostream;
using std::istream;

const int FIELD_COUNT = 18;
const int FIELD_SIZE[FIELD_COUNT] = {6, 41, 30, 30, 50, 63, 12,
	23, 2, 2, 25, 9, 7, 11, 20, 10, 31, 1};
enum {MINE_ID, MINE_NAME, CONTACT_TITLE, NEAREST_TOWN, BUSINESS_NAME,
	STREET, PO_BOX, CITY, STATE_ABBR, FIPS_CODE, STATE_NAME, ZIP_CODE,
	POSTAL_CODE, MINE_TYPE_CODE, MINE_STATUS, MINE_STATUS_DATE,
	MINE_SIC_CODE, MINE_COAL_METAL_IND};

/***************************************************************************
 *                                                                         *
 *                    struct FIPS_stateCode definition                     *
 *                                                                         *
 ***************************************************************************/

struct FIPS_stateCode {
	friend istream& operator>>(istream&, FIPS_stateCode&);
	
	string numericCode;
	string alphaCode;
	string stateName;
	
	FIPS_stateCode(string = "", string = "", string = "");	// Default constructor
	FIPS_stateCode(FIPS_stateCode &);												// Copy constructor
	~FIPS_stateCode();																			// Destructor
	
	// Overloaded assignment operator
	const FIPS_stateCode& operator=(const FIPS_stateCode&);
}; // END struct FIPS_stateCode definition

/***************************************************************************
 *                                                                         *
 *                  class FIPS_stateReference definition                   *
 *                                                                         *
 ***************************************************************************/

class FIPS_stateReference {
	friend ostream& operator<<(ostream&, const FIPS_stateReference&);
	
private:
	FIPS_stateCode *FIPSstateCodeList;
	int codeCount;
public:
	FIPS_stateReference();					// Default constructor
	FIPS_stateReference(ifstream&);	// Convert constructor
	~FIPS_stateReference();					// Destructor
	
	string getNumericCode(string) const;
	string getAlphaCode(string) const;
	string getStateName(string) const;
	void loadFipsFile(ifstream&);
	FIPS_stateCode* getFipsCodePointer(string) const;
	int getCodeCode() const { return codeCount; }
}; // END class FIPS_stateReference definition

/***************************************************************************
 *                                                                         *
 *                      struct MineRecord definition                       *
 *                                                                         *
 ***************************************************************************/

struct MineRecord {
	string dataField[FIELD_COUNT];
	Date adjustedDate;							// Date adjusted to our Date class format
	FIPS_stateCode *fipsPtr;				// Pointer to FIPS code object

	MineRecord();																					// Default constructor
	MineRecord(const FIPS_stateReference&, string = "");	// Default constructor
}; // END struct MineRecord definition

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
	Mine (string = "", string = "", string = "", string = "",
				Date = Date(1864, 1, 1), FIPS_stateCode* = NULL, string = "");
	// Destructor
	~Mine();
	
	string getMineID() const { return mineID; }
	string getMineName() const {return mineName; }
	string getNearestTown() const { return nearestTown; }
	string getMineStatus() const { return mineStatus; }
	Date getStatusDate() const { return mineStatusDate; }
	FIPS_stateCode* getAddressFipsCode() const { return addressFipsCode; }
	string getAddressZip() const { return addressZipCode; }
	virtual void execReport1() const;
}; // END class Mine definition

/***************************************************************************
 *                                                                         *
 *                     class AbandonedMine definition                      *
 *                                                                         *
 ***************************************************************************/

class AbandonedMine : public Mine {
public:
	AbandonedMine();								// Default constructor
	AbandonedMine(MineRecord&);			// Convert constructor
	~AbandonedMine();								// Destructor
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
	WorkingMine();									// Default constructor
	WorkingMine(MineRecord&);				// Convert constructor
	~WorkingMine();									// Destructor
	
	string getContactTitle() const { return contactTitle; }
	string getBusinessName() const { return businessName; }
	string getAddressStreet() const { return addressStreet; }
	string getAddressCity() const { return addressCity; }
	string getPrimarySicCode() const { return primarySicCode; }
	char getFlagMetalCoal() const { return flagMetalCoal; }
	virtual void execReport1() const;
}; // END class WorkingMine definition
#endif
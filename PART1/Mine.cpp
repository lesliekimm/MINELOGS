/*
 *  mine.cpp
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
 *  Honor Code, I certify that, with the exceptions of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#include <iostream>
#include <iomanip>
#include "Mine.h"

//#define DEBUG_ABANDONED = 1
//#define DEBUG_WORKING = 1
//#define DEBUG_MINE = 1

/****************************************************************************
 **                                                                        **
 **                  struct FIPS_stateCode implementation                  **
 **                                                                        **
 ****************************************************************************/

std::istream& operator>>(std::istream &is, FIPS_stateCode &rhsObj) {
  is >> rhsObj.numericCode >> rhsObj.alphaCode;
  getline(is, rhsObj.stateName);
    
  return is;
}

FIPS_stateCode::FIPS_stateCode(string nCode, string aCode, string sName) :
numericCode(nCode), alphaCode(aCode), stateName(sName) {
#ifdef DEBUG_FILE_OPENING
  cout << "Entered constructor FIPS_stateCode::FIPS_stateCode, numericCode = "
       << this->numericCode << endl;
#endif
}

FIPS_stateCode::FIPS_stateCode(FIPS_stateCode &otherObj) {
#ifdef DEBUG_FILE_OPENING
  cout << "Entered copy constructor FIPS_stateCode::FIPS_staeCode, "
       << "numericCode = " << otherObj.numericCode << endl;
#endif
    
  this->alphaCode = otherObj.alphaCode;
  this->numericCode = otherObj.numericCode;
  this->stateName = otherObj.stateName;
} // END FIPS_stateCode copy constructor


FIPS_stateCode::~FIPS_stateCode() {
#ifdef DEBUG_FILE_OPENING
  cout << "Entered destructor FIPS_stateCode::~FIPS_stateCode, numericCode = "
       << this->numericCode << endl;
#endif
} // END FIPS_stateCode desructor

const FIPS_stateCode& FIPS_stateCode::operator=(const FIPS_stateCode &otherObj) {
#ifdef DEBUG_FILE_OPENING
  cout << "Entered overloaded operator FIPS_stateCode::operator=, "
       << "otherObj.numericCode=" << otherObj.numericCode << endl;
#endif
    
  if (this != &otherObj) {
    // Not self assignment, OK to continue
    this->alphaCode = otherObj.alphaCode;
    this->numericCode = otherObj.numericCode;
    this->stateName = otherObj.stateName;
  }
    
  return *this;
}

/****************************************************************************
 **                                                                        **
 **                  struct FIPS_stateCode implementation                  **
 **                                                                        **
 ****************************************************************************/

std::ostream& operator<<(std::ostream &os, const FIPS_stateReference &rhsObj) {
  for (int c = 0; c < rhsObj.codeCount; c++) {
    os << "File entry " << c + 1 << " at address"
       << rhsObj.getFipsCodePointer(rhsObj.FIPSstateCodeList[c].numericCode)
       << ": "  << rhsObj.FIPSstateCodeList[c].numericCode << " "
       << rhsObj.FIPSstateCodeList[c].alphaCode << " "
       << rhsObj.FIPSstateCodeList[c].stateName << endl;
  }
  
  return os;
}

FIPS_stateReference::FIPS_stateReference() {
  // Default constructor, not much to do without more info
  codeCount = 0;
}

FIPS_stateReference::FIPS_stateReference(ifstream &inFile) {
  loadFipsFile(inFile);
} // END constructor FIPS_stateReference::FIPS_stateReference(ifstream &)

FIPS_stateReference::~FIPS_stateReference() {
  // Deallocate any memory that was dynamically allocated
  if (codeCount > 0) {
    delete [] FIPSstateCodeList;
  }
}

string FIPS_stateReference::getNumericCode(string stateAbbreviation) const {
  string returnCode = "";
  bool foundCode = false;
  
  for (int c = 0; c < codeCount && !foundCode; c++) {
    if (FIPSstateCodeList[c].alphaCode == stateAbbreviation) {
      returnCode = FIPSstateCodeList[c].numericCode;
      foundCode = true;
    }
  }
  
  return returnCode;
}

string FIPS_stateReference::getAlphaCode(string fipsNumberCode) const {
  string returnCode = "";
  bool foundCode = false;
  
  for (int c = 0; c < codeCount && !foundCode; c++) {
    if(FIPSstateCodeList[c].numericCode == fipsNumberCode) {
      returnCode = FIPSstateCodeList[c].alphaCode;
      foundCode = true;
    }
  }
    
  return returnCode;
}

string FIPS_stateReference::getStateName(string fipsNumberCode) const {
  string returnCode = "";
  bool foundCode = false;
  
  for (int c = 0; c < codeCount && !foundCode; c++) {
    if (FIPSstateCodeList[c].numericCode == fipsNumberCode) {
      returnCode = FIPSstateCodeList[c].stateName;
    }
  }
  
  return returnCode;
}

void FIPS_stateReference::loadFipsFile(std::ifstream &inFile) {
  try{
    int listSize = 0;
    string fileComment;
        
    if (!inFile) {
      inFile.close();
      string fileStreamError;
      fileStreamError += "ERROR: Error processing file in FIPS_stateReference";
      fileStreamError += "::loadFipsFile.\n";
            
      throw fileStreamError;
    }
    
    inFile >> listSize;
    getline(inFile, fileComment);
    listSize++; // Account for dummy record we are going to add
    
    codeCount = listSize;
    int fileRecords = 0;
    
    FIPSstateCodeList = new FIPS_stateCode[listSize];
        
#ifdef DEBUG_FILE_OPENING
    cout << "Just allocated " << sizeof(FIPSstateCodeList) << " memory for "
	 << "dynamic array of FIPS code objects." << endl;
#endif
        
    FIPS_stateCode nextCode;
    
    // Make first record dummy code to use when data is missing
    nextCode.numericCode = "??";
    nextCode.alphaCode = "??";
    nextCode.stateName = "Missing";
    FIPSstateCodeList[0] = nextCode;
    
    fileRecords++;
    
    while (inFile >> nextCode) {
#ifdef DEBUG_FILE_OPENING
      cout << "Loading FIPS code object number " << fileRecords << endl;
#endif
      if (fileRecords < codeCount + 1) {
	FIPSstateCodeList[fileRecords] = nextCode;
      }
      
      fileRecords++;
    }
    
    if (fileRecords != codeCount) {
      // Something is wrong, should have some error processing
      cout << "ERROR: Inside function FIPS_stateReference::FIPS_stateReference()"
	   << endl << "Read " << fileRecords << " number of file records"
	   << endl << "but function call said to expect " << listSize
	   << " records." << endl;
    }
        
    codeCount = fileRecords;
    inFile.close();
  }
  catch (string e) {
    cout << "ERROR: Fatal error in constructor FIPS_stateReference::"
	 << "FIPS_stateReference";
    throw;
  }
  catch (std::bad_alloc baErr) {
    cout << "ERROR: FIPS_stateReference::FIPS_stateReference() unable to "
	 << "allocate memory\n";
    cout << baErr.what() << endl;
    throw;
  }
}


FIPS_stateCode* FIPS_stateReference::getFipsCodePointer(string fipsNumberCode) const {
  FIPS_stateCode* returnCode = NULL;
  bool foundCode = false;
    
  for (int c = 0; c < codeCount && !foundCode; c++) {
    if (FIPSstateCodeList[c].numericCode == fipsNumberCode) {
      returnCode = &FIPSstateCodeList[c];
      foundCode = true;
    }
  }
  
  return returnCode;
}

int FIPS_stateReference::getCodeCount() const {
  return codeCount;
}

/****************************************************************************
 **                                                                        **
 **                    struct MineRecord implementation                    **
 **                                                                        **
 ****************************************************************************/

MineRecord::MineRecord(const FIPS_stateReference &fipsLookUp, string oneLine) {
  try {
    int onLineColumn = 0;
    
    for (int f = 0; f < FIELD_COUNT; f++) {
      // Clear contents of next data field
      dataField[f] = "";
      
      for (int c = 0; c < FIELD_SIZE[f]; c++) {
	// Advance to next character in input line
	onLineColumn++;
	dataField[f] += oneLine[onLineColumn];
      }
      
      // Advance over the spaces between columns
      onLineColumn += 4;
    }
    
    // Correct the date formate and store value to use in adjustedDate data
    // member
    // Date format from file is dd/mm/yyyy
    // Date format for calls to our Date class functions is yyyy, mm, dd
    // See Gaddis p. 8-8 for atoi functions and Gaddis p. 818-820 for
    // substr and other string functions
    adjustedDate.setDate(atoi((dataField[MINE_STATUS_DATE].substr(6, 4)).c_str()),
			 atoi((dataField[MINE_STATUS_DATE].substr(3, 2)).c_str()),
			 atoi((dataField[MINE_STATUS_DATE].substr(0, 2)).c_str()));
        
    if (fipsLookUp.getCodeCount() <= 0) {
      string fipsLkUpError = "ERROR: FIPS Lookup Table appears to be empty, ";
      fipsLkUpError += "FIPS looup table\n";
      fipsLkUpError += "is required to instantiate mineRecord struct object.\n";
      throw fipsLkUpError;
    }
    
#ifdef DEBUG_FILE_OPENING
    cout << "Inside MineRecord constructor, searching for pointer to object "
	 << "matching code: " << dataField[FIPS_CODE] << endl;
#endif

    fipsPtr = fipsLookUp.getFipsCodePointer(dataField[FIPS_CODE]);
    if (fipsPtr == NULL) {
      fipsPtr = fipsLookUp.getFipsCodePointer("??");
    }
#ifdef DEBUG_FILE_OPENING
    cout << "Pointer value returned was: " << fipsPtr << endl
	 << "Points to object with name = " << fipsPtr->stateName << endl;
#endif
  }
  catch (string mineRecConstErr) {
    cout << "ERROR: Error in constructor MineRecord::MineRecord()" << endl
	 << mineRecConstErr << endl;
    throw;
  }
  catch(...) {
    cout << "ERROR: Catch-all exception in constructor MineRecord::MineRecord()"
	 << endl;
    throw;
  }
} // END constructor MineRecord::MineRecord(const FIPS_stateReference, string)

/****************************************************************************
 **                                                                        **
 **                        class Mine implementation                       **
 **                                                                        **
 ****************************************************************************/

Mine::Mine(string mID, string mName, string nTown, string mStatus, Date mDate,
           FIPS_stateCode* aFipsCode, string aZip) : mineID(mID),
						     mineName(mName),
						     nearestTown(nTown),
						     mineStatus(mStatus),
						     mineStatusDate(mDate),
						     addressFipsCode(aFipsCode),
						     addressZipCode(aZip) {
#ifdef DEBUG_MINE
  cout << "Entered constructor Mine::Mine()" << endl;
#endif
}

Mine::~Mine() {
#ifdef DEBUG_MINE
  cout << "Entered destructor Mine::~Mine()" << endl;
#endif
}

void Mine::execReport1() const {
  cout << mineID << " " << mineName << endl << mineStatusDate << " "
       << mineStatus << endl;
}

/****************************************************************************
 **                                                                        **
 **                   class AbandonedMine implementation                   **
 **                                                                        **
 ****************************************************************************/

AbandonedMine::AbandonedMine() {
#ifdef DEBUG_ABANDONED
  cout << "Entered constructor AbandonedMine::AbandonedMine()" << endl;
#endif
    
  Mine::execReport1();
}

AbandonedMine::AbandonedMine(MineRecord &m) : Mine(m.dataField[MINE_ID],
						   m.dataField[MINE_NAME],
						   m.dataField[NEAREST_TOWN],
						   m.dataField[MINE_STATUS],
						   m.adjustedDate,
						   m.fipsPtr,
						   m.dataField[ZIP_CODE]) {
#ifdef DEBUG_ABANDONED
  cout << "Entered convert constructor AbandonedMine::AbandonedMine"
       << "(MineRecord &m)" << endl;
#endif
}

AbandonedMine::~AbandonedMine() {
#ifdef DEBUG_ABANDONED
  cout << "Entered destructor AbandonedMine::~AbandonedMine()" << endl;
#endif
}

/****************************************************************************
 **                                                                        **
 **                    class WorkingMine implementation                    **
 **                                                                        **
 ****************************************************************************/

WorkingMine::WorkingMine() {
#ifdef DEBUG_WORKING
  cout << "Entered constructor WorkingMine::WorkingMine()" << endl;
#endif

  contactTitle = "";
  businessName = "";
  addressStreet = "";
  addressCity = "";
  primarySicCode = "";
  flagMetalCoal = ' ';
}

WorkingMine::WorkingMine(MineRecord &m) : Mine(m.dataField[MINE_ID],
					       m.dataField[MINE_NAME],
					       m.dataField[NEAREST_TOWN],
					       m.dataField[MINE_STATUS],
					       m.adjustedDate,
					       m.fipsPtr,
					       m.dataField[ZIP_CODE]) {
#ifdef DEBUG_WORKING
  cout << "Entered conver constructor WorkingMine::WorkingMine(MineRecord &m)"
       << endl;
#endif
        
  contactTitle = m.dataField[CONTACT_TITLE];
  businessName = m.dataField[BUSINESS_NAME];
  addressStreet = m.dataField[STREET];
  addressCity = m.dataField[CITY];
  primarySicCode = m.dataField[MINE_SIC_CODE];
  flagMetalCoal = (m.dataField[MINE_COAL_METAL_IND].c_str())[0];
}

WorkingMine::~WorkingMine() {
#ifdef DEBUG_WORKING
  cout << "Entered destructor WorkingMine::~WorkingMine()" << endl;
#endif
}

void WorkingMine::execReport1() const {
  cout << getMineID() << " " << getMineName() << endl << getStatusDate() << " "
       << getMineStatus() << endl << businessName << endl << addressStreet
       << endl << addressCity << ",  " << getAddressFipsCode()->stateName
       << " " << getAddressZip() << endl << primarySicCode << endl;
}

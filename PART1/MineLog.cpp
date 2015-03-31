/*
 *  MineLog.cpp
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
 *  Honor Code, I certify that, with the exceptin of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#include <iostream>
#include "MineLog.h"

MineLog::MineLog(ifstream &inFileMineData, ifstream &inFileFIPS) {
#ifdef DEBUG_MINE
  cout << "Entered MineLog::MineLog(ifsream &, ifstream&)" << endl;
#endif
    
  string oneLine = "";
  string garbage = "";
    
  fipsLookUpTable.loadFipsFile(inFileFIPS); // Create FIPS table
    
  try {
    getline(inFileMineData, garbage);

    if (garbage == "") {
      throw NoData();
    }

    while (getline(inFileMineData, oneLine)) {
      MineRecord mr1(fipsLookUpTable, oneLine); // Store lines from FIPS table
      rawFileData.push_back(mr1);
    }
    
    for (int i = 0; i < rawFileData.size(); i++) {
      if (rawFileData.at(i).dataField[MINE_STATUS].substr(0, 9) == "Abandoned") {
	AbandonedMine a1(rawFileData.at(i));
	abandoned.push_back(a1);
      }
      else {
	WorkingMine w1(rawFileData.at(i));
	working.push_back(w1);
      }
    }
  }
  catch (NoData) {
    cout << "ERROR: There is no data in the file." << endl;
    throw;
  }
  catch (RawData) {
    cout << "ERROR: There was an error reading in raw data file." << endl;
    throw;
  }
  catch (...) {
    cout << "ERROR: Catch-all exception in MineLog::MineLog(ifstream &, ifstream &)"
	 << endl;
    throw;
  }
}

MineLog::~MineLog() {
#ifdef DEBUG_MINE
  cout << "Entered destructor MineLog::~MineLog()" << endl;
#endif
}

void MineLog::displayExecReport1() const {
  cout << "Abandoned Mines:" << endl;
  for (int a = 0; a < abandoned.size(); a++) {
    abandoned.at(a).execReport1();
    cout << endl;
  }
  cout << "Working Mines:" << endl;
  for (int a = 0; a < working.size(); a++) {
    working.at(a).execReport1();
    cout << endl;
  }
}

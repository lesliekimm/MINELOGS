/*
 *  MineLog.cpp
 *
 *  COSC 052 Summer 2014
 *  Project #4
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on: AUG 06, 2014
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exceptin of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#include <iostream>
#include "MineLog.h"

/****************************************************************************
 *                                                                          *
 *                      class MineLog implementation                        *
 *                                                                          *
 ****************************************************************************/

MineLog::MineLog(ifstream &inFileMineData, ifstream &inFileFIPS) {
#ifdef DEBUG_MINE
  cout << "Entered MineLog::MineLog(ifstream&, ifstream&)" << endl;
#endif
  
  try {
    fipsLookUpTable.loadFipsFile(inFileFIPS);
    
    int recordCount = 0;
    int allCount = 0;
    int recordsAccordingToFile = 0;
    string oneLine = "";
    string commentsToIgnore = "";
    string testMe = "";
    
    if (!inFileMineData) {
      cout << "ERROR: Error with input file stream.";
      throw "ERROR: Input file stream error.";
    }
    
    inFileMineData >> recordsAccordingToFile;
    getline(inFileMineData, commentsToIgnore);
    
    if (commentsToIgnore == "") {
      cout << "ERROR: No data in input file stream.";
      throw NoData();
    }
    
    while (getline(inFileMineData, oneLine)) {
      recordCount++;
      MineRecord mr1(fipsLookUpTable, oneLine);// Stores lines from FIPS table
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
    
    for (int i = 0; i < rawFileData.size(); i++) {
      allCount++;
      if (rawFileData.at(i).dataField[MINE_STATUS].substr(0, 9) == "Abandoned") {
	AbandonedMine *a1 = new AbandonedMine(rawFileData.at(i));
	allMines.push_back(a1);
      }
      else {
	WorkingMine *w1 = new WorkingMine(rawFileData.at(i));
	allMines.push_back(w1);
      }
    }
  }
  catch (string a) {
    cout << a << endl;
    cout << "ERROR: Program cannot continue. Goodbye." << endl;
    throw;
  }
  catch (NoData) {
    cout << "ERROR: There is no data in the file. Goodbye." << endl;
    throw;
  }
  catch (...) {
    cout << "ERROR: Catch-all excpetion in MineLog::MineLog()"<< endl
	 << "Unspecified fatal error. Godobye." << endl;
    throw;
  }
  
}

MineLog::~MineLog() {
#ifdef DEBUG_MINE
  cout << "Entered destructor MineLog::~MineLog()" << endl;
#endif
  
  for (int i = 0; i < allMines.size(); i++) {
    delete allMines.at(i);
  }
  
#ifdef DEBUG_MINE
  cout << "Exiting destructor MineLog::~MineLog()" << endl;
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
  
  cout << "All Mines:" << endl;
  for (int a = 0; a < allMines.size(); a++) {
    allMines.at(a)->execReport1();
    cout << endl;
  }
}

void MineLog::sortLL(int listToSort, int sortAlgorithm) {
  int list = listToSort;
  int algorithm = sortAlgorithm;
  
  if (list == ABANDONED && algorithm == BUBBLE_SORT) {
    abandoned.bubbleSort();
  }
  else if (list == ABANDONED && algorithm == SELECTION_SORT) {
    abandoned.selectionSort();
  }
  else if (list == WORKING && algorithm == BUBBLE_SORT) {
    working.bubbleSort();
  }
  else if (list == WORKING && algorithm == SELECTION_SORT) {
    working.selectionSort();
  }
  else {
    throw "ERROR: Incorrect input for list to sort or sorting algorithm.";
  }
}

int MineLog::searchLL(int listToSearch, int searchAlgorithm, string searchTerm) {
  int list = listToSearch;
  int algorithm = searchAlgorithm;
  string term = searchTerm;
  
  if (list == ABANDONED && algorithm == LINEAR_SEARCH) {
    return abandoned.linearSearch(term);
  }
  else if (list == ABANDONED && algorithm == BINARY_SEARCH) {
    return abandoned.binarySearch(term);
  }
  else if (list == WORKING && algorithm == LINEAR_SEARCH) {
    return working.linearSearch(term);
  }
  else if (list == WORKING && algorithm == BINARY_SEARCH) {
    return working.binarySearch(term);
  }
  else {
    throw "ERROR: Incorrect input for list to sort or searching algorithm.";
  }
}

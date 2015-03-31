/*
 *  LK584P4.cpp
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
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */


#include <iostream>
#include <string>
#include <fstream>
#include "DateTime.h"
#include "Mine.h"
#include "MineLog.h"
using namespace std;

class NoCommandLine {};
class NoCLOne {};
class NoCLTwo {};

int main(int argc, const char *argv[]) {
  string inFileMineData;
  string inFIPSData;
  ifstream inputMine;
  ifstream inputFIPS;

  try {
    if (argc < 3) {
      throw NoCommandLine();
    }
    
    inFileMineData = argv[1];
    inFIPSData = argv[2];
    
    inputMine.open(inFileMineData.c_str());
    if (!inputMine) {
      inputMine.close();
      throw NoCLOne();
    }
    
    inputFIPS.open(inFIPSData.c_str());
    if (!inputFIPS) {
      inputFIPS.close();
      throw NoCLTwo();
    }
    
    // Create and display MineLog instance
    MineLog ML1(inputMine, inputFIPS);
    ProcessTimer stopWatch;
    
    ML1.displayExecReport1();
    
    cout << "Peforming searches. Index of -1 indicates the\n";
    cout << "object was not found.\n\n";

    // Commented out both sorts for shorter run time
    // but both can be tested below
    
    /*
      // Perform bubble sort on abandoned
      cout << "Starting bubble sort of abandoned list:\n";
      stopWatch.setTimeStart(clock());
      ML1.sortLL(ABANDONED, BUBBLE_SORT);
      stopWatch.setTimeEnd(clock());
      cout << stopWatch;*/

    // Search for "0100198" using linear search in abandoned
    cout << "Searching for 100198 in abandoned list using\n";
    cout << "linear search:\n";
    stopWatch.setTimeStart(clock());
    cout << "Index of first match: ";
    // I used string "0100198" as the target b/c I figured out
    // how to fix the mineID length bug
    cout << ML1.searchLL(ABANDONED, LINEAR_SEARCH, "0100198") << endl;
    stopWatch.setTimeEnd(clock());
    cout << stopWatch;
    
    // Search for "406499" using linear search in abandoned
    cout << "Searching for 406499 in abandoned list using\n";
    cout << "linear search:\n";
    stopWatch.setTimeStart(clock());
    cout << "Index of first match: ";
    cout << ML1.searchLL(ABANDONED, LINEAR_SEARCH, "406499") << endl;
    stopWatch.setTimeEnd(clock());
    cout << stopWatch;

    /*
      // Perform selection sort on abandoned
      cout << "Starting the selection sort of abandoned list:\n";
      stopWatch.setTimeStart(clock());
      ML1.sortLL(ABANDONED, SELECTION_SORT);
      stopWatch.setTimeEnd(clock());
      cout << stopWatch;*/
    
    // Search for "0100198" using binary search in abandoned
    cout << "Searching for 100198 in abandoned list using\n";
    cout << "binary search:\n";
    stopWatch.setTimeStart(clock());
    cout << "Index of first match: ";
    // I used string "0100198" as the target b/c I figured out
    // how to fix the mineID length bug
    cout << ML1.searchLL(ABANDONED, BINARY_SEARCH, "0100198") << endl;
    stopWatch.setTimeEnd(clock());
    cout << stopWatch;
    
    // Search for "406499" using bubble search in abandoned
    cout << "Searching for 406499 in abandoned list using\n";
    cout << "binary search:\n";
    stopWatch.setTimeStart(clock());
    cout << "Index of first match: ";
    cout << ML1.searchLL(ABANDONED, BINARY_SEARCH, "406499") << endl;
    stopWatch.setTimeEnd(clock());
    cout << stopWatch;
    
  }
  catch (string e) {
    cout << e << endl;
  }
  catch (NoCommandLine) {
    cout << "ERROR: There were not enough command line arguments." << endl;
  }
  catch (NoCLOne) {
    cout << "ERROR: Input file of mine data did not open properly." << endl;
  }
  catch (NoCLTwo) {
    cout << "ERROR: Input file of FIPS data did not open properly." << endl;
  }
  catch (...) {
    cout << "ERROR: Catch-all exception in main()." << endl;
  }
  
  inputMine.close();
  inputFIPS.close();
  
  return 0;
}

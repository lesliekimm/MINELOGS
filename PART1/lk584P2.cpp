/*
 * LK584P2.cpp
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
 *  given nor received any assitance on this project.
 */

#include <iostream>
#include <string>
#include <fstream>
#include "Mine.h"
#include "MineLog.h"

using namespace std;

class NoCommandLine {};
class NoCLOne {};
class NoCLTwo{};

int main( int argc, const char *argv[]) {
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
      
      MineLog ML1(inputMine, inputFIPS);
      ML1.displayExecReport1();
  }
  catch (NoCommandLine) {
    cout << "ERROR: There were not enough command line arguments." << endl;
    throw;
  }
  catch (NoCLOne) {
    cout << "ERROR: Input file of mine data did not open properly." << endl;
    throw;
  }
  catch (NoCLTwo) {
    cout << "ERROR: Input file of FIPS data did not open properly." << endl;
    throw;
  }
  catch (...) {
    cout << "ERROR: Catch-all exception in main()." << endl;
    throw;
  }
  
  inputMine.close();
  inputFIPS.close();
    
  return 0;
}

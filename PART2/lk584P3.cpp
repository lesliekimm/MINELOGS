/*
 *  LK584P3.cpp
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
        
        // cout << "Instantiation of MineLog" << endl;
        MineLog ML1(inputMine, inputFIPS);
        
        // cout << "Created MineLog instance.\n";
        // cout << "Now calling displayExecReport1()" << endl;
        ML1.displayExecReport1();
        
        // cout << "Finished displaying exec report." << endl;
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
/*
 *  MineLog.h
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

#ifndef COSC052Summer2014P02v01_MineLog_h
#define COSC052Summer2014P02v01_MineLog_h

#include "Mine.h"

//#define DEBUG_MINE = 1

class NoData {};
class RawData {};
class AbandonedData {};
class WorkingData {};

class MineLog {
private:
  vector<MineRecord> rawFileData;
  vector<AbandonedMine> abandoned;
  vector<WorkingMine> working;
  FIPS_stateReference fipsLookUpTable;
public:
  // Constructor
  MineLog(ifstream&, ifstream&);
  // Destructor
  ~MineLog();
  
  // Prints out executive report
  void displayExecReport1() const;
}; // END class MineLog definition
#endif

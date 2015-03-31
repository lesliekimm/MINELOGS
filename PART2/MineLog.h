/*
 *  MineLog.h
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

#ifndef COSC052Summer2014P3_MineLog_h
#define COSC052Summer2014P3_MineLog_h

#include "Mine.h"
#include "LL.h"

//#define DEBUG_MINE = 1

class NoData {};

/****************************************************************************
 *                                                                          *
 *                        class MineLog definition                          *
 *                                                                          *
 ****************************************************************************/

class MineLog {
private:
	LL<MineRecord> rawFileData;
	LL<AbandonedMine> abandoned;
	LL<WorkingMine> working;
	LL<Mine*> allMines;
	FIPS_stateReference fipsLookUpTable;
public:
  MineLog(ifstream&, ifstream&);				// Constructor
  ~MineLog();														// Destructor
  
  void displayExecReport1() const;
}; // END class MineLog definition
#endif
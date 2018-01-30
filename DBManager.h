/*
 * DBManager.h
 *
 *  Created on: Oct 21, 2016
 *      Author: dkhelemendyk
 */

#ifndef DBMANAGER_H_
#define DBMANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "Record.h"
using namespace std;

/**
 * DBManager class
 *
 * The DBManager class represents and operates a database
 */
class DBManager {
public:
  static const string fN; //constant for a header title "First Name"
  static const string fL; //constant for a header title "Last Name"
  static const string fA; //constant for a header title "Address"
  static const string fC; //constant for a header title "City"
  static const string fS; //constant for a header title "State"
  static const string fZ; //constant for a header title "Zip"

  /**
   * constructors
   */
  DBManager();

  /**
   * Destructor
   */
  virtual ~DBManager();

  /**
   * Checks for invalid records flag
   */
  bool hasInvalidRecords() const;
  /**
   * Returns a vector of invalid records
   */
  vector<Record>& getInvalidRecords();

  /**
   * Gets a path to a database
   */
  string fileToOpen();

  /**
   * Reads records from a database one at a time
   */
  void readRecord(istream&);

  /**
   * Opens a file with the database and reads it
   */
  void readDB();

  /**
   * Checks DB for records with empty fields, if finds, move them to the invalidRecords vector
   * to be checked and filled by a user later, and removes these records from initial
   * vector representation of a database
   */
  void checkIncompleteRecords();

  /**
   * Creates a new vector without duplicate records
   */
  vector<Record> cleanDB();

  /**
   * Writes new database into a file
   */
  void writeNewDB();

  /**
   * Outputs a tabular style report to standard output
   */
  void printReport();

  /**
   * Determines the longest length of a field
   */
  array<int, 6> getMaxFieldLength();

  /**
   * Determines the optimal width of the column in the report
   */
  int optimizeWidth(string, int);

  /**
   * Centers the titles in each header
   */
  string centerHeader(const string s, int w);

private:
  string dbPath; //contains a path to a database
  bool hasInvalRecords; //flag for having invalid records
  vector<Record> records; //original vector of database records
  vector<Record> invalidRecords; //vector containing invalid records
  vector<Record> cleanedRecords; //to store records after cleaning of the database
};

#endif /* DBMANAGER_H_ */

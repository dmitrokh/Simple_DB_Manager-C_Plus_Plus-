/*
 * @file DBManager.cpp
 * @brief lab9 source file for the DBManager class
 *  Created on: Sep 21, 2016
 * @author dkhelemendyk
 */

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <array>
#include <algorithm>

#include "DBManager.h"
using namespace std;

/**
 * Constants for header titles, used for report printing
 */
const string DBManager::fN {"First Name"};
const string DBManager::fL {"Last Name"};
const string DBManager::fA {"Address"};
const string DBManager::fC {"City"};
const string DBManager::fS {"State"};
const string DBManager::fZ {"Zip"};

/**
 * Constructor without parameters
 * Instantiates a path to a DB to empty string, invalid records flag to false
 * declares two vectors: for original database and for invalid records
 */
DBManager::DBManager()
{
  dbPath = "";
  hasInvalRecords = false;
  vector<Record> records;
  vector<Record> invalidRecords;
  vector<Record> cleanedRecords;
}

/**
 * Destructor
 */
DBManager::~DBManager()
{
}

/**
 * Checks the condition of the invalid records flag
 * @param none
 * @return true if a database has invalid records, false if not
 */
bool DBManager::hasInvalidRecords() const
{
  return hasInvalRecords;
}

/**
 * A function to get a vector with invalid records that can be reviewed by a user
 * @param none
 * @return a vector with invalid records
 */
vector<Record>& DBManager::getInvalidRecords()
{
  return invalidRecords;
}

/**
 * Asks a user for a path to a database
 * @param none
 * @return string representation of the path to a database
 */
string DBManager::fileToOpen()
{
  cout << "Please enter the path to database: ";
  string path;
  cin >> path;
  return path;
}

/**
 * Reads a line from an input stream and records it to a vector
 * @param input stream
 * @return none
 */
void DBManager::readRecord(istream &ist)
{
  string line;
  getline(ist,line);
  if (!ist.eof())
    {
      records.push_back(Record(line));
    }
}

/**
 * Opens a database file and reads records from it
 * @param none
 * @return none
 */
void DBManager::readDB()
{
  dbPath = fileToOpen();
  //alternative: ifstream ifs; ifs.open (name, ifstream::in);
  ifstream ist {dbPath}; // ifstream is an“input stream from a file”
  ist.exceptions(ist.exceptions()|ios_base::badbit);
  if (!ist)
    {
      cerr << "can’t open file";
      return;
    }
  while (!ist.eof())
    {
      readRecord(ist);
    }
}

/**
 * Checks DB for records with empty fields, if finds, move them to the invalidRecords vector
 * to be checked and filled by a user later, and removes these records from initial
 * vector representation of a database, raises a flag for invlaid records
 * @param none
 * @return none
 */
void DBManager::checkIncompleteRecords()
{
  for (unsigned int i = 0; i < records.size(); ++i)
    {
      if (records[i].hasEmptyFields())
	{
	  hasInvalRecords = true;
	  invalidRecords.push_back(records[i]);
	  records.erase(records.begin()+i);
	}
    }
}

/**
 * Goes through the original vector and writes non-duplicate records to a new vector
 * @param none
 * @return a new vector without duplicates
 */
vector<Record> DBManager::cleanDB()
{
  vector<Record> validRecords;
  checkIncompleteRecords();
  for (Record r: records)
    {
      bool isDuplicate = false;
      for (Record nr: validRecords)
	{
	  if (nr == r)
	    {
	      isDuplicate = true;
	      break;
	    }
	}
      if (!isDuplicate)
	{
	  validRecords.push_back(r);
	}
    }
  sort(validRecords.begin(), validRecords.end());
  return validRecords;
}

/**
 * Writes a cleaned database to the same location with the original database,
 * gives a file with the new cleaned database a name based on an old name plus
 * prefix "new_"
 * @param none
 * @return none
 */
void DBManager::writeNewDB()
{
  string newDBName = "new_" + dbPath.substr(dbPath.find_last_of("/") + 1);
  string path = dbPath.substr(0, dbPath.find_last_of("/") + 1);
  ofstream ofs(path + newDBName); // ofstream is an “output stream from a file”
   // defining an ofstream with a name string
   // opens the file with that name for writing
  if (!ofs)
    {
      cerr << "can’t open output file";
    }
  cleanedRecords = cleanDB();
  for (unsigned int i = 0; i < cleanedRecords.size(); ++i)
    {
      ofs << i + 1 << "," << cleanedRecords[i];
    }
  ofs.close();
}

/**
 * Determines the longest length of values in fields in a vector
 * @param vector of cleaned records
 * @return array of the longest field values
 */
array<int, 6> DBManager::getMaxFieldLength()
{
  array<int, 6> maxFieldLength = {0, 0, 0, 0, 0, 0}; //array to hold the length of the longest values
  for (Record r: cleanedRecords)
    {
      //find the lengths of the longest values for each field
      if (r.getName().length() > maxFieldLength[0])
	{maxFieldLength[0] = r.getName().length();}
      if (r.getLName().length() > maxFieldLength[1])
	{maxFieldLength[1] = r.getLName().length();}
      if (r.getAddress().length() > maxFieldLength[2])
      	{maxFieldLength[2] = r.getAddress().length();}
      if (r.getCity().length() > maxFieldLength[3])
      	{maxFieldLength[3] = r.getCity().length();}
      if (r.getState().length() > maxFieldLength[4])
        {maxFieldLength[4] = r.getState().length();}
      if (r.getZip().length() > maxFieldLength[5])
       	{maxFieldLength[5] = r.getZip().length();}
    }
  return maxFieldLength;
}

/**
 * Optimizes the length of the columns in the report
 * @param
 * @return optimized width of the column
 */
int DBManager::optimizeWidth(string field, int l)
{
  //if the length of the header title is longer than the max length of the value
  //in a field, then make width equal to the length of the header title plus 2 characters
  //for a nicer look
  if (field.length() > l) return field.length() + 2;
  return l + 2; //add 2 characters for a nicer look
}

/**
 * Center the titles in each header
 * @param string to be centered, the width of the column
 * @return formatted string
 */
string DBManager::centerHeader(const string s, int w) {
    stringstream ss, spaces;
    int toFill = w - s.size(); //counts the number of characters except for a title
    for(int i = 0; i < toFill / 2; ++i)
      spaces << " ";
    ss << spaces.str() << s << spaces.str(); //format title header
    if(toFill > 0 && toFill % 2 != 0) //if odd number of characters to fill, add one space
      ss << " ";
    return ss.str();
}

/**
 * Prepares and outputs a report
 * @param DBManager class
 * @return none
 */
void DBManager::printReport()
{
  array<int, 6> fLength = getMaxFieldLength();
  //determine the width of each column based on a title name and the length
  //of the longest value in a field
  int nW = optimizeWidth(fN, fLength[0]);
  int lnW = optimizeWidth(fL, fLength[1]);
  int aW = optimizeWidth(fA, fLength[2]);
  int cW = optimizeWidth(fC, fLength[3]);
  int sW = optimizeWidth(fS, fLength[4]);
  int zW = optimizeWidth(fZ, fLength[5]);

  //print a header
  cout << setw(nW) << centerHeader(fN, nW)
       << setw(lnW) << centerHeader(fL, lnW)
       << setw(aW) << centerHeader(fA, aW)
       << setw(cW) << centerHeader(fC, cW)
       << setw(sW) << centerHeader(fS, sW)
       << setw(zW) << centerHeader(fZ, zW) << endl
       << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

  //print records
  for (Record r: cleanedRecords)
    {
      cout << left << setw(nW) << "|" + r.getName()
	   << left << setw(lnW) << "|" + r.getLName()
	   << left << setw(aW) << "|" + r.getAddress()
	   << setw(cW) << left << "|" + r.getCity()
	   << setw(sW) << left << "|" + r.getState()
	   << setw(zW) << left << "|" + r.getZip() << endl;
    }
}

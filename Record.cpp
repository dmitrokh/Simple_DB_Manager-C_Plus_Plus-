/*
 * @file Record.cpp
 * @brief lab9 source file for the Record class
 *  Created on: Sep 21, 2016
 * @author dkhelemendyk
 */

#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>

#include "Record.h"
using namespace std;

/**
 * Constructor with arguments
 * Takes a line of comma separated values from a database and parses it into the record
 * class fields
 */
Record::Record(string l)
{
  string index;
  stringstream lineStream(l);
  getline(lineStream, index, ',');
  getline(lineStream, name, ',');
  getline(lineStream, lName, ',');
  getline(lineStream, address, ',');
  getline(lineStream, city, ',');
  getline(lineStream, state, ',');
  getline(lineStream, zip, ',');
}

/**
 * Constructor with arguments
 * Takes string values of each field in a record object class
 */
Record::Record(string n, string l, string a, string c, string s, string z)
:name{n}, lName{l}, address{a}, city{c}, state{s}, zip{z}
{
}

/**
 * Destructor
 */
Record::~Record()
{
}

/**
  * Getter for name
  * @param none
  * @return string value of name
  */
string Record::getName() const
{
  return name;
}

/**
 * Getter for last name
 * @param none
 * @return string value of last name
 */
string Record::getLName() const
{
  return lName;
}

/**
 * Getter for address
 * @param none
 * @return string value of address
 */
string Record::getAddress() const
{
  return address;
}

/**
 * Getter for city
 * @param none
 * @return string value of city
 */
string Record::getCity() const
{
  return city;
}

/**
 * Getter for state
 * @param none
 * @return string value of state
 */
string Record::getState() const
{
  return state;
}

/**
 * Getter for zip
 * @param none
 * @return string value of zip
 */
string Record::getZip() const
{
  return zip;
}

/**
 * A function to check for empty fields in a record
 * @param none
 * @return true if a record has empty field(s), false if not
 */
bool Record::hasEmptyFields() const
{
  return (name=="" || lName =="" || address=="" ||
      city=="" || state=="" || zip=="");
}

/**
  * Overrides << operator for objects of type Record
  * @param output stream, Record class
  * @return output stream in a form of fields separated by commas
  */
std::ostream& operator <<(std::ostream& output, const Record& r)
{
  output << r.name << "," << r.lName << "," << r.address
       << "," << r.city << "," << r.state << "," << r.zip << std::endl;
  return output;
}

/**
  * Overrides the comparison operator "==" for objects of type Record
  * @param two objects of type Record to compare
  * @return boolean result of comparison
  */
bool operator ==(const Record &r1, const Record &r2)
{
  return (r1.name == r2.name && r1.lName == r2.lName && r1.address == r2.address &&
          r1.city == r2.city && r1.state == r2.state && r1.zip == r2.zip);
}

/**
 * Overrides the comparison operator "<" for objects of type Record
 * @param two objects of type Record to compare
 * @return boolean result of comparison
 */
bool operator <(const Record& r1, const Record& r2)
{
  if (r1.lName == r2.lName) {return r1.name < r2.name;}
  return r1.lName < r2.lName;
}

/**
  * Copy assignment; overrides the = operator for objects of type Record
  * @param the object of type Record that we want to assign to the current record
  * @return new object of type Record
  */
Record& Record::operator =( const Record& rhs )
{
  if (this == &rhs) return *this;
  name = rhs.name;
  lName = rhs.lName;
  address = rhs.address;
  city = rhs.city;
  zip = rhs.zip;
  return *this;
}



/*
 * Record.h
 *
 *  Created on: Oct 18, 2016
 *      Author: dkhelemendyk
 */

#ifndef LAB8_H_
#define LAB8_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * Record class
 *
 * The Record class represents one record (a line) from a database file in comma separated format
 */
class Record {
public:
  /**
   * constructors
   */
  Record(string);
  Record(string, string, string, string, string, string);

  /**
   * Getters
   */
  string getName() const;
  string getLName() const;
  string getAddress() const;
  string getCity() const;
  string getState() const;
  string getZip() const;

  /**
   * Checks whether a record has empty fields
   */
  bool hasEmptyFields() const;

  /**
   * Outputs the record to an output stream as a sequence of fields separated with commas
   */
  friend ostream& operator <<(ostream&, const Record&);
  /**
   * Defines the comparison == operator
   */
  friend bool operator ==(const Record&, const Record &b);

  /**
   * Defines copy assignment
   */
  Record& operator =( const Record& rhs );

  /**
   * Defines the < operator
   */
  friend bool operator <(const Record&, const Record&);

  /**
   * Destructor
   */
  virtual ~Record();

private:
  string name, lName, address, city, state, zip;
};

#endif /* LAB8_H_ */

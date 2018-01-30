/*
 * @file main.cpp
 * @brief main file
 *  Created on: Oct 19, 2016
 * @author dkhelemendyk
 */

#include <iostream>
#include "Record.h"
#include "DBManager.h"
using namespace std;

int main()
{
  //create an object representing a database
  DBManager dbManager {};
  //read database from a file
  dbManager.readDB();
  //write a new cleaned database on disk
  dbManager.writeNewDB();
  //prints the report
  dbManager.printReport();
}




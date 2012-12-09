/**
  hcprocess.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the method to process the Horn Clauses line by line in the file

*/

#ifndef HCPROCESS_H
#define HCPROCESS_H 

#include "stdafx.h"
#include "HornClause.h"
#include "SymbolTable.h"
#include <string>
#include <memory>
#include <vector>
using namespace std; 

// @brief Manipulates the file to parse the Horn Clauses line by line
// @param filename
// @return int - 0 = SUCCESS
int process(string& filename, vector<shared_ptr<HornClause>> & horn_clauses, ostream & output);

#endif
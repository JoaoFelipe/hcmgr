/**
  hcset.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the function to set the variable value
*/

#ifndef HCSET_H
#define HCSET_H 

#include "stdafx.h"
#include "HornClause.h"
#include "SymbolTable.h"
#include <string>
#include <memory>
#include <vector>
using namespace std; 

// @brief Parse a bound and a number from the text and set the value in the SymbolTable
// @param text - the bound and value
// @param output - ostream
// @return int indicating success (0-SUCCESS)
int set_variable(string& text, ostream & output);

#endif
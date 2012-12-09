/**
  hcrandomize.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the method to gerenerate a random value up to a max value.

*/

#ifndef HCRANDOMIZE_H
#define HCRANDOMIZE_H 

#include "stdafx.h"
#include "HornClause.h"
#include "SymbolTable.h"
#include <string>
#include <memory>
#include <vector>

using namespace std; 

// @brief Parse a bound and a optional number from the text and set the value in the SymbolTable to a random value between 0 and the number
// @param text is the bound and the optional value, output is ostream
// @return int indicating success (0-SUCCESS)
int randomize_variable(string& text, ostream & output);

// @brief Returns a random value from 0 to a given unsinged int max range (or INT_MAX)
// @param unsigned int max
// @return int - random value
int getRandomValue(unsigned int max);

#endif
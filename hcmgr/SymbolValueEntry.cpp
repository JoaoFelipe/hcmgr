/**
	SymbolValueEntry.cpp
	Class name: FunctionEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the SymbolValueEntry to represent Constants, Functions and Bound Variables
*/

#include "stdafx.h"
#include "SymbolValueEntry.h"
#include <sstream>
#include <iostream>

// @brief Checks if the Symbol can be evaluated
// @return bool
bool SymbolValueEntry::is_evaluable() const {
	return true;
}

// @brief Returns printable text of the SymbolTableEntry name and values
// @return string 		
string SymbolValueEntry::printable_text() const {
	ostringstream temp;
	temp << type() << ": " << text() << " = " << value();
	return temp.str();
}
/**
	UnboundSymbol.cpp
	Class name: UnboundSymbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the UNBOUND
*/

#include "stdafx.h"
#include "UnboundSymbol.h"
#include "string_utils.h"
#include "ConstantEntry.h"
#include "BoundEntry.h"
#include <iostream>
#include <sstream>
#include "const.h"

#include "UnboundEntry.h"

// @brief UnboundSymbol class Constructor using a value reference as parameter 
// @param v - reference to string value	
UnboundSymbol::UnboundSymbol(const string& v): _value(v) {}

// @brief UnboundSymbol class Copy Constructor 
// @param s - reference to another UnboundSymbol	
UnboundSymbol::UnboundSymbol(const UnboundSymbol& s): _value(s._value) {}

// @brief Returns a clone of the Symbol
// @return shared_ptr<Symbol>
shared_ptr<Symbol> UnboundSymbol::clone() const {
	return shared_ptr<Symbol>(new UnboundSymbol(*this));
}


// @brief Setter to the UnboundSymbol value 
// @param v - reference to string value	
void UnboundSymbol::value(const string& v) {
	_value = v;
}

// @brief Getter to the UnboundSymbol value 
// @return string 	
string UnboundSymbol::value() const {
	return _value;
}

// @brief Returns a text with the type and value of the Symbol 
// @return string 
string UnboundSymbol::text() const {
	string temp = "Unbound:" + _value;
	return temp;
}

// @brief Prints the Symbol according to the grammar syntax
// @param output - ostream
void UnboundSymbol::print(ostream & output) const {
	output << _value;
}

// @brief Converts the Symbol to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
shared_ptr<SymbolTableEntry> UnboundSymbol::convertToSymbolTableEntry() const {
	return shared_ptr<SymbolTableEntry>(new UnboundEntry(_value));
}

// @brief Get a list of SymbolTableEntry that can be added in the table
// @return vector<shared_ptr<SymbolTableEntry>>
vector<shared_ptr<SymbolTableEntry>> UnboundSymbol::getRealSymbolTableEntry() const {
	return vector<shared_ptr<SymbolTableEntry>>();
}


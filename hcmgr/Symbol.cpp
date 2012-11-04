/**
	Symbol.cpp
	Class name: Symbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the Symbol  for the grammar
				symbol -> LABEL | NUMBER
*/

#include "stdafx.h"
#include "Symbol.h"
#include "string_utils.h"
#include "ConstantEntry.h"
#include "VariableEntry.h"
#include <iostream>
#include <sstream>

// @brief Symbol class Constructor using a value reference as parameter 
// @param v - reference to string value	
Symbol::Symbol(const string& v): _value(v) {}

// @brief Symbol class Copy Constructor 
// @param s - reference to another Symbol	
Symbol::Symbol(const Symbol& s): _value(s._value) {}

// @brief Setter to the Symbol value 
// @param v - reference to string value	
void Symbol::value(const string& v) {
	_value = v;
}

// @brief Getter to the Symbol value 
// @return string 	
string Symbol::value() const {
	return _value;
}

// @brief Returns a text with the type and value of the Symbol 
// @return string 
string Symbol::text() const {
	if (check_string(_value, is_number)) {
		string temp = "Constant:" + _value;
		return temp;
	} else {
		string temp = "Variable:" + _value;
		return temp;
	}
}

// @brief Prints the Symbol according to the grammar syntax
// @param output - ostream
void Symbol::print(ostream & output) const {
	output << _value;
}

// @brief Converts the Symbol to a SymbolTableEntry
// @return SymbolTableEntry
SymbolTableEntry * Symbol::convertToSymbolTableEntry() const {
	if (check_string(_value, is_number)) {
		unsigned int value;
		istringstream str(_value);
		str >> value;
		return new ConstantEntry(value);
	} else {
		return new VariableEntry(_value);
	}
}

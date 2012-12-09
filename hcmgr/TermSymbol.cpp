/**
	TermSymbol.cpp
	Class name: TermSymbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the UNBOUND
*/

#include "stdafx.h"
#include "TermSymbol.h"
#include "string_utils.h"
#include "ConstantEntry.h"
#include "BoundEntry.h"
#include <iostream>
#include <sstream>
#include "SymbolTable.h"
#include "const.h"


// @brief TermSymbol class Constructor using a value reference as parameter 
// @param v - reference to string value	
TermSymbol::TermSymbol(const string& v): _value(v) {}

// @brief TermSymbol class Copy Constructor 
// @param s - reference to another TermSymbol	
TermSymbol::TermSymbol(const TermSymbol& s): _value(s._value) {}

// @brief Returns a clone of the Symbol
// @return Symbol * 
shared_ptr<Symbol> TermSymbol::clone() const {
	return shared_ptr<Symbol>(new TermSymbol(*this));
}


// @brief Setter to the TermSymbol value 
// @param v - reference to string value	
void TermSymbol::value(const string& v) {
	_value = v;
}

// @brief Getter to the TermSymbol value 
// @return string 	
string TermSymbol::value() const {
	return _value;
}

// @brief Returns a text with the type and value of the Symbol 
// @return string 
string TermSymbol::text() const {
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
void TermSymbol::print(ostream & output) const {
	output << _value;
}

// @brief Converts the Symbol to a SymbolTableEntry
// @param SymbolTable
// @return SymbolTableEntry
shared_ptr<SymbolTableEntry> TermSymbol::convertToSymbolTableEntry() const {
	shared_ptr<SymbolTable> table = SymbolTable::instance();
	shared_ptr<SymbolTableEntry> sym = table->find(this->text());
	if (!sym) {
		return this->getRealSymbolTableEntry()[0];
	}
	return sym;
}

// @brief Get a list of SymbolTableEntry that can be added in the table
// @return SymbolTableEntry
vector<shared_ptr<SymbolTableEntry>> TermSymbol::getRealSymbolTableEntry() const {
	vector<shared_ptr<SymbolTableEntry>> result;
	if (check_string(_value, is_number)) {
		unsigned int value;
		istringstream str(_value);
		str >> value;
		result.push_back(shared_ptr<SymbolTableEntry>(new ConstantEntry(value)));
	} else {
		result.push_back(shared_ptr<SymbolTableEntry>(new BoundEntry(_value)));
	}
	return result;
}


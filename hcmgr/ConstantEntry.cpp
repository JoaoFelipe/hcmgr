/**
	ConstantEntry.cpp
	Class name: ConstantEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the class ConstantEntry to represent a numeric symbol (constant) in the SymbolTable

*/


#include "stdafx.h"
#include "ConstantEntry.h"
#include <iostream>
#include <sstream>

using namespace std;

// @brief ConstantEntry class Constructor passing a value parameter
// @param v - value of the ConstantEntry
ConstantEntry::ConstantEntry(const unsigned int v): _value(v) {}

// @brief ConstantEntry class Copy Constructor
// @param other - reference to other ConstantEntry 
ConstantEntry::ConstantEntry(const ConstantEntry & other): _value(other._value) {}

// @brief Create a copy of the current ConstantEntry 
// @return shared_ptr<SymbolTableEntry>
shared_ptr<SymbolTableEntry> ConstantEntry::clone() const {
	return shared_ptr<SymbolTableEntry>(new ConstantEntry(*this));
}


// @brief Converts the current value to a constant
// @return shared_ptr<SymbolTableEntry> 
shared_ptr<SymbolTableEntry> ConstantEntry::get_constant_value() const {
	return this->clone();
}

// @brief Compares current ConstantEntry value with a ConstantEntry parameter value
// @param bool - returns true if they have same value  
bool ConstantEntry::operator==(const ConstantEntry & other) const {
	return _value == other._value;
}

// @brief Returns the name of the ConstantEntry type according to the grammar (Constant)
// @param string - name of the type  
string ConstantEntry::type() const {
	return "Constant";
}

// @brief Returns a string of the ConstantEntry value
// @param string - value in string  
string ConstantEntry::text() const {
	ostringstream convert;
	convert << _value;
	return convert.str();
}

// @brief Get the value of the Symbol
// @return int
int ConstantEntry::value() const {
	return _value;
}

// @brief Returns true if the ConstantEntry value is constant
// @param bool  
bool ConstantEntry::is_constant() const {
	return true;
}



/**
	VariableEntry.cpp
	Class name: VariableEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the VariableEntry to represent Variables in the SymbolTable
*/

#include "stdafx.h"
#include "VariableEntry.h"

// @brief  VariableEntry class Constructor using a label string reference as parameter 
// @param l - reference to string value as label	
VariableEntry::VariableEntry(const string & l): _label(l) {}

// @brief VariableEntry class Copy Constructor 
// @param other - reference to another VariableEntry
VariableEntry::VariableEntry(const VariableEntry & other): _label(other._label) {}

// @brief Returns the clone of the VariableEntry
// @return SymbolTableEntry
SymbolTableEntry * VariableEntry::clone() const {
	return new VariableEntry(*this);
}

// @brief Compares the current VariableEntry to another VariableEntry 
// @param other - references to another VariableEntry
// @return bool - returns true if they hava same label
bool VariableEntry::operator==(const VariableEntry & other) const {
	return _label == other._label;
}

// @brief Returns the name of the VariableEntry type
// @return string - name of the VariableEntry type 		
string VariableEntry::type() const {
	return "Variable";
}

// @brief Returns VariableEntry label
// @return string
string VariableEntry::text() const {
	return _label;
}

// @brief Returns true if the entry is constant
// @return bool
bool VariableEntry::is_constant() const {
	return false;
}

// @brief Returns true if the entry is variable
// @return bool
bool VariableEntry::is_variable() const {
	return true;
}


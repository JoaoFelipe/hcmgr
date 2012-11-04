
/**
	VariableEntry.cpp
	Class name: VariableEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the VariableEntry to represent Variables in the SymbolTable
*/

#include "stdafx.h"
#include "VariableEntry.h"

//  @brief VariableEntry(const string & l) - VariableEntry class Constructor using a label string reference as parameter 
//  @param l - reference to string value as label	
VariableEntry::VariableEntry(const string & l): _label(l) {}

//  @brief VariableEntry(const VariableEntry & other) - VariableEntry class Copy Constructor 
//  @param other - reference to another VariableEntry
VariableEntry::VariableEntry(const VariableEntry & other): _label(other._label) {}

//  @brief clone()  - Returns the clone of the VariableEntry
//  @return SymbolTableEntry
SymbolTableEntry * VariableEntry::clone() const {
	return new VariableEntry(*this);
}

//  @brief operator==(const VariableEntry & other)- Compares the current VariableEntry to another VariableEntry 
//  @param other - references to another VariableEntry
//  @return bool - returns true if they hava same label
bool VariableEntry::operator==(const VariableEntry & other) const {
	return _label == other._label;
}

//  @brief type()  - Returns the name of the VariableEntry type
//  @return string - name of the VariableEntry type 		
string VariableEntry::type() const {
	return "Variable";
}

//  @brief text()  - Returns VariableEntry label
//  @return string
string VariableEntry::text() const {
	return _label;
}

//  @brief is_constant()  - Returns true if the entry is constant
//  @return bool
bool VariableEntry::is_constant() const {
	return false;
}

//  @brief is_variable()  - Returns true if the entry is variable
//  @return bool
bool VariableEntry::is_variable() const {
	return true;
}


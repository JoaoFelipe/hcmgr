
/**
	VariableEntry.h
	Class name: VariableEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the VariableEntry to represent Variables in the SymbolTable
*/


#ifndef VARIABLE_ENTRY_H
#define VARIABLE_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include <string>

using namespace std;

class VariableEntry : public SymbolEntry {
public:

// @brief VariableEntry class Constructor using a label string reference as parameter 
// @param l - reference to string value as label	
	VariableEntry(const string & l);

// @brief VariableEntry class Copy Constructor 
// @param other - reference to another VariableEntry
	VariableEntry(const VariableEntry & other);

// @brief Returns the clone of the VariableEntry
// @return SymbolTableEntry
	virtual SymbolTableEntry * clone() const;

// @brief Compares the current VariableEntry to another VariableEntry 
// @param other - references to another VariableEntry
// @return bool - returns true if they hava same label
	bool operator==(const VariableEntry & other) const;

// @brief Returns the name of the VariableEntry type
// @return string - name of the VariableEntry type 	
	virtual string type() const;

// @brief Returns VariableEntry label
// @return string
	virtual string text() const;

// @brief Returns true if the entry is constant
// @return bool
	virtual bool is_constant() const;

// @brief Returns true if the entry is variable
// @return bool
	virtual bool is_variable() const;


private:
// Label of the VariableEntry
	string _label;
};

#endif

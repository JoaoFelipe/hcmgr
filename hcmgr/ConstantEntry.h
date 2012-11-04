/**
	ConstantEntry.h
	Class name: ConstantEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the class ConstantEntry to represent a numeric symbol (constant) in the SymbolTable

*/


#ifndef CONSTANT_ENTRY_H
#define CONSTANT_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include <string>

using namespace std;

class ConstantEntry : public SymbolEntry {
public:

// @brief ConstantEntry class Constructor passing a value parameter
// @param v - value of the ConstantEntry
	ConstantEntry(const unsigned int v);

// @brief ConstantEntry class Copy Constructor
// @param other - reference to other ConstantEntry 
	ConstantEntry(const ConstantEntry & other);

// @brief Create a copy of the current ConstantEntry 
// @return SymbolTableEntry - clone 
	virtual SymbolTableEntry * clone() const;

// @brief Compares current ConstantEntry value with a ConstantEntry parameter value
// @param bool - returns true if they have same value  
	bool operator==(const ConstantEntry & other) const;

// @brief Returns the name of the ConstantEntry type according to the grammar (Constant)
// @param string - name of the type  
	virtual string type() const;

// @brief Returns a string of the ConstantEntry value
// @param string - value in string  
	virtual string text() const;

// @brief Returns true if the ConstantEntry value is constant
// @param bool  
	virtual bool is_constant() const;

// @brief Returns true if the ConstantEntry value is variable
// @param bool
	virtual bool is_variable() const;

private:
// Value of the ConstantEntry
	unsigned int _value;
};

#endif
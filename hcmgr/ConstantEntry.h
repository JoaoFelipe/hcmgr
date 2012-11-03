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

//  @brief ConstantEntry(const unsigned int v) - ConstantEntry class Constructor passing a value parameter
//  @param v - value of the ConstantEntry
	ConstantEntry(const unsigned int v);

//  @brief ConstantEntry(const ConstantEntry & other) - ConstantEntry class Copy Constructor
//  @param other - reference to other ConstantEntry 
	ConstantEntry(const ConstantEntry & other);

//  @brief clone() - Create a copy of the current ConstantEntry 
//  @return SymbolTableEntry - clone 
	virtual SymbolTableEntry * clone() const;

//  @brief operator==(const ConstantEntry & other) - Compares current ConstantEntry value with a ConstantEntry parameter value
//  @param bool - returns true if they have same value  
	bool operator==(const ConstantEntry & other) const;

//  @brief type() - Returns the name of the ConstantEntry type according to the grammar (Constant)
//  @param string - name of the type  
	virtual string type() const;

//  @brief text() - Returns a string of the ConstantEntry value
//  @param string - value in string  
	virtual string text() const;

//  @brief is_constant() - Returns true if the ConstantEntry value is constant
//  @param bool  
	virtual bool is_constant() const;

//  @brief is_variable() - Returns true if the ConstantEntry value is variable
//  @param bool
	virtual bool is_variable() const;

private:
// Value of the ConstantEntry
	unsigned int _value;
};

#endif
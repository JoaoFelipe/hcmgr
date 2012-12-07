/**
	SymbolValueEntry.h
	Class name: SymbolValueEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the SymbolValueEntry to represent Bound, Function and Constant
*/
#ifndef SYMBOL_VALUE_ENTRY_H
#define SYMBOL_VALUE_ENTRY_H

#include "stdafx.h"
#include "SymbolEntry.h"
#include "SubstitutionList.h"
#include <string>
#include <memory>

using namespace std;

class SymbolValueEntry : public SymbolEntry {
public:

// @brief Returns the clone of the SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
	virtual shared_ptr<SymbolTableEntry> clone() const = 0;

// @brief Converts the current value to a constant
// @return shared_ptr<SymbolTableEntry> 
	virtual shared_ptr<SymbolTableEntry> get_constant_value() const = 0;

// @brief Get the value of the Symbol
// @return int
	virtual int value() const = 0;

	
// @brief Checks if the Symbol can be evaluated
// @return bool
	virtual bool is_evaluable() const;
};

#endif
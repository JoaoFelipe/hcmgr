/**
	FunctionEntry.h
	Class name: FunctionEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the FunctionEntry to represent Variables in the SymbolTable
*/


#ifndef FUNCTION_ENTRY_H
#define FUNCTION_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include "SymbolValueEntry.h"
#include <string>
#include <memory>

using namespace std;

class FunctionEntry : public SymbolValueEntry {
public:

// @brief FunctionEntry class Constructor using thre label string reference as parameter 
// @param operation - reference to string 
// @param term1, term2 - pointers to SymbolTableEntry 
	FunctionEntry(const string & operation, shared_ptr<SymbolValueEntry> term1, shared_ptr<SymbolValueEntry> term2);

// @brief FunctionEntry class Copy Constructor 
// @param other - reference to another FunctionEntry
	FunctionEntry(const FunctionEntry & other);

// @brief Returns the clone of the FunctionEntry
// @return shared_ptr<SymbolTableEntry>
	virtual shared_ptr<SymbolTableEntry> clone() const;

// @brief Converts the current value to a constant
// @return shared_ptr<SymbolTableEntry> 
	virtual shared_ptr<SymbolTableEntry> get_constant_value() const;

// @brief Compares the current FunctionEntry to another FunctionEntry
// @param other - references to another FunctionEntry
// @return bool - returns true if they have same fields
	bool operator==(const FunctionEntry & other) const;

// @brief Returns the name of the FunctionEntry type
// @return string - name of the FunctionEntry type 	
	virtual string type() const;

// @brief Returns FunctionEntry text
// @return string
	virtual string text() const;

// @brief Get the value of the Symbol
// @return int
	virtual int value() const;

// @brief Returns true if the entry is function
// @return bool
	virtual bool is_function() const;

// @brief Returns the modified symbols with the substitutions after the unification 
// @return string - symbols after substitutions 			
	virtual string unification(SubstitutionList & substitution_list) const;


private:
// Operation of the FunctionEntry
	string _operation;
// Term1 of the FunctionEntry
	shared_ptr<SymbolValueEntry> _term1;
// Term2 of the FunctionEntry
	shared_ptr<SymbolValueEntry> _term2;
};

#endif

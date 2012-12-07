
/**
	SymbolTableEntry.h
	Class name: SymbolTableEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the SymbolTableEntry as superclass of the tokens representations in the SymbolTable
*/


#ifndef SYMBOL_TABLE_ENTRY_H
#define SYMBOL_TABLE_ENTRY_H

#include "stdafx.h"
#include <string>
#include <memory>
using namespace std;

class SubstitutionList;

class SymbolTableEntry {
public:
// @brief Returns the clone of the SymbolTableEntry
// @return SymbolTableEntry
	virtual shared_ptr<SymbolTableEntry> clone() const = 0;
	
// @brief Compares the current SymbolTableEntry to another SymbolTableEntry 
// @param other - references to another SymbolTableEntry	
	virtual bool operator==(const SymbolTableEntry & other) const;

// @brief Compares the current SymbolTableEntry text to a text given as parameter 
// @param t - references to a text string ('type:text' format)
	virtual bool equals(const string& text) const;

// @brief Returns the name of SymbolTableEntry type
// @return string - name of the SymbolTableEntry type
	virtual string type() const = 0;

// @brief Returns text of the SymbolTableEntry name and values
// @return string 		
	virtual string text() const = 0;

// @brief Returns true if a SymbolTableEntry is a Predicate
// @return bool 
	virtual bool is_predicate() const;

// @brief Returns true if a SymbolTableEntry is a constant
// @return bool 
	virtual bool is_constant() const;

// @brief Returns true if a SymbolTableEntry is a bound
// @return bool 
	virtual bool is_bound() const;

// @brief Returns true if a SymbolTableEntry is a function
// @return bool 
	virtual bool is_function() const;

// @brief Returns true if a SymbolTableEntry is an unbound
// @return bool 
	virtual bool is_unbound() const;

// @brief Checks if the Symbol can be evaluated
// @return bool
	virtual bool is_evaluable() const;

// @brief Returns true if the current SymbolTableEntry matches with other SymbolTableEntry
// @return bool
	virtual bool matches(shared_ptr<SymbolTableEntry> other, SubstitutionList & substitution_list) const = 0;

// @brief Returns the modified entries with the substitutions after the unification 
// @return string - entries after substitutions 		
	virtual string unification(SubstitutionList & substitution_list) const = 0;
};



#endif


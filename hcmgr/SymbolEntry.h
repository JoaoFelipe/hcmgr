/**
	SymbolEntry.h
	Class name: SymbolEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the SymbolEntry to represent a Symbol in the SymbolTable
*/
#ifndef SYMBOL_ENTRY_H
#define SYMBOL_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SubstitutionList.h"
#include <string>

using namespace std;

class SymbolEntry : public SymbolTableEntry {
public:

// @brief Returns the clone of the SymbolTableEntry
// @return SymbolTableEntry
	virtual SymbolTableEntry * clone() const = 0;

// @brief Returns true if a SymbolTableEntry is a Predicate
// @return bool 
	virtual bool is_predicate() const;

// @brief Returns true if the current SymbolTableEntry matches with other SymbolTableEntry
// @return bool
	virtual bool SymbolEntry::matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const;
	
// @brief Returns the modified symbols with the substitutions after the unification 
// @return string - symbols after substitutions 			
	virtual string SymbolEntry::unification(SubstitutionList & substitution_list) const;
};

#endif

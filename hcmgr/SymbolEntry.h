/**
	SymbolEntry.h
	Class name: SymbolEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the SymbolEntry to represent a Symbol in the SymbolTable
*/
#ifndef SYMBOL_ENTRY_H
#define SYMBOL_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SubstitutionList.h"
#include <string>
#include <memory>

using namespace std;

class SymbolEntry : public SymbolTableEntry {
public:

// @brief Returns the clone of the SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
	virtual shared_ptr<SymbolTableEntry> clone() const = 0;

// @brief Returns true if the current SymbolTableEntry matches with other SymbolTableEntry
// @return bool
	virtual bool SymbolEntry::matches(shared_ptr<SymbolTableEntry> other, SubstitutionList & substitution_list) const;

// @brief Returns the modified symbols with the substitutions after the unification 
// @return string - symbols after substitutions 			
	virtual string SymbolEntry::unification(SubstitutionList & substitution_list) const;

};


#endif

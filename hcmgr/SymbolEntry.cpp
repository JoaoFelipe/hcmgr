/**
	SymbolEntry.cpp
	Class name: SymbolEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the SymbolEntry to represent a Symbol in the SymbolTable
*/

#include "stdafx.h"
#include "SymbolEntry.h"
#include "const.h"

//  @brief is_predicate()  - Returns true if a SymbolTableEntry is a Predicate
//  @return bool 
bool SymbolEntry::is_predicate() const {
	return false;
}

//  @brief matches(SymbolTableEntry * other, SubstitutionList & substitution_list)  - Returns true if the current SymbolTableEntry matches with other SymbolTableEntry
//  @return bool 		
bool SymbolEntry::matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const {
	if (!other->is_variable() && !other->is_constant()) {
		return false;
	}
	SymbolTableEntry * os = substitution_list.find(other);
	if (os == NONE) {
		os = other;
	}

	const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);

	SymbolTableEntry * ts = substitution_list.find(super);
	if (ts == NONE) {
		return (super == os);
	}
	return (ts == os);
}

//  @brief unification(SubstitutionList & substitution_list)  - Returns the modified symbols with the substitutions after the unification 
//  @return string - symbols after substitutions 		
string SymbolEntry::unification(SubstitutionList & substitution_list) const {
	const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);
	SymbolTableEntry * ts = substitution_list.find(super);
	if (ts == NONE) {
		return text();
	} else {
		string result = ts->text() + "/";
		result += text();
		return result;
	}
}

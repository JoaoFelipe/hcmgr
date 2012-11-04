/**
	SubstitutionList.cpp
	Class name: SubstitutionList 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the SubstitutionList to search and store equivalent symbols for the unification
*/

#include "stdafx.h"
#include "SubstitutionList.h"
#include "SymbolTableEntry.h"
#include "const.h"

// @brief SubstitutionList class Default Constructor 
SubstitutionList::SubstitutionList(): _substitutions() {}

// @brief Searches a SynbolTableEntry in the SubstitutionList
// @param entry - reference to a SymbolTableEntry
// @return SymbolTableEntry - Returns the substitution entry or NONE if it doesn't find a substitution
SymbolTableEntry * SubstitutionList::find(const SymbolTableEntry * entry) const {
	SymbolTableEntry * current = NONE;
	for (vector<pair<SymbolTableEntry *, SymbolTableEntry *>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		if (i->first == entry) {
			current = i->second;
			break;
		}
	}
	if (current != NONE) {
		SymbolTableEntry * again = find(current);
		if (again == NONE) {
			return current;
		} else {
			return again;
		}
	}
	return NONE;
}

// @brief Add a valid pair of entries to the substitution list
// @param first, second - references to the first and second values of the pair - the second is a substitute for the first
void SubstitutionList::add(SymbolTableEntry * first, SymbolTableEntry * second) {
	_substitutions.push_back(pair<SymbolTableEntry *, SymbolTableEntry *>(first, second));
}


// @brief Prints the pairs of the Substitution List
// @param output - ostream
void SubstitutionList::print(ostream & output) const {
	for (vector<pair<SymbolTableEntry *, SymbolTableEntry *>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		output << "  " << i->second->text() << "/" << i->first->text() << endl;
	}
}
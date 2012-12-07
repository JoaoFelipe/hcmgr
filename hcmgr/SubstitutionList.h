/**
	SubstitutionList.h
	Class name: SubstitutionList 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the SubstitutionList to search and store equivalent symbols for the unification
*/


#ifndef SUBSTITUTION_LIST_H
#define SUBSTITUTION_LIST_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include <vector>
#include <ostream>
#include <iostream>
#include <memory>
using namespace std;

class SubstitutionList {
public:

// @brief SubstitutionList class Default Constructor 
	SubstitutionList();

// @brief Searches a SynbolTableEntry in the SubstitutionList
// @param entry - reference to a SymbolTableEntry
// @return SymbolTableEntry - Returns the substitution entry or NONE if it doesn't find a substitution
	shared_ptr<SymbolTableEntry> find(shared_ptr<const SymbolTableEntry> entry) const;

// @brief Searches a SynbolTableEntry in the SubstitutionList and returns itself if not found.
// @param entry - reference to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
	shared_ptr<SymbolTableEntry> find_non_null(shared_ptr<SymbolTableEntry> entry) const;

	
// @brief Searches a SynbolTableEntry in the SubstitutionList and returns itself if not found. For functions and bound, returns the evalueted value in ConstantEntry
// @param entry - reference to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
	shared_ptr<SymbolTableEntry> find_value(shared_ptr<SymbolTableEntry> entry) const;


// @brief Add a valid pair of entries to the substitution list
// @param first, second - references to the first and second values of the pair - the second is a substitute for the first
	void add(shared_ptr<SymbolTableEntry> first, shared_ptr<SymbolTableEntry> second);

// @brief Prints the pairs of the Substitution List
// @param output - ostream
	void print(ostream & output=cout) const;

private:
// Pairs of the substitution list <original symbol, substitute>
	vector<pair<shared_ptr<SymbolTableEntry>, shared_ptr<SymbolTableEntry>>> _substitutions;

};

#endif

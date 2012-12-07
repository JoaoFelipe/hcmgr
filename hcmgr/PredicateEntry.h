/**
	PredicateEntry.h
	Class name: PredicateEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the PredicateEntry to represent the Predicate in the SymbolTable
*/


#ifndef PREDICATE_ENTRY_H
#define PREDICATE_ENTRY_H

#include "stdafx.h"
#include "SymbolTable.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include "SubstitutionList.h"
#include "Predicate.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class PredicateEntry : public SymbolTableEntry {
public:

// @brief PredicateEntry class Constructor
// @param symbols - reference to a vector<SymbolTableEntry *>	
	PredicateEntry(string & name, vector<shared_ptr<SymbolTableEntry>>& symbols);

// @brief PredicateEntry class Copy Constructor 
// @param other - references to another PredicateEntry
	PredicateEntry(const PredicateEntry & other);

// @brief Returns a clone of the current PredicateEntry as a SymbolTableEntry 
// @return SymbolTableEntry 
	virtual shared_ptr<SymbolTableEntry> clone() const;

// @brief Compares the current PredicateEntry to another PredicateEntry 
// @param other - references to another PredicateEntry
	bool operator==(const PredicateEntry & other) const;

// @brief Getter method for the PredicateEntry name
// @return string - PredicateEntry name		
	string PredicateEntry::name() const;

// @brief Returns the name of PredicateEntry type
// @return string - name of the PredicateEntry type 		
	virtual string type() const;

// @brief Returns PredicateEntry name followed by its symbols
// @return string 		
	virtual string text() const;

// @brief Returns true if a SymbolTableEntry is a Predicate
// @return bool 		
	virtual bool is_predicate() const;

// @brief Returns true if the PredicateEnry matches with other PredicateEntry
// @return bool 		
	virtual bool matches(shared_ptr<SymbolTableEntry> other, SubstitutionList & substitution_list) const;
	
// @brief Returns the modified predicate with the substitutions after the unification 
// @return string - predicate after substitutions 		
	virtual string unification(SubstitutionList & substitution_list) const;

private:
// Name of the PredicateEntry
	string _name;
// Vector of Symbols of the PredicateEntry
	vector<shared_ptr<SymbolTableEntry>> _symbols;
};

#endif
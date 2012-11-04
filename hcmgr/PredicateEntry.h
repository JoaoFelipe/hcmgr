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

using namespace std;

class PredicateEntry : public SymbolTableEntry {
public:

//  @brief PredicateEntry(const Predicate & p, const SymbolTable & table) - PredicateEntry class Constructor using a Predicate and SymbolTable references as parameters 
//  @param p, table - references to a Predicate and SymbolTable	
	PredicateEntry(const Predicate & p, const SymbolTable & table);

//  @brief PredicateEntry(const PredicateEntry & other) - PredicateEntry class Copy Constructor 
//  @param other - references to another PredicateEntry
	PredicateEntry(const PredicateEntry & other);

//  @brief clone() - Returns a clone of the current PredicateEntry as a SymbolTableEntry 
//  @return SymbolTableEntry 
	virtual SymbolTableEntry * clone() const;

//  @brief operator==(const PredicateEntry & other)- Compares the current PredicateEntry to another PredicateEntry 
//  @param other - references to another PredicateEntry
	bool operator==(const PredicateEntry & other) const;

//  @brief name()  - Getter method for the PredicateEntry name
//  @return string - PredicateEntry name		
	string PredicateEntry::name() const;

//  @brief type()  - Returns the name of PredicateEntry type
//  @return string - name of the PredicateEntry type 		
	virtual string type() const;

//  @brief text()  - Returns PredicateEntry name followed by its symbols
//  @return string 		
	virtual string text() const;

//  @brief is_predicate()  - Returns true if a SymbolTableEntry is a Predicate
//  @return bool 		
	virtual bool is_predicate() const;

//  @brief is_constant()  - Returns true if a SymbolTableEntry is a constant
//  @return bool 		
	virtual bool is_constant() const;

//  @brief is_variable()  - Returns true if a SymbolTableEntry is a variable
//  @return bool 		
	virtual bool is_variable() const;

//  @brief matches(SymbolTableEntry * other, SubstitutionList & substitution_list)  - Returns true if the PredicateEnry matches with other PredicateEntry
//  @return bool 		
	virtual bool matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const;
	
//  @brief unification(SubstitutionList & substitution_list)  - Returns the modified predicate with the substitutions after the unification 
//  @return string - predicate after substitutions 		
	virtual string unification(SubstitutionList & substitution_list) const;

private:
// Name of the PredicateEntry
	string _name;
// Vector of Symbols of the PredicateEntry
	vector<SymbolTableEntry *> _symbols;
};

#endif
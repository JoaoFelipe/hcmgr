/**
	SymbolTable.h
	Class name: SymbolTable
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the SymbolTable to manage the entries
*/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <vector>
#include "SymbolTableEntry.h"
#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class SymbolTable {
public:
//  @brief SymbolTable() - SymbolTable class default Constructor 
	SymbolTable();

//  @brief ~SymbolTable() - SymbolTable class Destructor 
	~SymbolTable();

//  @brief add(SymbolTableEntry * entry) - Add an entry to the SymbolTable 
//  @param entry - references to a SymbolTableEntry
//  @return bool - returns true if it is possible to add (no duplicate entry) 
	bool add(SymbolTableEntry * entry);

//  @brief find(const string & value) - Seaches if a value exists in the entries 
//  @param value - string value for the entry
//  @return SymbolTableEntry - returns the SymbolTableEntry for the value, or NONE if not found
	SymbolTableEntry * find(const string & value) const;

//  @brief print(ostream & output)  - Prints the SymbolTable entries
//  @param output - ostream
	void SymbolTable::print(ostream & output=cout) const;

//  @brief print(ostream & output)  - Prints entries predicates
//  @param output - ostream
	void SymbolTable::print_predicates(ostream & output=cout) const;

//  @brief unifications(ostream & output)  - Prints the SymbolTable status after unifications (substitutions)
//  @param output - ostream
	void SymbolTable::unifications(ostream & output=cout) const;
private:
// Vector of the SymbolTable entries
	vector<SymbolTableEntry *> _entries;
};

#endif
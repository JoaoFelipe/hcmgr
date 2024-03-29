/**
	SymbolTable.h
	Class name: SymbolTable
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the SymbolTable to manage the entries
*/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <vector>
#include "SymbolTableEntry.h"
#include <string>
#include <ostream>
#include <iostream>
#include <memory>
using namespace std;

class SymbolTable {
public:

// @brief instantiate the SymbolTable and returns an instance of it
	static shared_ptr<SymbolTable> instance();

// @brief Add an entry to the SymbolTable 
// @param entry - shared_ptr<SymbolTableEntry>
// @return bool - returns true if it is possible to add (no duplicate entry) 
	bool add(shared_ptr<SymbolTableEntry> entry);

// @brief Seaches if a value exists in the entries 
// @param value - string value for the entry
// @return shared_ptr<SymbolTableEntry> - returns the SymbolTableEntry for the value, or NONE if not found
	shared_ptr<SymbolTableEntry> find(const string & value) const;

// @brief Prints the SymbolTable entries
// @param output - ostream
	void SymbolTable::print(ostream & output=cout) const;

// @brief Prints entries predicates
// @param output - ostream
	void SymbolTable::print_predicates(ostream & output=cout) const;

// @brief Prints the SymbolTable status after unifications (substitutions)
// @param output - ostream
	void SymbolTable::unifications(ostream & output=cout) const;

// @brief Erases the SymbolTable
	void SymbolTable::erase();

// @brief Backup current entries
	void SymbolTable::backup();

// @brief Restore current entries
	void SymbolTable::restore();


private:
// Vector of the SymbolTable entries
	vector<shared_ptr<SymbolTableEntry>> _entries;
// Vector for backup of the SymbolTable entries
	vector<shared_ptr<SymbolTableEntry>> _back_state;
// Singleton instance
	static shared_ptr<SymbolTable> _instance;

// @brief SymbolTable class default Constructor 
	SymbolTable();

};

#endif
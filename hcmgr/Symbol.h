/**
	Symbol.h
	Class name: Symbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the Symbol  for the grammar
				symbol -> LABEL | NUMBER
*/

#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>
#include "SymbolTableEntry.h"
#include <vector>
#include "SymbolTable.h"
#include <memory>
#include <memory>

using namespace std;

class Symbol
{
public:

// @brief Returns a clone of the Symbol
// @return shared_ptr<Symbol>
	virtual shared_ptr<Symbol> clone() const = 0;

// @brief Returns a text with the type and value of the Symbol 
// @return string 
	virtual string text() const = 0;

// @brief Prints the Symbol according to the grammar syntax
// @param output - ostream
	virtual void print(ostream & = cout) const = 0; 

// @brief Converts the Symbol to a SymbolTableEntry
// @param SymbolTable
// @return shared_ptr<SymbolTableEntry>
	virtual shared_ptr<SymbolTableEntry> convertToSymbolTableEntry(SymbolTable & table) const = 0;

// @brief Get a list of SymbolTableEntry that can be added in the table
// @return  vector<shared_ptr<SymbolTableEntry>>
	virtual vector<shared_ptr<SymbolTableEntry>> getRealSymbolTableEntry() const = 0;

};
 

#endif
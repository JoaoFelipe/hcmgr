/**
	UnboundSymbol.h
	Class name: UnboundSymbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the Unbound

*/

#ifndef UNBOUND_SYMBOL_H
#define UNBOUND_SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>
#include "Symbol.h"
#include "SymbolTable.h"
#include <memory>

using namespace std;

class UnboundSymbol: public Symbol
{
private:
// Value of the Symbol
	string _value;
public:

// @brief UnboundSymbol class Constructor using a value reference as parameter 
// @param v - reference to string value	
    UnboundSymbol(const string& v);
	
// @brief UnboundSymbol class Copy Constructor 
// @param s - reference to another UnboundSymbol		
	UnboundSymbol(const UnboundSymbol& s);

// @brief Returns a clone of the Symbol
// @return shared_ptr<Symbol>
	virtual shared_ptr<Symbol> clone() const;


// @brief Setter to the UnboundSymbol value 
// @param v - reference to string value	
    void value(const string& v);

// @brief Getter to the UnboundSymbol value 
// @return string 	
    string value() const;

// @brief Returns a text with the type and value of the Symbol 
// @return string 
	virtual string text() const;

// @brief Prints the Symbol according to the grammar syntax
// @param output - ostream
	virtual void print(ostream & = cout) const; 

// @brief Converts the Symbol to a SymbolTableEntry
// @param SymbolTable
// @return SymbolTableEntry
	virtual shared_ptr<SymbolTableEntry> convertToSymbolTableEntry() const;

// @brief Get a list of SymbolTableEntry that can be added in the table
// @return SymbolTableEntry
	virtual vector<shared_ptr<SymbolTableEntry>> getRealSymbolTableEntry() const;

};
 

#endif
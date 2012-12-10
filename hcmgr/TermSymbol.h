/**
	TermSymbol.h
	Class name: TermSymbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the term -> NUMBER | BOUND

*/

#ifndef TERM_SYMBOL_H
#define TERM_SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>
#include "Symbol.h"
#include "SymbolTable.h"
#include <memory>
using namespace std;

class TermSymbol: public Symbol
{
private:
// Value of the Symbol
	string _value;
public:

// @brief TermSymbol class Constructor using a value reference as parameter 
// @param v - reference to string value	
    TermSymbol(const string& v);
	
// @brief TermSymbol class Copy Constructor 
// @param s - reference to another TermSymbol		
	TermSymbol(const TermSymbol& s);

// @brief Returns a clone of the Symbol
// @return shared_ptr<Symbol>
	virtual shared_ptr<Symbol> clone() const;

// @brief Setter to the TermSymbol value 
// @param v - reference to string value	
    void value(const string& v);

// @brief Getter to the TermSymbol value 
// @return string 	
    string value() const;

// @brief Returns a text with the type and value of the Symbol 
// @return string 
	virtual string text() const;

// @brief Prints the Symbol according to the grammar syntax
// @param output - ostream
	virtual void print(ostream & = cout) const; 

// @brief Converts the Symbol to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry> 
	virtual shared_ptr<SymbolTableEntry> convertToSymbolTableEntry() const;

// @brief Get a list of SymbolTableEntry that can be added in the table
// @return vector<shared_ptr<SymbolTableEntry>>
	virtual vector<shared_ptr<SymbolTableEntry>> getRealSymbolTableEntry() const;
};
 

#endif
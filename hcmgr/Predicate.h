/**
	Predicate.h
	Class name: Predicate 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the Predicate for the grammar
				predicate -> LEFTPAREN name {symbol} RIGHTPAREN
*/

#ifndef PREDICATE_H
#define PREDICATE_H

#include <vector>
#include "Name.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include <ostream>
#include <iostream>

class Predicate
{
private:
// Name of the Predicate
	Name _name;
// Vector of Symbols of the Predicate
	vector<Symbol> _symbols; 
public:

// @brief Predicate class Constructor using a Name and a vector of Symbols as parameters 
// @param n, s - references to a Name and a vector of Symbols	
	Predicate(const Name& n, const vector<Symbol>& s);

// @brief Predicate class Copy Constructor
// @param p - reference to another Predicate
	Predicate(const Predicate& p);

// @brief Setter method for the Predicate Name
// @param n - reference to a Name	
    void name(const Name& n);
    
// @brief Getter method for the Predicate Name
// @return Name - Predicate Name		
	Name name() const;

// @brief Setter method for the vector of Symbols
// @param s - reference to a vector of Symbols	
	void symbols(const vector<Symbol>& s);

// @brief Getter method for the Predicate vector of Symbols
// @return vector<Symbol> - Predicate vector of Symbols	

	vector<Symbol> symbols() const;

// @brief Prints the Predicate according to the grammar syntax
// @param output - ostream
	void print(ostream & = cout) const; 

// @brief Fills out a Symbol Table with tokens from the Predicate 
// @param table - SymbolTable 
	void fill_symbol_table(SymbolTable & table) const;

};



#endif

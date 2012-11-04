/**
	Head.h
	Class name: Head 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the class Head for the grammar
			    head -> predicate
*/

#ifndef HEAD_H
#define HEAD_H

#include "Predicate.h"
#include <ostream>
#include <iostream>

using namespace std;

class Head
{
private:
// Predicate of the Head token  
	Predicate _predicate; 
public:

//  @brief Head(const Predicate& p) - Head class Constructor using a predicate parameter
//  @param p - reference to a predicate 
	Head(const Predicate& p);

//  @brief Head(const Head& h) - Head class Copy Constructor
//  @param h - reference to another head
	Head(const Head& h);
 
//  @brief predicate(const Predicate& p) - Setter to the Head predicate
//  @param p - reference to a predicate
	void predicate(const Predicate& p);
	
//  @brief predicate() - Getter to the Head predicate
//  @return Predicate
	Predicate predicate() const;
	
//  @brief print(ostream & output)  - Prints the predicate according to the grammar syntax
//  @param output - ostream
	void print(ostream & = cout) const;

//  @brief fill_symbol_table(SymbolTable & table) - Fills out a Symbol Table with tokens from the predicate and its symbols (variables and constants)
//  @param table - SymbolTable
	void fill_symbol_table(SymbolTable & table) const;

};

#endif
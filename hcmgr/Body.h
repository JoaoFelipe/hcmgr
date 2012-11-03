/**
	Body.h
	Class name: Body 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the class Body for the grammar
			    body -> LEFTPAREN predicate {predicate} RIGHTPAREN
*/

#ifndef BODY_H
#define BODY_H

#include <vector>
#include "Predicate.h"
#include <ostream>
#include <iostream>

using namespace std;

class Body
{
private:
// Vector with one or more predicates
	vector<Predicate> _predicates; 
public:
//  @brief Body(const vector<Predicate>& p) - Body class Constructor using a vector of predicates
//  @param p - reference to a vector of predicates 
	Body(const vector<Predicate>& p);

//  @brief Body(const Body& b) - Body class Copy Constructor
//  @param b - reference to a body instance
	Body(const Body& b);

//  @brief predicates(vector<Predicate>& p)  - Setter method for the Body predicates
//  @param p - reference to a vector of predicates
	void predicates(vector<Predicate>& p);

//  @brief predicates()  - Getter method for the Body predicates
//  @return p - vector of predicates	
	vector<Predicate> predicates() const;

//  @brief size()  - Returns the size of the vector of predicates that means the number of predicates
//  @return int - size of the vector
	int size() const;

//  @brief print(ostream & output)  - Prints all the predicates in the vector according to the grammar syntax
//  @param output - ostream
	void print(ostream & = cout) const; 

//  @brief fill_symbol_table(SymbolTable & table)  - Fills out a Symbol Table with tokens from the predicates and their symbols (variables and constants)
//  @param table - SymbolTable 
	void fill_symbol_table(SymbolTable & table) const;

};

#endif
/**
	PredicatesContainer.h
	Class name: PredicatesContainer 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the class PredicatesContainer that is inherited by Head and Body
*/

#ifndef PREDICATES_CONTAINER_H
#define PREDICATES_CONTAINER_H

#include <vector>
#include "Predicate.h"
#include <ostream>
#include <iostream>
#include <memory>

using namespace std;

class PredicatesContainer
{
protected:
// Vector with one or more predicates
	vector<Predicate> _predicates; 
public:
// @brief PredicatesContainer class Constructor using a vector of predicates
// @param p - reference to a vector of predicates 
	PredicatesContainer(const vector<Predicate>& p);

// @brief PredicatesContainer class Copy Constructor
// @param b - reference to a predicatecontainer instance
	PredicatesContainer(const PredicatesContainer& b);

// @brief Setter method for the PredicatesContainer predicates
// @param p - reference to a vector of predicates
	void predicates(vector<Predicate>& p);

// @brief Getter method for the PredicatesContainer predicates
// @return p - vector of predicates	
	vector<Predicate> predicates() const;

// @brief Returns the size of the vector of predicates that means the number of predicates
// @return int - size of the vector
	int size() const;

// @brief Prints all the predicates in the vector according to the grammar syntax
// @param output - ostream
	void print(ostream & = cout) const; 

// @brief Fills out a Symbol Table with tokens from the predicates and their symbols (variables and constants)
// @param table - SymbolTable 
	void fill_symbol_table(SymbolTable & table);

};

#endif
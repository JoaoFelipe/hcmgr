/**
	Body.cpp
	Class name: Body 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the class Body for the grammar
			    body -> LEFTPAREN predicate {predicate} RIGHTPAREN
*/

#include "stdafx.h"
#include "Body.h"
#include "const.h"
#include "Predicate.h"

// @brief Body class Constructor using a vector of predicates
// @param p - reference to a vector of predicates 
Body::Body(const vector<Predicate>& p): _predicates(p) {}

// @brief Body class Copy Constructor
// @param b - reference to a body instance
Body::Body(const Body& b) : _predicates(b._predicates) {}

// @brief Setter method for the Body predicates
// @param p - reference to a vector of predicates
void Body::predicates(vector<Predicate>& p) {
	_predicates = p;
}

// @brief Getter method for the Body predicates
// @return p - vector of predicates
vector<Predicate> Body::predicates() const {
	return _predicates;
}

// @brief Returns the size of the vector of predicates that means the number of predicates
// @return int - size of the vector
int Body::size() const {
	return _predicates.size();
}

// @brief Prints all the predicates in the vector according to the grammar syntax
// @param output - ostream
void Body::print(ostream & output) const {
	output << LEFTPAREN;
	for (vector<Predicate>::const_iterator i = _predicates.begin(); i != _predicates.end(); ++i) {
		if (i != _predicates.begin()) {
			output << " ";
		}
		i->print(output);
	}
	output << RIGHTPAREN;
}

// @brief Fills out a Symbol Table with tokens from the predicates and their symbols (variables and constants)
// @param table - SymbolTable 
void Body::fill_symbol_table(SymbolTable & table) const {
	for (vector<Predicate>::const_iterator i = _predicates.begin(); i != _predicates.end(); ++i) {
		i->fill_symbol_table(table);
	}
}
/**
	PredicatesContainer.cpp
	Class name: PredicatesContainer 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the class PredicatesContainer that is inherited by Head and Body
*/

#include "stdafx.h"
#include "PredicatesContainer.h"
#include "const.h"
#include "Predicate.h"

// @brief PredicatesContainer class Constructor using a vector of predicates
// @param p - reference to a vector of predicates 
PredicatesContainer::PredicatesContainer(const vector<Predicate>& p): _predicates(p) {}

// @brief PredicatesContainer class Copy Constructor
// @param b - reference to a PredicatesContainer instance
PredicatesContainer::PredicatesContainer(const PredicatesContainer& b) : _predicates(b._predicates) {}

// @brief Setter method for the PredicatesContainer predicates
// @param p - reference to a vector of predicates
void PredicatesContainer::predicates(vector<Predicate>& p) {
	_predicates = p;
}

// @brief Getter method for the PredicatesContainer predicates
// @return p - vector of predicates
vector<Predicate> PredicatesContainer::predicates() const {
	return _predicates;
}

// @brief Returns the size of the vector of predicates that means the number of predicates
// @return int - size of the vector
int PredicatesContainer::size() const {
	return _predicates.size();
}

// @brief Prints all the predicates in the vector according to the grammar syntax
// @param output - ostream
void PredicatesContainer::print(ostream & output) const {
	for (vector<Predicate>::const_iterator i = _predicates.begin(); i != _predicates.end(); ++i) {
		if (i != _predicates.begin()) {
			output << " ";
		}
		i->print(output);
	}
}

// @brief Fills out a Symbol Table with tokens from the predicates and their symbols (variables and constants)
// @param table - SymbolTable 
void PredicatesContainer::fill_symbol_table() {
	for (vector<Predicate>::iterator i = _predicates.begin(); i != _predicates.end(); ++i) {
		i->fill_symbol_table();
	}
}

bool PredicatesContainer::is_valid() {
	for (vector<Predicate>::iterator i = _predicates.begin(); i != _predicates.end(); ++i) {
		if (!i->is_valid()) {
			return false;
		}
	}
	return true;
}
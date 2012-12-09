/**
	Body.cpp
	Class name: Body 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the class Body for the grammar
			    body -> LEFTPAREN predicate {predicate} RIGHTPAREN
*/

#include "stdafx.h"
#include "Body.h"
#include "const.h"
#include "Predicate.h"

// @brief Body class Constructor using a vector of predicates
// @param p - reference to a vector of predicates 
Body::Body(const vector<Predicate>& p): PredicatesContainer(p) {}

// @brief Body class Copy Constructor
// @param b - reference to a body instance
Body::Body(const Body& b) : PredicatesContainer(b) {}

// @brief Prints all the predicates in the vector according to the grammar syntax
// @param output - ostream
void Body::print(ostream & output) const {
	output << LEFTPAREN;
	PredicatesContainer::print(output);
	output << RIGHTPAREN;
}

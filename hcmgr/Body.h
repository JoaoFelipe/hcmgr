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
#include "PredicatesContainer.h"
#include <ostream>
#include <iostream>
#include <memory>

using namespace std;

class Body: public PredicatesContainer
{
public:
// @brief Body class Constructor using a vector of predicates
// @param p - reference to a vector of predicates 
	Body(const vector<Predicate>& p);

// @brief Body class Copy Constructor
// @param b - reference to a body instance
	Body(const Body& b);

// @brief Prints all the predicates in the vector according to the grammar syntax
// @param output - ostream
	void print(ostream & = cout) const; 
};

#endif
/**
	Head.h
	Class name: Head 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the class Head for the grammar
			    head -> predicate
*/

#ifndef HEAD_H
#define HEAD_H

#include "Predicate.h"
#include "PredicatesContainer.h"
#include <ostream>
#include <iostream>
#include <memory>
using namespace std;

class Head: public PredicatesContainer
{
public:

// @brief Head class Constructor using a predicate parameter
// @param p - reference to a predicate 
	Head(const Predicate& p);

// @brief Head class Copy Constructor
// @param h - reference to another head
	Head(const Head& h);
 
// @brief Setter to the Head predicate
// @param p - reference to a predicate
	void predicate(const Predicate& p);
	
// @brief Getter to the Head predicate
// @return Predicate
	Predicate predicate() const;

};

#endif
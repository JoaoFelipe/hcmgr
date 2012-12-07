/**
	Head.cpp
	Class name: Head 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the class Head for the grammar
			    head -> predicate
*/

#include "stdafx.h"
#include "Head.h"
#include <vector>


// @brief Head class Constructor using a predicate parameter
// @param p - reference to a predicate 
Head::Head(const Predicate& p) : PredicatesContainer(vector<Predicate>()) {
	PredicatesContainer::_predicates.push_back(p);
}

// @brief Head class Copy Constructor
// @param h - reference to another head
Head::Head(const Head& h): PredicatesContainer(h){}

// @brief Setter to the Head predicate
// @param p - reference to a predicate
void Head::predicate(const Predicate& p) {
	PredicatesContainer::_predicates[0] = p;
}

// @brief Getter to the Head predicate
// @return Predicate
Predicate Head::predicate() const {
	return PredicatesContainer::_predicates[0];
}

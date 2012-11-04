/**
	Name.cpp
	Class name: Name 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the Name for the grammar
			    name -> LABEL
*/

#include "stdafx.h"
#include "Name.h"

// @brief Name class Constructor using a value string parameter
// @param v - reference to a string value
Name::Name(const string& v): _value(v) {}

// @brief Name class Copy Constructor
// @param n - reference to a name
Name::Name(const Name& n) : _value(n._value) {}

// @brief Setter method to the Name value
// @param v - reference to a string value
void Name::value(const string& v) {
	_value = v;
}

// @brief Getter method to the Name value
// @return string
string Name::value() const {
	return _value;
}

// @brief Prints the Name value according to the grammar syntax
// @param output - ostream
void Name::print(ostream & output) const {
	output << _value;
}
/**
	Name.h
	Class name: Name 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the Name for the grammar
			    name -> LABEL
*/

#ifndef NAME_H
#define NAME_H

#include <string>
#include <ostream>
#include <iostream>
#include <memory>
using namespace std;

class Name
{
private:
// Value of the Name
    string _value;
public:

// @brief Name class Constructor using a value string parameter
// @param v - reference to a string value
    Name(const string& v);

// @brief Name class Copy Constructor
// @param n - reference to a name
	Name(const Name& n);
 
// @brief Setter method to the Name value
// @param v - reference to a string value
    void value(const string& v);

// @brief Getter method to the Name value
// @return string
    string value() const;
	
// @brief Prints the Name value according to the grammar syntax
// @param output - ostream
	void print(ostream & = cout) const; 
};


#endif
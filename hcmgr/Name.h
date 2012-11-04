/**
	Name.h
	Class name: Name 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the Name for the grammar
			    name -> LABEL
*/

#ifndef NAME_H
#define NAME_H

#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class Name
{
private:
// Value of the Name
    string _value;
public:

//  @brief Name(const string& v) - Name class Constructor using a value string parameter
//  @param v - reference to a string value
    Name(const string& v);

//  @brief Name(const Name& n) - Name class Copy Constructor
//  @param n - reference to a name
	Name(const Name& n);
 
//  @brief value(const string& v) - Setter method to the Name value
//  @param v - reference to a string value
    void value(const string& v);

//  @brief value() - Getter method to the Name value
//  @return string
    string value() const;
	
//  @brief print(ostream & output)  - Prints the Name value according to the grammar syntax
//  @param output - ostream
	void print(ostream & = cout) const; 
};


#endif
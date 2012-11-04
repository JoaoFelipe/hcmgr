/**
	Symbol.h
	Class name: Symbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the Symbol  for the grammar
				symbol -> LABEL | NUMBER
*/

#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>
#include "SymbolTableEntry.h"

using namespace std;

class Symbol
{
private:
// Value of the Symbol
	string _value;
public:

//  @brief Symbol(const string& v) - Symbol class Constructor using a value reference as parameter 
//  @param v - reference to string value	
    Symbol(const string& v);
	
//  @brief Symbol(const Symbol& s) - Symbol class Copy Constructor 
//  @param s - reference to another Symbol		
	Symbol(const Symbol& s);

//  @brief value(const string& v) - Setter to the Symbol value 
//  @param v - reference to string value	
    void value(const string& v);

//  @brief value() - Getter to the Symbol value 
//  @return string 	
    string value() const;

//  @brief text() - Returns a text with the type and value of the Symbol 
//  @return string 
	string text() const;

//  @brief print(ostream & output)  - Prints the Symbol according to the grammar syntax
//  @param output - ostream
	void print(ostream & = cout) const; 

//  @brief Symbol::convertToSymbolTableEntry()  - Converts the Symbol to a SymbolTableEntry
//  @return SymbolTableEntry
	SymbolTableEntry * convertToSymbolTableEntry() const;
};
 

#endif
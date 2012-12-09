/**
	FunctionSymbol.h
	Class name: FunctionSymbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the function -> LEFTBRACKET operator term term RIGHTBRACKET 

*/

#ifndef FUNCTION_SYMBOL_H
#define FUNCTION_SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>
#include "Symbol.h"
#include "SymbolTable.h"
#include <memory>

using namespace std;

class FunctionSymbol: public Symbol
{
private:
// Value of the Symbol
	string _operation;
	string _term1;
	string _term2;
public:

// @brief FunctionSymbol class Constructor using three references as parameter 
// @param oper - reference to string value	
// @param term1 - reference to string value	
// @param term2 - reference to string value	
    FunctionSymbol(const string& oper, const string& term1, const string& term2);
	
// @brief FunctionSymbol class Copy Constructor 
// @param s - reference to another FunctionSymbol		
	FunctionSymbol(const FunctionSymbol& s);

// @brief Returns a clone of the Symbol
// @return shared_ptr<Symbol>
	virtual shared_ptr<Symbol> clone() const;

// @brief Setter to the FunctionSymbol operation 
// @param operation - reference to string operation	
    void operation(const string& operation);

// @brief Getter to the FunctionSymbol operation 
// @return string 	
    string operation() const;

// @brief Setter to the FunctionSymbol term1 
// @param term1 - reference to string term1	
    void term1(const string& term1);

// @brief Getter to the FunctionSymbol term1 
// @return string 	
    string term1() const;

// @brief Setter to the FunctionSymbol term2 
// @param v - reference to string term2	
    void term2(const string& term2);

// @brief Getter to the FunctionSymbol term2 
// @return string 	
    string term2() const;

// @brief Returns a text with the type and value of the Symbol 
// @return string 
	virtual string text() const;

// @brief Prints the Symbol according to the grammar syntax
// @param output - ostream
	virtual void print(ostream & = cout) const; 

// @brief Converts the Symbol to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
	virtual shared_ptr<SymbolTableEntry> convertToSymbolTableEntry() const;

// @brief Get a list of SymbolTableEntry that can be added in the table
// @return vector<shared_ptr<SymbolTableEntry>>
	virtual vector<shared_ptr<SymbolTableEntry>> getRealSymbolTableEntry() const;
};
 

#endif
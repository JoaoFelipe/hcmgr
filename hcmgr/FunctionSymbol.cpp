/**
	FunctionSymbol.cpp
	Class name: FunctionSymbol 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the UNBOUND
*/

#include "stdafx.h"
#include "FunctionSymbol.h"
#include "string_utils.h"
#include "ConstantEntry.h"
#include "BoundEntry.h"
#include <iostream>
#include <sstream>
#include "SymbolTable.h"
#include "const.h"
#include "FunctionEntry.h"
#include "TermSymbol.h"
#include "string_utils.h"

// @brief FunctionSymbol class Constructor using three references as parameter 
// @param oper - reference to string value	
// @param term1 - reference to string value	
// @param term2 - reference to string value	
FunctionSymbol::FunctionSymbol(const string& oper, const string& term1, const string& term2)
	: _operation(oper), _term1(term1), _term2(term2) {}

// @brief FunctionSymbol class Copy Constructor 
// @param s - reference to another FunctionSymbol		
FunctionSymbol::FunctionSymbol(const FunctionSymbol& s)
	: _operation(s._operation), _term1(s._term1), _term2(s._term2) {}


// @brief Returns a clone of the Symbol
// @return shared_ptr<Symbol>
shared_ptr<Symbol> FunctionSymbol::clone() const {
	return shared_ptr<Symbol>(new FunctionSymbol(*this));
}

// @brief Setter to the FunctionSymbol operation 
// @param operation - reference to string operation	
void FunctionSymbol::operation(const string& operation) {
	_operation = operation;
}

// @brief Getter to the FunctionSymbol operation 
// @return string 	
string FunctionSymbol::operation() const {
	return _operation;
}


// @brief Setter to the FunctionSymbol term1 
// @param term1 - reference to string term1	
void FunctionSymbol::term1(const string& term1) {
	_term1 = term1;
}

// @brief Getter to the FunctionSymbol term1 
// @return string 	
string FunctionSymbol::term1() const {
	return _term1;
}


// @brief Setter to the FunctionSymbol term2 
// @param term2 - reference to string term2	
void FunctionSymbol::term2(const string& term2) {
	_term2 = term2;
}

// @brief Getter to the FunctionSymbol term2 
// @return string 	
string FunctionSymbol::term2() const {
	return _term2;
}

// @brief Returns a text with the type and value of the Symbol 
// @return string 
string FunctionSymbol::text() const {
	string temp = "[" + _operation + " " + _term1 + " " + _term2 + "]";
	return temp;
}

// @brief Prints the Symbol according to the grammar syntax
// @param output - ostream
void FunctionSymbol::print(ostream & output) const {
	output << text();
}

// @brief Converts the Symbol to a SymbolTableEntry
// @param SymbolTable
// @return shared_ptr<SymbolTableEntry>
shared_ptr<SymbolTableEntry> FunctionSymbol::convertToSymbolTableEntry(SymbolTable & table) const {
	TermSymbol temp_term1(_term1);
	TermSymbol temp_term2(_term2);
	shared_ptr<SymbolValueEntry> term1 = dynamic_pointer_cast<SymbolValueEntry>(temp_term1.convertToSymbolTableEntry(table));
	shared_ptr<SymbolValueEntry> term2 = dynamic_pointer_cast<SymbolValueEntry>(temp_term2.convertToSymbolTableEntry(table));
	return shared_ptr<SymbolTableEntry>(new FunctionEntry(_operation, term1, term2));
}

// @brief Get a list of SymbolTableEntry that can be added in the table
// @return vector<shared_ptr<SymbolTableEntry>> 
vector<shared_ptr<SymbolTableEntry>> FunctionSymbol::getRealSymbolTableEntry() const {
	vector<shared_ptr<SymbolTableEntry>> result;
	TermSymbol temp_term1(_term1);
	TermSymbol temp_term2(_term2);
	result.push_back(temp_term1.getRealSymbolTableEntry()[0]);
	result.push_back(temp_term2.getRealSymbolTableEntry()[0]);
	return result;
}


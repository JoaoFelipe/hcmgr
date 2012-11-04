
/**
	SymbolTableEntry.cpp
	Class name: SymbolTableEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the SymbolTableEntry as superclass of the tokens representations in the SymbolTable
*/


#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "VariableEntry.h"
#include "ConstantEntry.h"
#include "PredicateEntry.h"
#include "string_utils.h"


using namespace std;

// @brief Compares the current SymbolTableEntry to another SymbolTableEntry 
// @param other - references to another SymbolTableEntry
bool SymbolTableEntry::operator==(const SymbolTableEntry & other) const {
	return text() == other.text() && type() == other.type();
}

// @brief Compares the current SymbolTableEntry text to a text given as parameter 
// @param t - references to a text string ('type:text' format)
bool SymbolTableEntry::equals(const string& t) const {
	string temp = type() + ":";
	temp += text();
	return (t == temp);
}




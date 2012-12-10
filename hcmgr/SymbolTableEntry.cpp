
/**
	SymbolTableEntry.cpp
	Class name: SymbolTableEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the SymbolTableEntry as superclass of the tokens representations in the SymbolTable
*/


#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "BoundEntry.h"
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

// @brief Returns printable text of the SymbolTableEntry name and values
// @return string 		
string SymbolTableEntry::printable_text() const {
	string temp = type() + ": ";
	temp += text();
	return temp;
}

// @brief Returns true if a SymbolTableEntry is a Predicate
// @return bool 
bool SymbolTableEntry::is_predicate() const {
	return false;
}

// @brief Returns true if a SymbolTableEntry is a constant
// @return bool 
bool SymbolTableEntry::is_constant() const {
	return false;
}

// @brief Returns true if a SymbolTableEntry is a bound
// @return bool 
bool SymbolTableEntry::is_bound() const {
	return false;
}

// @brief Returns true if a SymbolTableEntry is a function
// @return bool 
bool SymbolTableEntry::is_function() const {
	return false;
}

// @brief Returns true if a SymbolTableEntry is a unbound
// @return bool 
bool SymbolTableEntry::is_unbound() const {
	return false;
}

// @brief Checks if the Symbol can be evaluated
// @return bool
bool SymbolTableEntry::is_evaluable() const {
	return false;
}

// @brief Check if it is a valid symbol. May fail for function symbol
// @return bool	
bool SymbolTableEntry::is_valid() const {
	return true;
}


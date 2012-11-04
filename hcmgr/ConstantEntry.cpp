/**
	ConstantEntry.cpp
	Class name: ConstantEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the class ConstantEntry to represent a numeric symbol (constant) in the SymbolTable

*/


#include "stdafx.h"
#include "ConstantEntry.h"
#include <iostream>
#include <sstream>

using namespace std;

//  @brief ConstantEntry(const unsigned int v) - ConstantEntry class Constructor passing a value parameter
//  @param v - value of the ConstantEntry
ConstantEntry::ConstantEntry(const unsigned int v): _value(v) {}

//  @brief ConstantEntry(const ConstantEntry & other) - ConstantEntry class Copy Constructor
//  @param other - reference to other ConstantEntry 
ConstantEntry::ConstantEntry(const ConstantEntry & other): _value(other._value) {}

//  @brief clone() - Create a copy of the current ConstantEntry 
//  @return SymbolTableEntry - clone 
SymbolTableEntry * ConstantEntry::clone() const {
	return new ConstantEntry(*this);
}

//  @brief operator==(const ConstantEntry & other) - Compares current ConstantEntry value with a ConstantEntry parameter value
//  @param bool - returns true if they have same value  
bool ConstantEntry::operator==(const ConstantEntry & other) const {
	return _value == other._value;
}

//  @brief type() - Returns the name of the ConstantEntry type according to the grammar (Constant)
//  @param string - name of the type  
string ConstantEntry::type() const {
	return "Constant";
}

//  @brief text() - Returns a string of the ConstantEntry value
//  @param string - value in string  
string ConstantEntry::text() const {
	ostringstream convert;
	convert << _value;
	return convert.str();
}

//  @brief is_constant() - Returns true if the ConstantEntry value is constant
//  @param bool  
bool ConstantEntry::is_constant() const {
	return true;
}

//  @brief is_variable() - Returns true if the ConstantEntry value is variable
//  @param bool
bool ConstantEntry::is_variable() const {
	return false;
}
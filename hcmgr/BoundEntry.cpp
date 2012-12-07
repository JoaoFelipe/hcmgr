
/**
	BoundEntry.cpp
	Class name: BoundEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the BoundEntry to represent Variables in the SymbolTable
*/

#include "stdafx.h"
#include "BoundEntry.h"
#include "ConstantEntry.h"


// @brief  BoundEntry class Constructor using a label string reference as parameter 
// @param l - reference to string value as label	
BoundEntry::BoundEntry(const string & l): _label(l), _value(0) {}

// @brief BoundEntry class Copy Constructor 
// @param other - reference to another BoundEntry
BoundEntry::BoundEntry(const BoundEntry & other): _label(other._label), _value(other._value) {}

// @brief Returns the clone of the BoundEntry
// @return SymbolTableEntry
shared_ptr<SymbolTableEntry> BoundEntry::clone() const {
	return shared_ptr<SymbolTableEntry>(new BoundEntry(*this));
}

// @brief Converts the current value to a constant
// @return shared_ptr<SymbolTableEntry> 
shared_ptr<SymbolTableEntry> BoundEntry::get_constant_value() const {
	return shared_ptr<SymbolTableEntry>(new ConstantEntry(this->value()));
}

// @brief Compares the current BoundEntry to another BoundEntry 
// @param other - references to another BoundEntry
// @return bool - returns true if they hava same label
bool BoundEntry::operator==(const BoundEntry & other) const {
	return _label == other._label;
}

// @brief Returns the name of the BoundEntry type
// @return string - name of the BoundEntry type 		
string BoundEntry::type() const {
	return "Bound";
}

// @brief Returns BoundEntry label
// @return string
string BoundEntry::text() const {
	return _label;
}


// @brief Get the value of the Symbol
// @return int
int BoundEntry::value() const {
	return _value;
}

// @brief Set the value of the Bound
// @param int
void BoundEntry::value(int value) {
	_value = value;
}



// @brief Returns true if the entry is bound
// @return bool
bool BoundEntry::is_bound() const {
	return true;
}

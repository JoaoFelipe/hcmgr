
/**
	UnboundEntry.cpp
	Class name: UnboundEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the UnboundEntry to represent Variables in the SymbolTable
*/

#include "stdafx.h"
#include "UnboundEntry.h"

// @brief  UnboundEntry class Constructor using a label string reference as parameter 
// @param l - reference to string value as label	
UnboundEntry::UnboundEntry(const string & l): _label(l) {}

// @brief UnboundEntry class Copy Constructor 
// @param other - reference to another UnboundEntry
UnboundEntry::UnboundEntry(const UnboundEntry & other): _label(other._label) {}

// @brief Returns the clone of the UnboundEntry
// @return SymbolTableEntry
shared_ptr<SymbolTableEntry> UnboundEntry::clone() const {
	return shared_ptr<SymbolTableEntry>(new UnboundEntry(*this));
}

// @brief Compares the current UnboundEntry to another UnboundEntry 
// @param other - references to another UnboundEntry
// @return bool - returns true if they hava same label
bool UnboundEntry::operator==(const UnboundEntry & other) const {
	return _label == other._label;
}

// @brief Returns the name of the UnboundEntry type
// @return string - name of the UnboundEntry type 		
string UnboundEntry::type() const {
	return "Unbound";
}

// @brief Returns UnboundEntry label
// @return string
string UnboundEntry::text() const {
	return _label;
}

// @brief Returns true if the entry is unbound
// @return bool
bool UnboundEntry::is_unbound() const {
	return true;
}


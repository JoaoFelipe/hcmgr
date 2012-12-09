
/**
	BoundEntry.h
	Class name: BoundEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the BoundEntry to represent Variables in the SymbolTable
*/


#ifndef BOUND_ENTRY_H
#define BOUND_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolValueEntry.h"
#include <string>
#include <memory>

using namespace std;

class BoundEntry : public SymbolValueEntry {
public:
// @brief BoundEntry class Constructor using a label string reference as parameter 
// @param l - reference to string value as label	
	BoundEntry(const string & l);

// @brief BoundEntry class Copy Constructor 
// @param other - reference to another BoundEntry
	BoundEntry(const BoundEntry & other);

// @brief Returns the clone of the BoundEntry
// @return SymbolTableEntry
	virtual shared_ptr<SymbolTableEntry> clone() const;

// @brief Converts the current value to a constant
// @return shared_ptr<SymbolTableEntry> 
	virtual shared_ptr<SymbolTableEntry> get_constant_value() const;

// @brief Compares the current BoundEntry to another BoundEntry 
// @param other - references to another BoundEntry
// @return bool - returns true if they hava same label
	bool operator==(const BoundEntry & other) const;

// @brief Returns the name of the BoundEntry type
// @return string - name of the BoundEntry type 	
	virtual string type() const;

// @brief Returns BoundEntry label
// @return string
	virtual string text() const;

// @brief Get the value of the Symbol
// @return int
	virtual int value() const;

// @brief Set the value of the Bound
// @param int
	void value(int value);


// @brief Returns true if the entry is bound
// @return bool
	virtual bool is_bound() const;

private:
	


// Label of the BoundEntry
	string _label;
	int _value;
};

#endif

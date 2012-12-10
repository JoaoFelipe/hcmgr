/**
	UnboundEntry.h
	Class name: UnboundEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the UnboundEntry to represent Variables in the SymbolTable
*/


#ifndef UNBOUND_ENTRY_H
#define UNBOUND_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include <string>
#include <memory>
using namespace std;

class UnboundEntry : public SymbolEntry {
public:

// @brief UnboundEntry class Constructor using a label string reference as parameter 
// @param l - reference to string value as label	
	UnboundEntry(const string & l);

// @brief UnUnboundEntry class Copy Constructor 
// @param other - reference to another UnUnboundEntry
	UnboundEntry(const UnboundEntry & other);

// @brief Returns the clone of the UnboundEntry
// @return shared_ptr<SymbolTableEntry>
	virtual shared_ptr<SymbolTableEntry> clone() const;

// @brief Compares the current UnboundEntry to another UnboundEntry 
// @param other - references to another UnboundEntry
// @return bool - returns true if they hava same label
	bool operator==(const UnboundEntry & other) const;

// @brief Returns the name of the UnboundEntry type
// @return string - name of the UnboundEntry type 	
	virtual string type() const;

// @brief Returns UnboundEntry label
// @return string
	virtual string text() const;

// @brief Returns true if the entry is unbound
// @return bool
	virtual bool is_unbound() const;

private:
// Label of the UnboundEntry
	string _label;
};

#endif

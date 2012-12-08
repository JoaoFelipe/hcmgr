
/**
	FunctionEntry.cpp
	Class name: FunctionEntry
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the FunctionEntry to represent Variables in the SymbolTable
*/

#include "stdafx.h"
#include "FunctionEntry.h"
#include "operations_utils.h"
#include "ConstantEntry.h"
#include "const.h"
#include <sstream>
#include <iostream>

// @brief  FunctionEntry class Constructor using a label string reference as parameter 
// @param l - reference to string value as label	
FunctionEntry::FunctionEntry(const string & operation, shared_ptr<SymbolValueEntry> term1, shared_ptr<SymbolValueEntry> term2)
	: _operation(operation), _term1(term1), _term2(term2) {}

// @brief FunctionEntry class Copy Constructor 
// @param other - reference to another FunctionEntry
FunctionEntry::FunctionEntry(const FunctionEntry & other)
	: _operation(other._operation), _term1(other._term1), _term2(other._term2) {}

// @brief Returns the clone of the UnboundEntry
// @return shared_ptr<SymbolTableEntry>
shared_ptr<SymbolTableEntry> FunctionEntry::clone() const {
	return shared_ptr<SymbolTableEntry>(new FunctionEntry(*this));
}

// @brief Converts the current value to a constant
// @return shared_ptr<SymbolTableEntry> 
shared_ptr<SymbolTableEntry> FunctionEntry::get_constant_value() const {
	try {
		return shared_ptr<SymbolTableEntry>(new ConstantEntry(this->value()));
	} catch (int i) {
		if (i == DIVIDE_BY_ZERO_ERROR) {
			return shared_ptr<SymbolTableEntry>();
		}
		throw i;
	}
}

// @brief Compares the current UnboundEntry to another UnboundEntry 
// @param other - references to another UnboundEntry
// @return bool - returns true if they hava same label
bool FunctionEntry::operator==(const FunctionEntry & other) const {
	return (_operation == other._operation) && 
			(_term1 == other._term1) &&
			(_term2 == other._term2);
}

// @brief Returns the name of the FunctionEntry type
// @return string - name of the FunctionEntry type 		
string FunctionEntry::type() const {
	return "Function";
}

// @brief Returns FunctionEntry text
// @return string
string FunctionEntry::text() const {
	return "["+_operation +" "+ _term1->text() + " " + _term2->text() +  "]";
}

// @brief Get the value of the Symbol
// @return int
int FunctionEntry::value() const {
	return operation(_operation, _term1->value(), _term2->value());
}

// @brief Returns true if the entry is function
// @return bool
bool FunctionEntry::is_function() const {
	return true;
}

// @brief Returns the modified symbols with the substitutions after the unification 
// @return string - symbols after substitutions 		
string FunctionEntry::unification(SubstitutionList & substitution_list) const {
	try {
		ostringstream convert;
		convert << this->value();
		return convert.str();
	} catch (int i) {
		if (i == DIVIDE_BY_ZERO_ERROR) {
			return text();
		}
		throw i;
	}
}

bool FunctionEntry::is_valid() const {
	try {
		this->value();
		return true;
	} catch (int i) {
		if (i == DIVIDE_BY_ZERO_ERROR) {
			return false;
		}
		throw i;
	}
}

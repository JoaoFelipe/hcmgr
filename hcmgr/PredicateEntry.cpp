/**
	PredicateEntry.cpp
	Class name: PredicateEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the PredicateEntry to represent the Predicate in the SymbolTable
*/

#include "stdafx.h"
#include "PredicateEntry.h"
#include "const.h"
#include "UnboundEntry.h"
#include "Parser.h"
#include <sstream>
#include <iostream>


// @brief PredicateEntry class Constructor
// @param symbols - reference to a vector<SymbolTableEntry *>	
PredicateEntry::PredicateEntry(string & name, vector<shared_ptr<SymbolTableEntry>>& symbols) : _name(name), _symbols(symbols){}

// @brief PredicateEntry class Copy Constructor 
// @param other - references to another PredicateEntry
PredicateEntry::PredicateEntry(const PredicateEntry & other): _name(other._name), _symbols(other._symbols) {}

// @brief Returns a clone of the current PredicateEntry as a SymbolTableEntry 
// @return SymbolTableEntry 
shared_ptr<SymbolTableEntry> PredicateEntry::clone() const {
	return shared_ptr<SymbolTableEntry>(new PredicateEntry(*this));
}

// @brief Compares the current PredicateEntry to another PredicateEntry 
// @param other - references to another PredicateEntry
bool PredicateEntry::operator==(const PredicateEntry & other) const {
	if (_name != other._name || _symbols.size() != other._symbols.size()) {
		return false;
	}
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		if (_symbols[i] != other._symbols[i]) {
			return false;
		}
	}
	return true;
}

// @brief Getter method for the PredicateEntry name
// @return string - PredicateEntry name		
string PredicateEntry::name() const {
	return _name;
}


// @brief Returns the name of PredicateEntry type
// @return string - name of the PredicateEntry type 		
string PredicateEntry::type() const {
	return "Predicate";
}

// @brief Returns PredicateEntry name followed by its symbols
// @return string 		
string PredicateEntry::text() const {
	string result = _name;
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		result += " ";
		result += _symbols[i]->text();
	}
	return result;
}

// @brief Returns true if a SymbolTableEntry is a Predicate
// @return bool 		
bool PredicateEntry::is_predicate() const {
	return true;
}


// @brief Returns true if the PredicateEnry matches with other PredicateEntry
// @return bool 		
bool PredicateEntry::matches(shared_ptr<SymbolTableEntry> other, SubstitutionList & substitution_list) const {
	if (!other->is_predicate()) {
		return false;
	}
	shared_ptr<PredicateEntry> otherp = dynamic_pointer_cast<PredicateEntry>(other);

	if (_name != otherp->_name || _symbols.size() != otherp->_symbols.size()) {
		return false;
	}

	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		shared_ptr<SymbolTableEntry> ci_value = substitution_list.find_value(_symbols[i]);
		shared_ptr<SymbolTableEntry> oi_value = substitution_list.find_value(otherp->_symbols[i]);
		shared_ptr<SymbolTableEntry> ci = substitution_list.find_non_null(_symbols[i]);
		shared_ptr<SymbolTableEntry> oi = substitution_list.find_non_null(otherp->_symbols[i]);
		if (!ci_value || !oi_value) {
			//semantic error
			return false;
		}

		if (!(*ci_value == *oi_value)) {
			if (ci_value->is_constant() && oi_value->is_constant()) {
				return false;
			} 

			if (!ci_value->is_constant()) {
				substitution_list.add(ci, oi);
			} else { //!oi->is_constant()
				substitution_list.add(oi, ci);
			}
		} 
	}
	return true;
}

// @brief Returns the modified predicate with the substitutions after the unification 
// @return string - predicate after substitutions 		
string PredicateEntry::unification(SubstitutionList & substitution_list) const {
	string result = _name;
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		result += " ";
		result += _symbols[i]->unification(substitution_list);
	}
	return result;
}


shared_ptr<Predicate> PredicateEntry::substitute(SubstitutionList & substitution_list) const {
	vector<shared_ptr<SymbolTableEntry>> symbols;
	for (auto i = _symbols.begin(); i != _symbols.end(); ++i) {
		symbols.push_back(substitution_list.find_value(*i));
	}
	PredicateEntry p(string(_name), symbols);
	ostringstream s;
	s << "(" << p.text() << ")";
	Parser parser(s.str());

	return parser.parse_predicate();
}

bool PredicateEntry::is_valid() const {
	for (auto i = _symbols.begin(); i != _symbols.end(); ++i) {
		if (!(*i)->is_valid()) {
			return false;
		}
	}
	return true;
}



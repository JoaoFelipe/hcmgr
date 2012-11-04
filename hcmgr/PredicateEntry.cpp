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

//  @brief PredicateEntry(const Predicate & p, const SymbolTable & table) - PredicateEntry class Constructor using a Predicate and SymbolTable references as parameters 
//  @param p, table - references to a Predicate and SymbolTable	
PredicateEntry::PredicateEntry(const Predicate & p, const SymbolTable & table): _name(p.name().value()), _symbols()  {
	vector<Symbol> symbols = p.symbols();
	for (vector<Symbol>::iterator i = symbols.begin(); i != symbols.end(); ++i) {
		SymbolTableEntry * sym = table.find(i->text());
		if (sym != NONE) {
			_symbols.push_back(sym);
		}
	}

}

//  @brief PredicateEntry(const PredicateEntry & other) - PredicateEntry class Copy Constructor 
//  @param other - references to another PredicateEntry
PredicateEntry::PredicateEntry(const PredicateEntry & other): _name(other._name), _symbols(other._symbols) {}

//  @brief clone() - Returns a clone of the current PredicateEntry as a SymbolTableEntry 
//  @return SymbolTableEntry 
SymbolTableEntry * PredicateEntry::clone() const {
	return new PredicateEntry(*this);
}

//  @brief operator==(const PredicateEntry & other)- Compares the current PredicateEntry to another PredicateEntry 
//  @param other - references to another PredicateEntry
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

//  @brief name()  - Getter method for the PredicateEntry name
//  @return string - PredicateEntry name		
string PredicateEntry::name() const {
	return _name;
}


//  @brief type()  - Returns the name of PredicateEntry type
//  @return string - name of the PredicateEntry type 		
string PredicateEntry::type() const {
	return "Predicate";
}

//  @brief text()  - Returns PredicateEntry name followed by its symbols
//  @return string 		
string PredicateEntry::text() const {
	string result = _name;
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		result += " ";
		result += _symbols[i]->text();
	}
	return result;
}

//  @brief is_predicate()  - Returns true if a SymbolTableEntry is a Predicate
//  @return bool 		
bool PredicateEntry::is_predicate() const {
	return true;
}

//  @brief is_constant()  - Returns true if a SymbolTableEntry is a constant
//  @return bool 		
bool PredicateEntry::is_constant() const {
	return false;
}

//  @brief is_variable()  - Returns true if a SymbolTableEntry is a variable
//  @return bool 		
bool PredicateEntry::is_variable() const {
	return false;
}


//  @brief matches(SymbolTableEntry * other, SubstitutionList & substitution_list)  - Returns true if the PredicateEnry matches with other PredicateEntry
//  @return bool 		
bool PredicateEntry::matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const {
	if (!other->is_predicate()) {
		return false;
	}
	PredicateEntry * otherp = dynamic_cast<PredicateEntry *>(other);

	if (_name != otherp->_name || _symbols.size() != otherp->_symbols.size()) {
		return false;
	}

	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		SymbolTableEntry * ci = substitution_list.find(_symbols[i]);
		if (ci == NONE) {
			ci = _symbols[i];
		}
		SymbolTableEntry * oi = substitution_list.find(otherp->_symbols[i]);
		if (oi == NONE) {
			oi = otherp->_symbols[i];
		}
		if (ci != oi) {
			if (ci->is_constant() && oi->is_constant()) {
				return false;
			}
			if (ci->is_variable() && oi->is_variable() || ci->is_variable() && oi->is_constant()) {
				substitution_list.add(ci, oi);
			} else { // (ci->is_constant() && oi->is_variable())
				substitution_list.add(oi, ci);
			}
		}
	}
	return true;
}

//  @brief unification(SubstitutionList & substitution_list)  - Returns the modified predicate with the substitutions after the unification 
//  @return string - predicate after substitutions 		
string PredicateEntry::unification(SubstitutionList & substitution_list) const {
	string result = _name;
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		result += " ";
		SymbolTableEntry * ci = substitution_list.find(_symbols[i]);
		if (ci == NONE) {
			ci = _symbols[i];
			result += ci->text();
		} else {
			result += ci->text() + "/";
			result += _symbols[i]->text();
		}
	}
	return result;
}

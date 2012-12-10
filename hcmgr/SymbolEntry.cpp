/**
	SymbolEntry.cpp
	Class name: SymbolEntry 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the SymbolEntry to represent a Symbol in the SymbolTable
*/

#include "stdafx.h"
#include "SymbolEntry.h"
#include "SymbolValueEntry.h"
#include "const.h"

// @brief Returns true if the current SymbolTableEntry matches with other SymbolTableEntry
// @return bool 		
bool SymbolEntry::matches(shared_ptr<SymbolTableEntry> other, SubstitutionList & substitution_list) const {
	if (other->is_predicate()) {
		return false;
	}

	shared_ptr<const SymbolTableEntry> super = dynamic_pointer_cast<const SymbolTableEntry>(shared_ptr<const SymbolEntry>(this, null_deleter()));
	//const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);

	shared_ptr<SymbolTableEntry> os_value = substitution_list.find_value(other);	
	if (!os_value) {
		//semantic error
		return false;
	}
	shared_ptr<SymbolTableEntry> ts_value = substitution_list.find(super);
	if (!ts_value) {
		if (super->is_evaluable()){
			shared_ptr<const SymbolValueEntry> cv = dynamic_pointer_cast<const SymbolValueEntry>(super);
			ts_value = cv->get_constant_value();
			if (!ts_value) {
				//semantic error
				return false;
			} 
		} else {
			return true;
		}
	}
	if (ts_value->is_unbound() || os_value->is_unbound()) {
		return true;
	}
	return (*ts_value == *os_value);
}

// @brief Returns the modified symbols with the substitutions after the unification 
// @return string - symbols after substitutions 		
string SymbolEntry::unification(SubstitutionList & substitution_list) const {
	shared_ptr<const SymbolTableEntry> super = dynamic_pointer_cast<const SymbolTableEntry>(shared_ptr<const SymbolEntry>(this, null_deleter()));
	//const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);
	shared_ptr<SymbolTableEntry> ts = substitution_list.find(super);
	if (!ts) {
		if (super->is_evaluable()){
			shared_ptr<const SymbolValueEntry> cv = dynamic_pointer_cast<const SymbolValueEntry>(super);
			ts = cv->get_constant_value();
			if (!ts) {
				return text();
			} 

		} else {
			return text();
		}
	} else {
		if (ts->is_evaluable()){
			shared_ptr<SymbolValueEntry> cv = dynamic_pointer_cast<SymbolValueEntry>(ts);
			ts = cv->get_constant_value();
			if (!ts) {
				return text();
			} 
		}
		
	}
	string result;
	if (!is_constant()) {
		result += ts->text() + "/";
	}
	result += text();
	return result;
}


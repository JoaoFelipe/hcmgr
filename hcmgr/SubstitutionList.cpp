/**
	SubstitutionList.cpp
	Class name: SubstitutionList 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the SubstitutionList to search and store equivalent symbols for the unification
*/

#include "stdafx.h"
#include "SubstitutionList.h"
#include "SymbolTableEntry.h"
#include "SymbolValueEntry.h"
#include "const.h"

// @brief SubstitutionList class Default Constructor 
SubstitutionList::SubstitutionList(): _substitutions() {}

// @brief Searches a SynbolTableEntry in the SubstitutionList
// @param entry - reference to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry> - Returns the substitution entry or NONE if it doesn't find a substitution
shared_ptr<SymbolTableEntry> SubstitutionList::find(shared_ptr<const SymbolTableEntry> entry) const {
	shared_ptr<SymbolTableEntry> current = shared_ptr<SymbolTableEntry>();
	for (vector<pair<shared_ptr<SymbolTableEntry>, shared_ptr<SymbolTableEntry>>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		if (*entry == *i->first) {
			current = i->second;
			break;
		}
	}
	if (current) {
		shared_ptr<SymbolTableEntry> again = find(current);
		if (!again) {
			return current;
		} else {
			return again;
		}
	}
	return shared_ptr<SymbolTableEntry>();
}

// @brief Searches a SynbolTableEntry in the SubstitutionList and returns itself if not found. For functions and bound, returns the evalueted value in ConstantEntry
// @param entry - reference to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
shared_ptr<SymbolTableEntry> SubstitutionList::find_non_null(shared_ptr<SymbolTableEntry> entry) const {
	shared_ptr<SymbolTableEntry> ci = this->find(entry);
	if (!ci) {
		ci = entry;
	}
	return ci;
}


// @brief Searches a SynbolTableEntry in the SubstitutionList and returns itself if not found. For functions and bound, returns the evalueted value in ConstantEntry
// @param entry - reference to a SymbolTableEntry
// @return shared_ptr<SymbolTableEntry>
shared_ptr<SymbolTableEntry> SubstitutionList::find_value(shared_ptr<SymbolTableEntry> entry) const {
	shared_ptr<SymbolTableEntry> ci = this->find_non_null(entry);
	if (ci->is_evaluable()){
		shared_ptr<SymbolValueEntry> cv = dynamic_pointer_cast<SymbolValueEntry>(ci);
		ci = cv->get_constant_value();
		if (!ci) {
			return shared_ptr<SymbolTableEntry>();
		} 
	}
	return ci;
}

// @brief Add a valid pair of entries to the substitution list
// @param first, second - references to the first and second values of the pair - the second is a substitute for the first
void SubstitutionList::add(shared_ptr<SymbolTableEntry> first, shared_ptr<SymbolTableEntry> second) {
	_substitutions.push_back(pair<shared_ptr<SymbolTableEntry>, shared_ptr<SymbolTableEntry>>(first, second));
}


// @brief Prints the pairs of the Substitution List
// @param output - ostream
void SubstitutionList::print(ostream & output) const {
	for (vector<pair<shared_ptr<SymbolTableEntry>, shared_ptr<SymbolTableEntry>>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		output << "  " << i->second->text() << "/" << i->first->text() << endl;
	}
}

void SubstitutionList::add_all(SubstitutionList & other) {
	for (vector<pair<shared_ptr<SymbolTableEntry>, shared_ptr<SymbolTableEntry>>>::const_iterator i = other._substitutions.begin(); i != other._substitutions.end(); ++i) {
		if (!find(i->first)) {
			add(i->first, i->second);
		}
	}
}
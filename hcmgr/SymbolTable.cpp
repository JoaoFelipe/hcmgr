/**
	SymbolTable.cpp
	Class name: SymbolTable 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the SymbolTable to manage the entries
*/


#include "stdafx.h"
#include "SymbolTable.h"
#include "SymbolEntry.h"
#include "PredicateEntry.h"
#include "const.h"

using namespace std;


// @brief SymbolTable class default Constructor 	
SymbolTable::SymbolTable(): _entries() {}

// @brief Add an entry to the SymbolTable 
// @param entry - shared_ptr<SymbolTableEntry>
// @return bool - returns true if it is possible to add (no duplicate entry) 
bool SymbolTable::add(shared_ptr<SymbolTableEntry> entry) {
	string temp = entry->type() + ":";
	temp += entry->text();

	if (find(temp) == 0) {
		shared_ptr<SymbolTableEntry> copy = entry->clone();
		_entries.push_back(copy);
		return true;
	} 
	return false;
}

// @brief Seaches if a value exists in the entries 
// @param value - string value for the entry
// @return shared_ptr<SymbolTableEntry> - returns the SymbolTableEntry for the value, or NONE if not found
shared_ptr<SymbolTableEntry> SymbolTable::find(const string & value) const {
	for (vector<shared_ptr<SymbolTableEntry>>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->equals(value)) {
			return *i;
		}
	}
	return shared_ptr<SymbolTableEntry>();
}

// @brief Prints the SymbolTable entries
// @param output - ostream
void SymbolTable::print(ostream & output) const {
	for (vector<shared_ptr<SymbolTableEntry>>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		output << (*i)->printable_text() << endl;
	}
}

// @brief Prints entries predicates
// @param output - ostream
void SymbolTable::print_predicates(ostream & output) const {
	for (vector<shared_ptr<SymbolTableEntry>>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->is_predicate()) {
			output << (*i)->text() << endl;
		}
	}
}

// @brief Prints the SymbolTable status after unifications (substitutions)
// @param output - ostream
void SymbolTable::unifications(ostream & output) const {
	for (vector<shared_ptr<SymbolTableEntry>>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->is_predicate()) {
			for (vector<shared_ptr<SymbolTableEntry>>::const_iterator j = _entries.begin(); j != _entries.end(); ++j) {
				if ((*j)->is_predicate() && i != j) {
					shared_ptr<PredicateEntry> pi = dynamic_pointer_cast<PredicateEntry>(*i);
					shared_ptr<PredicateEntry> pj = dynamic_pointer_cast<PredicateEntry>(*j);
					if (pi->name() == pj->name()) {
						SubstitutionList substs;
						if ((*i)->matches(*j, substs)) {
							output << "(" << (*i)->text() << ") matches (" << (*j)->text() << ")" << endl;
							substs.print();
							output << "  Unification (" << (*i)->unification(substs) << ") matches (" << (*j)->unification(substs) << ")" << endl << endl;
						} else {
							output << "(" << (*i)->text() << ") doesn't match (" << (*j)->text() << ")" << endl << endl;
						}
					}
				}
			}
		}
	}
}

// @brief instantiate the SymbolTable and returns an instance of it
shared_ptr<SymbolTable> SymbolTable::instance() {
	if (!_instance) {
		_instance = shared_ptr<SymbolTable>(new SymbolTable());
	}
	return _instance;
}

// @brief Erases the SymbolTable
void SymbolTable::erase() {
	_entries = vector<shared_ptr<SymbolTableEntry>>();
}

// @brief Backup current entries
void SymbolTable::backup() {
	_back_state = _entries;
}

// @brief Restore current entries
void SymbolTable::restore() {
	_entries = _back_state;
}

// Set initial singleton value as null
shared_ptr<SymbolTable> SymbolTable::_instance = shared_ptr<SymbolTable>();
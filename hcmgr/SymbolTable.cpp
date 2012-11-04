/**
	SymbolTable.cpp
	Class name: SymbolTable 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the SymbolTable to manage the entries
*/


#include "stdafx.h"
#include "SymbolTable.h"
#include "SymbolEntry.h"
#include "PredicateEntry.h"
#include "const.h"

using namespace std;


//  @brief SymbolTable() - SymbolTable class default Constructor 	
SymbolTable::SymbolTable(): _entries() {}

//  @brief ~SymbolTable() - SymbolTable class Destructor 
SymbolTable::~SymbolTable() {
	for (vector<SymbolTableEntry *>::iterator i = _entries.begin(); i != _entries.end(); ++i) {
		delete *i;
	}
}

//  @brief add(SymbolTableEntry * entry) - Add an entry to the SymbolTable 
//  @param entry - references to a SymbolTableEntry
//  @return bool - returns true if it is possible to add (no duplicate entry) 
bool SymbolTable::add(SymbolTableEntry * entry) {
	string temp = entry->type() + ":";
	temp += entry->text();

	if (find(temp) == 0) {
		SymbolTableEntry * copy = entry->clone();
		_entries.push_back(copy);
		return true;
	} 
	return false;
}

//  @brief find(const string & value) - Seaches if a value exists in the entries 
//  @param value - string value for the entry
//  @return SymbolTableEntry - returns the SymbolTableEntry for the value, or NONE if not found
SymbolTableEntry * SymbolTable::find(const string & value) const {
	for (vector<SymbolTableEntry *>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->equals(value)) {
			return *i;
		}
	}
	return NONE;
}

//  @brief print(ostream & output)  - Prints the SymbolTable entries
//  @param output - ostream
void SymbolTable::print(ostream & output) const {
	for (vector<SymbolTableEntry *>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		output << (*i)->type() << ": " << (*i)->text() << endl;
	}
}

//  @brief print(ostream & output)  - Prints entries predicates
//  @param output - ostream
void SymbolTable::print_predicates(ostream & output) const {
	for (vector<SymbolTableEntry *>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->is_predicate()) {
			output << (*i)->text() << endl;
		}
	}
}

//  @brief unifications(ostream & output)  - Prints the SymbolTable status after unifications (substitutions)
//  @param output - ostream
void SymbolTable::unifications(ostream & output) const {
	for (vector<SymbolTableEntry *>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->is_predicate()) {
			for (vector<SymbolTableEntry *>::const_iterator j = _entries.begin(); j != _entries.end(); ++j) {
				if ((*j)->is_predicate() && i != j) {
					PredicateEntry * pi = dynamic_cast<PredicateEntry *>(*i);
					PredicateEntry * pj = dynamic_cast<PredicateEntry *>(*j);
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
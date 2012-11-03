#include "stdafx.h"
#include "SymbolTable.h"
#include "SymbolEntry.h"
#include "PredicateEntry.h"
//#include "SubstitutionList.h"

using namespace std;

SymbolTable::SymbolTable(): _entries() {}

SymbolTable::~SymbolTable() {
	for (vector<SymbolTableEntry *>::iterator i = _entries.begin(); i != _entries.end(); ++i) {
		delete *i;
	}
}

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

SymbolTableEntry * SymbolTable::find(const string & value) const {
	for (vector<SymbolTableEntry *>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->equals(value)) {
			return *i;
		}
	}
	return 0;
}

void SymbolTable::print(ostream & output) const {
	for (vector<SymbolTableEntry *>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		output << (*i)->type() << ": " << (*i)->text() << endl;
	}
}

void SymbolTable::print_predicates(ostream & output) const {
	for (vector<SymbolTableEntry *>::const_iterator i = _entries.begin(); i != _entries.end(); ++i) {
		if ((*i)->is_predicate()) {
			output << (*i)->text() << endl;
		}
	}
}

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
							output << "(" << (*i)->text() << ") doens't match (" << (*j)->text() << ")" << endl << endl;
						}
					}
				}
			}
		}
	}
}
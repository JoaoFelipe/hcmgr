
#include "stdafx.h"
#include "SubstitutionList.h"
#include "SymbolTableEntry.h"
#include "const.h"

SubstitutionList::SubstitutionList(): _substitutions() {}

SymbolTableEntry * SubstitutionList::find(const SymbolTableEntry * entry) const {
	SymbolTableEntry * current = NONE;
	for (vector<pair<SymbolTableEntry *, SymbolTableEntry *>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		if (i->first == entry) {
			current = i->second;
			break;
		}
	}
	if (current != NONE) {
		SymbolTableEntry * again = find(current);
		if (again == NONE) {
			return current;
		} else {
			return again;
		}
	}
	return NONE;
}

void SubstitutionList::add(SymbolTableEntry * first, SymbolTableEntry * second) {
	_substitutions.push_back(pair<SymbolTableEntry *, SymbolTableEntry *>(first, second));
}

void SubstitutionList::print(ostream & output) const {
	for (vector<pair<SymbolTableEntry *, SymbolTableEntry *>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		output << "  " << i->second->text() << "/" << i->first->text() << endl;
	}
}
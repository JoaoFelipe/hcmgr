
#include "stdafx.h"
#include "SubstitutionList.h"
#include "SymbolTableEntry.h"

SubstitutionList::SubstitutionList(): _substitutions() {}

SymbolTableEntry * SubstitutionList::find(const SymbolTableEntry * entry) const {
	SymbolTableEntry * current = 0;
	for (vector<pair<SymbolTableEntry *, SymbolTableEntry *>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		if (i->first == entry) {
			current = i->second;
			break;
		}
	}
	if (current != 0) {
		SymbolTableEntry * again = find(current);
		if (again == 0) {
			return current;
		} else {
			return again;
		}
	}
	return 0;
}

void SubstitutionList::add(SymbolTableEntry * first, SymbolTableEntry * second) {
	_substitutions.push_back(pair<SymbolTableEntry *, SymbolTableEntry *>(first, second));
}

void SubstitutionList::print(ostream & output) const {
	for (vector<pair<SymbolTableEntry *, SymbolTableEntry *>>::const_iterator i = _substitutions.begin(); i != _substitutions.end(); ++i) {
		output << "  " << i->second->text() << "/" << i->first->text() << endl;
	}
}
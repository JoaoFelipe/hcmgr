#include "stdafx.h"
#include "SymbolTable.h"


SymbolTable::SymbolTable(): _entries() {}

SymbolTable::~SymbolTable() {
	for (set<SymbolTableEntry *>::iterator i = _entries.begin(); i != _entries.end(); ++i) {
		delete *i;
	}
}


bool SymbolTable::add(SymbolTableEntry * entry) {
	SymbolTableEntry * copy = entry->clone();
	bool added = _entries.insert(entry).second;
	return added;
}
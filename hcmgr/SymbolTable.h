#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <set>
#include "SymbolTableEntry.h"

using namespace std;

class SymbolTable {
public:
	SymbolTable();
	~SymbolTable();
	bool add(SymbolTableEntry * entry);
private:
	set<SymbolTableEntry *> _entries;
};

#endif
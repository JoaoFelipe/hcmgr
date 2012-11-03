#ifndef SYMBOL_TABLE_ENTRY_H
#define SYMBOL_TABLE_ENTRY_H

#include "stdafx.h"
#include <string>

using namespace std;

class SymbolTableEntry {
public:
	virtual SymbolTableEntry * clone() const = 0;
	bool operator==(const SymbolTableEntry & other) const;
};

#endif

SymbolTableEntry * symbolToSymbolTableEntry(string & symbol);
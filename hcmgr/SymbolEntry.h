#ifndef SYMBOL_ENTRY_H
#define SYMBOL_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include <string>

using namespace std;

class SymbolEntry : public SymbolTableEntry {
public:
	virtual SymbolTableEntry * clone() const = 0;
};

#endif

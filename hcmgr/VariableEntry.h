#ifndef VARIABLE_ENTRY_H
#define VARIABLE_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include <string>

using namespace std;

class VariableEntry : public SymbolEntry {
public:
	VariableEntry(string & l);
	virtual SymbolTableEntry * clone() const;
	bool operator==(const VariableEntry & other) const;
private:
	string _label;
};

#endif

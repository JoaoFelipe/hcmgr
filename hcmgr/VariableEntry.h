#ifndef VARIABLE_ENTRY_H
#define VARIABLE_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include <string>

using namespace std;

class VariableEntry : public SymbolEntry {
public:
	VariableEntry(const string & l);
	VariableEntry(const VariableEntry & other);
	virtual SymbolTableEntry * clone() const;
	bool operator==(const VariableEntry & other) const;
	virtual string type() const;
	virtual string text() const;
	virtual bool is_variable() const;
	virtual bool is_constant() const;
private:
	string _label;
};

#endif

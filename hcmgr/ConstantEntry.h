#ifndef CONSTANT_ENTRY_H
#define CONSTANT_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include <string>

using namespace std;

class ConstantEntry : public SymbolEntry {
public:
	ConstantEntry(unsigned int v);
	virtual SymbolTableEntry * clone() const;
	bool operator==(const ConstantEntry & other) const;
private:
	unsigned int _value;
};

#endif
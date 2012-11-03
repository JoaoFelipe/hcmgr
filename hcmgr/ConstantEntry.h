#ifndef CONSTANT_ENTRY_H
#define CONSTANT_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include <string>

using namespace std;

class ConstantEntry : public SymbolEntry {
public:
	ConstantEntry(const unsigned int v);
	ConstantEntry(const ConstantEntry & other);
	virtual SymbolTableEntry * clone() const;
	bool operator==(const ConstantEntry & other) const;
	virtual string type() const;
	virtual string text() const;
	virtual bool is_variable() const;
	virtual bool is_constant() const;
private:
	unsigned int _value;
};

#endif
#ifndef SYMBOL_TABLE_ENTRY_H
#define SYMBOL_TABLE_ENTRY_H

#include "stdafx.h"
#include <string>

using namespace std;

class SubstitutionList;

class SymbolTableEntry {
public:
	virtual SymbolTableEntry * clone() const = 0;
	
	virtual string type() const = 0;
	virtual string text() const = 0;

	virtual bool operator==(const SymbolTableEntry & other) const;
	virtual bool equals(const string& text) const;

	virtual bool is_predicate() const = 0;
	virtual bool is_constant() const = 0;
	virtual bool is_variable() const = 0;
	virtual bool matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const = 0;
	virtual string unification(SubstitutionList & substitution_list) const = 0;
};



#endif


#ifndef SYMBOL_ENTRY_H
#define SYMBOL_ENTRY_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "SubstitutionList.h"
#include <string>

using namespace std;

class SymbolEntry : public SymbolTableEntry {
public:
	virtual SymbolTableEntry * clone() const = 0;
	virtual bool is_predicate() const;
	virtual bool SymbolEntry::matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const;
	virtual string SymbolEntry::unification(SubstitutionList & substitution_list) const;
};

#endif

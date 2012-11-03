#ifndef PREDICATE_ENTRY_H
#define PREDICATE_ENTRY_H

#include "stdafx.h"
#include "SymbolTable.h"
#include "SymbolTableEntry.h"
#include "SymbolEntry.h"
#include "SubstitutionList.h"
#include "Predicate.h"
#include <string>
#include <vector>

using namespace std;

class PredicateEntry : public SymbolTableEntry {
public:
	PredicateEntry(const Predicate & p, const SymbolTable & table);
	PredicateEntry(const PredicateEntry & other);
	virtual SymbolTableEntry * clone() const;
	bool operator==(const PredicateEntry & other) const;
	string PredicateEntry::name() const;
	virtual string type() const;
	virtual string text() const;
	virtual bool is_predicate() const;
	virtual bool is_variable() const;
	virtual bool is_constant() const;
	virtual bool matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const;
	virtual string unification(SubstitutionList & substitution_list) const;

private:
	string _name;
	vector<SymbolTableEntry *> _symbols;
};

#endif
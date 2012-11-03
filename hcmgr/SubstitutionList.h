#ifndef SUBSTITUTION_LIST_H
#define SUBSTITUTION_LIST_H

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

class SubstitutionList {
public:
	SubstitutionList();
	SymbolTableEntry * find(const SymbolTableEntry * entry) const;
	void add(SymbolTableEntry * first, SymbolTableEntry * second);
	void print(ostream & output=cout) const;

private:
	vector<pair<SymbolTableEntry *, SymbolTableEntry *>> _substitutions;

};

#endif

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <vector>
#include "SymbolTableEntry.h"
#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class SymbolTable {
public:
	SymbolTable();
	~SymbolTable();
	bool add(SymbolTableEntry * entry);
	SymbolTableEntry * find(const string & value) const;
	void SymbolTable::print(ostream & output=cout) const;
	void SymbolTable::print_predicates(ostream & output=cout) const;
	void SymbolTable::unifications(ostream & output=cout) const;
private:
	vector<SymbolTableEntry *> _entries;
};

#endif
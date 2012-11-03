#ifndef PREDICATE_H
#define PREDICATE_H

#include <vector>
#include "Name.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include <ostream>
#include <iostream>

class Predicate
{
private:
	Name _name;
	vector<Symbol> _symbols; 
public:
    Predicate(const Name& n, const vector<Symbol>& s);
	Predicate(const Predicate& p);

    void name(const Name& n);
	void symbols(const vector<Symbol>& s);
    Name name() const;
	vector<Symbol> symbols() const;

	void fill_symbol_table(SymbolTable & table) const;

	void print(ostream & = cout) const; 
};



#endif

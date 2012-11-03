#ifndef PREDICATE_H
#define PREDICATE_H

#include <vector>
#include "Name.h"
#include "Symbol.h"
#include <ostream>
#include <iostream>

class Predicate
{
private:
	Name _name;
	vector<Symbol> _symbols; 
public:
    Predicate(Name& n, vector<Symbol>& s);
	Predicate(const Predicate& p);

    void name(Name& n);
	void symbols(vector<Symbol>& s);
    Name& name();
	vector<Symbol>& symbols();

	void print(ostream & = cout) const; 
};



#endif

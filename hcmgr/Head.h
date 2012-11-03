#ifndef HEAD_H
#define HEAD_H

#include "Predicate.h"
#include <ostream>
#include <iostream>

using namespace std;

class Head
{
private:
	Predicate _predicate; 
public:
    Head(const Predicate& p);
	Head(const Head& h);
 
	void predicate(const Predicate& p);
 	Predicate predicate() const;

	void fill_symbol_table(SymbolTable & table) const;

	void print(ostream & = cout) const; 
};

#endif
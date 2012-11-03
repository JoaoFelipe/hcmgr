#ifndef BODY_H
#define BODY_H

#include <vector>
#include "Predicate.h"
#include <ostream>
#include <iostream>

using namespace std;

class Body
{
private:
	vector<Predicate> _predicates; 
public:
    Body(const vector<Predicate>& p);
	Body(const Body& b);
 
	void predicates(vector<Predicate>& p);
 	vector<Predicate> predicates() const;

	void fill_symbol_table(SymbolTable & table) const;

	int size() const;

	void print(ostream & = cout) const; 
};

#endif
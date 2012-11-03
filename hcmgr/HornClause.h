#ifndef HORN_CLAUSE_H
#define HORN_CLAUSE_H

#include <vector>
#include "body.h"
#include "head.h"
#include "SymbolTable.h"
#include <ostream>
#include <iostream>

using namespace std;

class HornClause
{
private:
	Head _head;
	Body * _body;  
public:
	HornClause(const Head & h);
	HornClause(const Head & h, const Body & b);
	HornClause(const HornClause & hc);
	~HornClause();
	HornClause & operator=(const HornClause & other);

	void fill_symbol_table(SymbolTable & table) const;

	void head(const Head & h);
 	Head head() const;

	void body(const Body & b);
 	Body body() const;

	void print(ostream & = cout) const; 

};

#endif
#ifndef HORN_CLAUSE_H
#define HORN_CLAUSE_H

#include <vector>
#include "body.h"
#include "head.h"
#include <ostream>
#include <iostream>

using namespace std;

class HornClause
{
private:
	Head _head;
	Body * _body;  
public:
	HornClause(Head & h);
	HornClause(Head & h, Body & b);
	HornClause(const HornClause & hc);
	~HornClause();
	HornClause & operator= (HornClause & other);

	void head(Head & h);
 	Head & head();

	void body(Body & b);
 	Body & body();

	void print(ostream & = cout) const; 

};

#endif
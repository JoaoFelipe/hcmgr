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
    Body(vector<Predicate>& p);
	Body(Body& b);
 
	void predicates(vector<Predicate>& p);
 	vector<Predicate>& predicates();

	int size() const;

	void print(ostream & = cout) const; 
};

#endif
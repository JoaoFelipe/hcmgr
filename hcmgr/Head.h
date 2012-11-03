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
    Head(Predicate& p);
	Head(const Head& h);
 
	void predicate(Predicate& p);
 	Predicate& predicate();

	void print(ostream & = cout) const; 
};

#endif
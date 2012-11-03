#include "stdafx.h"
#include "Head.h"

Head::Head(Predicate& p) : _predicate(p) {}
Head::Head(const Head& h): _predicate(h._predicate){}

void Head::predicate(Predicate& p) {
	_predicate = p;
}

Predicate& Head::predicate() {
	return _predicate;
}

void Head::print(ostream & output) const {
	_predicate.print(output);
}
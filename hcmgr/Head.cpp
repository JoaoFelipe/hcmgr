#include "stdafx.h"
#include "Head.h"

Head::Head(const Predicate& p) : _predicate(p) {}
Head::Head(const Head& h): _predicate(h._predicate){}

void Head::predicate(const Predicate& p) {
	_predicate = p;
}

Predicate Head::predicate() const {
	return _predicate;
}

void Head::print(ostream & output) const {
	_predicate.print(output);
}

void Head::fill_symbol_table(SymbolTable & table) const {
	_predicate.fill_symbol_table(table);
}
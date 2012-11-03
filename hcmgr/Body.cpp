#include "stdafx.h"
#include "Body.h"
#include "const.h"
#include "Predicate.h"

Body::Body(const vector<Predicate>& p): _predicates(p) {}
Body::Body(const Body& b) : _predicates(b._predicates) {}
 
void Body::predicates(vector<Predicate>& p) {
	_predicates = p;
}

vector<Predicate> Body::predicates() const {
	return _predicates;
}

int Body::size() const {
	return _predicates.size();
}

void Body::print(ostream & output) const {
	output << LEFTPAREN;
	for (vector<Predicate>::const_iterator i = _predicates.begin(); i != _predicates.end(); ++i) {
		if (i != _predicates.begin()) {
			output << " ";
		}
		i->print(output);
	}
	output << RIGHTPAREN;
}

void Body::fill_symbol_table(SymbolTable & table) const {
	for (vector<Predicate>::const_iterator i = _predicates.begin(); i != _predicates.end(); ++i) {
		i->fill_symbol_table(table);
	}
}
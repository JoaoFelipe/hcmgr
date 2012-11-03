#include "stdafx.h"
#include "Body.h"
#include "const.h"

Body::Body(vector<Predicate>& p): _predicates(p) {}
Body::Body(Body& b) : _predicates(b._predicates) {}
 
void Body::predicates(vector<Predicate>& p) {
	_predicates = p;
}

vector<Predicate>& Body::predicates() {
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
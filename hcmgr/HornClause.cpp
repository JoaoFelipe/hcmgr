#include "stdafx.h"
#include "HornClause.h"
#include "const.h"

HornClause::HornClause(Head & h): _head(h), _body(0) {}

HornClause::HornClause(Head & h, Body & b): _head(h), _body(new Body(b)) {}

HornClause::HornClause(const HornClause & hc): _head(hc._head), _body(new Body(*hc._body)){}

HornClause & HornClause::operator= (HornClause & other) {
	if (this != &other) {
		head(other.head());
		body(other.body());
	}
	return *this;
}

HornClause::~HornClause() {
	delete _body;
}

void HornClause::head(Head & h) {
	_head = h;
}

Head & HornClause::head() {
	return _head;
}

void HornClause::body(Body & b) {
	delete _body;
	_body = new Body(b);
}

Body & HornClause::body() {
	return *_body;
}

void HornClause::print(ostream & output) const {
	output << LEFTPAREN;
	_head.print(output);
	if (_body != 0) {
		output << " ";
		_body->print(output);
	}
	output << RIGHTPAREN;
}
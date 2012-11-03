#include "stdafx.h"
#include "HornClause.h"
#include "const.h"

HornClause::HornClause(const Head & h): _head(h), _body(0) {}

HornClause::HornClause(const Head & h, const Body & b): _head(h), _body(new Body(b)) {}

HornClause::HornClause(const HornClause & hc): _head(hc._head), _body(new Body(*hc._body)){}

HornClause & HornClause::operator=(const HornClause & other) {
	if (this != &other) {
		head(other.head());
		body(other.body());
	}
	return *this;
}

HornClause::~HornClause() {
	delete _body;
}

void HornClause::head(const Head & h) {
	_head = h;
}

Head HornClause::head() const {
	return _head;
}

void HornClause::body(const Body & b) {
	delete _body;
	_body = new Body(b);
}

Body HornClause::body() const {
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

void HornClause::fill_symbol_table(SymbolTable & table) const{
	_head.fill_symbol_table(table);
	if (_body != 0) {
		_body->fill_symbol_table(table);
	}
}
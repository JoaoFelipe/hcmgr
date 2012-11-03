#include "stdafx.h"
#include "Predicate.h"
#include "const.h"

Predicate::Predicate(Name& n, vector<Symbol>& s): _name(n), _symbols(s) {}

Predicate::Predicate(const Predicate& p) :_name(p._name), _symbols(p._symbols){}

void Predicate::name(Name& n) {
	_name = n;
}

void Predicate::symbols(vector<Symbol>& s) {
	_symbols = s;
}

Name& Predicate::name() {
	return _name;
}

vector<Symbol>& Predicate::symbols() {
	return _symbols;
}

void Predicate::print(ostream & output) const {
	output << LEFTPAREN;
	_name.print();
	for (vector<Symbol>::const_iterator i = _symbols.begin(); i != _symbols.end(); ++i) {
		output << " ";
		i->print(output);
	}
	output << RIGHTPAREN;

}
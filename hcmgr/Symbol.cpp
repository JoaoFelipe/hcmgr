#include "stdafx.h"
#include "Symbol.h"

Symbol::Symbol(string& v): _value(v) {}
Symbol::Symbol(const Symbol& s): _value(s._value) {}

void Symbol::value(string& v) {
	_value = v;
}

string& Symbol::value() {
	return _value;
}

void Symbol::print(ostream & output) const {
	output << _value;
}
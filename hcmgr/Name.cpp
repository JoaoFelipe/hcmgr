#include "stdafx.h"
#include "Name.h"

Name::Name(string& v): _value(v) {}
Name::Name(const Name& n) : _value(n._value) {}

void Name::value(string& v) {
	_value = v;
}

string& Name::value() {
	return _value;
}

void Name::print(ostream & output) const {
	output << _value;
}
#include "stdafx.h"
#include "Symbol.h"
#include "string_utils.h"
#include "ConstantEntry.h"
#include "VariableEntry.h"
#include <iostream>
#include <sstream>

Symbol::Symbol(const string& v): _value(v) {}
Symbol::Symbol(const Symbol& s): _value(s._value) {}

void Symbol::value(const string& v) {
	_value = v;
}

string Symbol::value() const {
	return _value;
}

string Symbol::text() const {
	if (check_string(_value, is_number)) {
		string temp = "Constant:" + _value;
		return temp;
	} else {
		string temp = "Variable:" + _value;
		return temp;
	}
}


void Symbol::print(ostream & output) const {
	output << _value;
}

SymbolTableEntry * Symbol::convertToSymbolTableEntry() const {
	if (check_string(_value, is_number)) {
		unsigned int value;
		istringstream str(_value);
		str >> value;
		return new ConstantEntry(value);
	} else {
		return new VariableEntry(_value);
	}
}

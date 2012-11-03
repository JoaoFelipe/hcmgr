#include "stdafx.h"
#include "ConstantEntry.h"
#include <iostream>
#include <sstream>

using namespace std;


ConstantEntry::ConstantEntry(const unsigned int v): _value(v) {}
ConstantEntry::ConstantEntry(const ConstantEntry & other): _value(other._value) {}

SymbolTableEntry * ConstantEntry::clone() const {
	return new ConstantEntry(*this);
}

bool ConstantEntry::operator==(const ConstantEntry & other) const {
	return _value == other._value;
}

string ConstantEntry::type() const {
	return "Constant";
}

string ConstantEntry::text() const {
	ostringstream convert;
	convert << _value;
	return convert.str();
}

bool ConstantEntry::is_constant() const {
	return true;
}

bool ConstantEntry::is_variable() const {
	return false;
}
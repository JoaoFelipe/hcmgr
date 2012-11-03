#include "stdafx.h"
#include "ConstantEntry.h"


ConstantEntry::ConstantEntry(unsigned int v): _value(v) {}

SymbolTableEntry * ConstantEntry::clone() const {
	return new ConstantEntry(*this);
}

bool ConstantEntry::operator==(const ConstantEntry & other) const {
	return _value == other._value;
}
#include "stdafx.h"
#include "VariableEntry.h"


VariableEntry::VariableEntry(string & l): _label(l) {}

SymbolTableEntry * VariableEntry::clone() const {
	return new VariableEntry(*this);
}

bool VariableEntry::operator==(const VariableEntry & other) const {
	return _label == other._label;
}
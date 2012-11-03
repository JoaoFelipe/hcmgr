#include "stdafx.h"
#include "VariableEntry.h"


VariableEntry::VariableEntry(const string & l): _label(l) {}
VariableEntry::VariableEntry(const VariableEntry & other): _label(other._label) {}

SymbolTableEntry * VariableEntry::clone() const {
	return new VariableEntry(*this);
}

bool VariableEntry::operator==(const VariableEntry & other) const {
	return _label == other._label;
}

string VariableEntry::type() const {
	return "Variable";
}

string VariableEntry::text() const {
	return _label;
}

bool VariableEntry::is_constant() const {
	return false;
}

bool VariableEntry::is_variable() const {
	return true;
}


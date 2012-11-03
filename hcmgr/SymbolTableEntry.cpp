

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "VariableEntry.h"
#include "ConstantEntry.h"
#include "PredicateEntry.h"
#include "string_utils.h"


using namespace std;

bool SymbolTableEntry::operator==(const SymbolTableEntry & other) const {
	return text() == other.text() && type() == other.type();
}


bool SymbolTableEntry::equals(const string& t) const {
	string temp = type() + ":";
	temp += text();
	return (t == temp);
}




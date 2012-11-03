

#include "stdafx.h"
#include "SymbolTableEntry.h"
#include "VariableEntry.h"
#include "ConstantEntry.h"
#include "string_utils.h"
#include <iostream>
#include <sstream>

using namespace std;

bool SymbolTableEntry::operator==(const SymbolTableEntry & other) const {
//	const 
	return true;
}


SymbolTableEntry * symbolToSymbolTableEntry(string & symbol) {
	if (check_string(symbol, is_number)) {
		unsigned int value;
		istringstream str(symbol);
		str >> value;
		return new ConstantEntry(value);
	} else {
		return new VariableEntry(symbol);
	}

}
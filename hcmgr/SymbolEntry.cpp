#include "stdafx.h"
#include "SymbolEntry.h"
#include "const.h"

bool SymbolEntry::is_predicate() const {
	return false;
}


bool SymbolEntry::matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const {
	if (!other->is_variable() && !other->is_constant()) {
		return false;
	}
	SymbolTableEntry * os = substitution_list.find(other);
	if (os == NONE) {
		os = other;
	}

	const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);

	SymbolTableEntry * ts = substitution_list.find(super);
	if (ts == NONE) {
		return (super == os);
	}
	return (ts == os);
}

string SymbolEntry::unification(SubstitutionList & substitution_list) const {
	const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);
	SymbolTableEntry * ts = substitution_list.find(super);
	if (ts == NONE) {
		return text();
	} else {
		string result = ts->text() + "/";
		result += text();
		return result;
	}
}

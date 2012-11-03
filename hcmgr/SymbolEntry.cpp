#include "stdafx.h"
#include "SymbolEntry.h"

bool SymbolEntry::is_predicate() const {
	return false;
}


bool SymbolEntry::matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const {
	if (!other->is_variable() && !other->is_constant()) {
		return false;
	}
	SymbolTableEntry * os = substitution_list.find(other);
	if (os == 0) {
		os = other;
	}

	const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);

	SymbolTableEntry * ts = substitution_list.find(super);
	if (ts == 0) {
		return (super == os);
	}
	return (ts == os);
}

string SymbolEntry::unification(SubstitutionList & substitution_list) const {
	const SymbolTableEntry * super = dynamic_cast<const SymbolTableEntry *>(this);
	SymbolTableEntry * ts = substitution_list.find(super);
	if (ts == 0) {
		return text();
	} else {
		string result = ts->text() + "/";
		result += text();
	}
}

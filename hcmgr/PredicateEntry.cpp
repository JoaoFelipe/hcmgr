#include "stdafx.h"
#include "PredicateEntry.h"
#include "const.h"


PredicateEntry::PredicateEntry(const Predicate & p, const SymbolTable & table): _name(p.name().value()), _symbols()  {
	vector<Symbol> symbols = p.symbols();
	for (vector<Symbol>::iterator i = symbols.begin(); i != symbols.end(); ++i) {
		SymbolTableEntry * sym = table.find(i->text());
		if (sym != NONE) {
			_symbols.push_back(sym);
		}
	}

}

PredicateEntry::PredicateEntry(const PredicateEntry & other): _name(other._name), _symbols(other._symbols) {}

SymbolTableEntry * PredicateEntry::clone() const {
	return new PredicateEntry(*this);
}

bool PredicateEntry::operator==(const PredicateEntry & other) const {
	if (_name != other._name || _symbols.size() != other._symbols.size()) {
		return false;
	}
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		if (_symbols[i] != other._symbols[i]) {
			return false;
		}
	}
	return true;
}

string PredicateEntry::name() const {
	return _name;
}


string PredicateEntry::type() const {
	return "Predicate";
}

string PredicateEntry::text() const {
	string result = _name;
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		result += " ";
		result += _symbols[i]->text();
	}
	return result;
}

bool PredicateEntry::is_predicate() const {
	return true;
}

bool PredicateEntry::is_constant() const {
	return false;
}

bool PredicateEntry::is_variable() const {
	return false;
}


bool PredicateEntry::matches(SymbolTableEntry * other, SubstitutionList & substitution_list) const {
	if (!other->is_predicate()) {
		return false;
	}
	PredicateEntry * otherp = dynamic_cast<PredicateEntry *>(other);

	if (_name != otherp->_name || _symbols.size() != otherp->_symbols.size()) {
		return false;
	}

	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		SymbolTableEntry * ci = substitution_list.find(_symbols[i]);
		if (ci == NONE) {
			ci = _symbols[i];
		}
		SymbolTableEntry * oi = substitution_list.find(otherp->_symbols[i]);
		if (oi == NONE) {
			oi = otherp->_symbols[i];
		}
		if (ci != oi) {
			if (ci->is_constant() && oi->is_constant()) {
				return false;
			}
			if (ci->is_variable() && oi->is_variable() || ci->is_variable() && oi->is_constant()) {
				substitution_list.add(ci, oi);
			} else { // (ci->is_constant() && oi->is_variable())
				substitution_list.add(oi, ci);
			}
		}
	}
	return true;
}

string PredicateEntry::unification(SubstitutionList & substitution_list) const {
	string result = _name;
	for (unsigned int i = 0; i < _symbols.size(); ++i) {
		result += " ";
		SymbolTableEntry * ci = substitution_list.find(_symbols[i]);
		if (ci == NONE) {
			ci = _symbols[i];
			result += ci->text();
		} else {
			result += ci->text() + "/";
			result += _symbols[i]->text();
		}
	}
	return result;
}

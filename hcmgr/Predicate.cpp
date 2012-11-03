#include "stdafx.h"
#include "Predicate.h"
#include "const.h"
#include "SymbolTableEntry.h"
#include "PredicateEntry.h"


Predicate::Predicate(const Name& n, const vector<Symbol>& s): _name(n), _symbols(s) {}

Predicate::Predicate(const Predicate& p) :_name(p._name), _symbols(p._symbols){}

void Predicate::name(const Name& n) {
	_name = n;
}

void Predicate::symbols(const vector<Symbol>& s) {
	_symbols = s;
}

Name Predicate::name() const {
	return _name;
}

vector<Symbol> Predicate::symbols() const {
	return _symbols;
}

void Predicate::print(ostream & output) const {
	output << LEFTPAREN;
	_name.print();
	for (vector<Symbol>::const_iterator i = _symbols.begin(); i != _symbols.end(); ++i) {
		output << " ";
		i->print(output);
	}
	output << RIGHTPAREN;

}

void Predicate::fill_symbol_table(SymbolTable & table) const {
	for (vector<Symbol>::const_iterator i = _symbols.begin(); i != _symbols.end(); ++i) {
		SymbolTableEntry * symbol_entry = i->convertToSymbolTableEntry();
		table.add(symbol_entry);
		delete symbol_entry;
	}
	SymbolTableEntry * predicate_entry = new PredicateEntry(*this, table);
	if (!table.add(predicate_entry)) {
		cout << "The predicate ";
		this->print();
		cout << " was found in the symbol table. Skipping..." << endl << endl;
	}
	delete predicate_entry;
}
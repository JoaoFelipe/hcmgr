/**
	Predicate.cpp
	Class name: Predicate 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the Predicate for the grammar
				predicate -> LEFTPAREN name {symbol} RIGHTPAREN
*/

#include "stdafx.h"
#include "Predicate.h"
#include "const.h"
#include "SymbolTableEntry.h"
#include "PredicateEntry.h"
#include "string_utils.h"

// @brief Predicate class Constructor using a Name and a vector of Symbols as parameters 
// @param n, s - references to a Name and a vector of Symbols
Predicate::Predicate(const Name& n, const vector<shared_ptr<Symbol>>& s): _name(n), _symbols() {
	for (vector<shared_ptr<Symbol>>::const_iterator i = s.begin(); i != s.end(); ++i) {
		_symbols.push_back((*i)->clone());
	}
}

// @brief Predicate class Copy Constructor
// @param p - reference to another Predicate
Predicate::Predicate(const Predicate& p) :_name(p._name), _symbols(), _predicateEntry(p._predicateEntry){
	for (vector<shared_ptr<Symbol>>::const_iterator i = p._symbols.begin(); i != p._symbols.end(); ++i) {
		_symbols.push_back((*i)->clone());
	}
}


// @brief Setter method for the Predicate Name
// @param n - reference to a Name	
void Predicate::name(const Name& n) {
	_name = n;
}

// @brief Getter method for the Predicate Name
// @return Name - Predicate Name	
Name Predicate::name() const {
	return _name;
}

// @brief Setter method for the vector of Symbols
// @param s - reference to a vector of Symbols	
void Predicate::symbols(const vector<shared_ptr<Symbol>>& s) {
	_symbols = s;
}

// @brief Getter method for the Predicate vector of Symbols
// @return vector<Symbol> - Predicate vector of Symbols	
vector<shared_ptr<Symbol>> Predicate::symbols() const {
	return _symbols;
}

// @brief Prints the Predicate according to the grammar syntax
// @param output - ostream
void Predicate::print(ostream & output) const {
	output << LEFTPAREN;
	_name.print(output);
	for (vector<shared_ptr<Symbol>>::const_iterator i = _symbols.begin(); i != _symbols.end(); ++i) {
		output << " ";
		(*i)->print(output);
	}
	output << RIGHTPAREN;

}


// @brief Checks if the Predicate has the same name and the same number of parameters than other predicate
// @param reference to Predicate
bool Predicate::can_unify(const Predicate & other) const {
	return (_name.value() == other._name.value()) &&
		(_symbols.size() == other._symbols.size());
}



// @brief Fills out a Symbol Table with tokens from the Predicate 
// @param table - SymbolTable 
void Predicate::fill_symbol_table(SymbolTable & table) {
	vector<shared_ptr<SymbolTableEntry>> entries;
	for (vector<shared_ptr<Symbol>>::const_iterator i = _symbols.begin(); i != _symbols.end(); ++i) {
		vector<shared_ptr<SymbolTableEntry>> real_entries = (*i)->getRealSymbolTableEntry();
		for (vector<shared_ptr<SymbolTableEntry>>::iterator j = real_entries.begin(); j != real_entries.end(); ++j) {
			shared_ptr<SymbolTableEntry> sym = table.find(term_with_type((*j)->text()));
			if (!sym) {
				table.add(*j);
			} 
		}
		shared_ptr<SymbolTableEntry> symbol_entry = (*i)->convertToSymbolTableEntry(table);
		entries.push_back(symbol_entry);
	}
	shared_ptr<SymbolTableEntry> predicate_entry = shared_ptr<SymbolTableEntry>(new PredicateEntry(_name.value(), entries));
	if (!table.add(predicate_entry)) {
		cout << "The predicate ";
		this->print();
		cout << " was found in the symbol table. Skipping..." << endl << endl;
	}
	string temp = predicate_entry->type() + ":";
	temp += predicate_entry->text();
	_predicateEntry = table.find(temp);
}

shared_ptr<SymbolTableEntry> Predicate::predicate_entry() {
	return _predicateEntry;
}

bool Predicate::is_valid() {
	if (!_predicateEntry) {
		SymbolTable table;
		fill_symbol_table(table);
	}
	return _predicateEntry->is_valid();	
}
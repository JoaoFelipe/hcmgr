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

//  @brief Predicate(const Name& n, const vector<Symbol>& s) - Predicate class Constructor using a Name and a vector of Symbols as parameters 
//  @param n, s - references to a Name and a vector of Symbols
Predicate::Predicate(const Name& n, const vector<Symbol>& s): _name(n), _symbols(s) {}

//  @brief Predicate(const Predicate& p) - Predicate class Copy Constructor
//  @param p - reference to another Predicate
Predicate::Predicate(const Predicate& p) :_name(p._name), _symbols(p._symbols){}


//  @brief name(const Name& n)  - Setter method for the Predicate Name
//  @param n - reference to a Name	
void Predicate::name(const Name& n) {
	_name = n;
}

//  @brief name()  - Getter method for the Predicate Name
//  @return Name - Predicate Name	
Name Predicate::name() const {
	return _name;
}

//  @brief symbols(const vector<Symbol>& s) - Setter method for the vector of Symbols
//  @param s - reference to a vector of Symbols	
void Predicate::symbols(const vector<Symbol>& s) {
	_symbols = s;
}

//  @brief symbols() - Getter method for the Predicate vector of Symbols
//  @return vector<Symbol> - Predicate vector of Symbols	
vector<Symbol> Predicate::symbols() const {
	return _symbols;
}

//  @brief print(ostream & output)  - Prints the Predicate according to the grammar syntax
//  @param output - ostream
void Predicate::print(ostream & output) const {
	output << LEFTPAREN;
	_name.print();
	for (vector<Symbol>::const_iterator i = _symbols.begin(); i != _symbols.end(); ++i) {
		output << " ";
		i->print(output);
	}
	output << RIGHTPAREN;

}

//  @brief fill_symbol_table(SymbolTable & table)  - Fills out a Symbol Table with tokens from the Predicate 
//  @param table - SymbolTable 
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
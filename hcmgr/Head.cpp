/**
	Head.cpp
	Class name: Head 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the class Head for the grammar
			    head -> predicate
*/

#include "stdafx.h"
#include "Head.h"

//  @brief Head(const Predicate& p) - Head class Constructor using a predicate parameter
//  @param p - reference to a predicate 
Head::Head(const Predicate& p) : _predicate(p) {}

//  @brief Head(const Head& h) - Head class Copy Constructor
//  @param h - reference to another head
Head::Head(const Head& h): _predicate(h._predicate){}

//  @brief predicate(const Predicate& p) - Setter to the Head predicate
//  @param p - reference to a predicate
void Head::predicate(const Predicate& p) {
	_predicate = p;
}

//  @brief predicate() - Getter to the Head predicate
//  @return Predicate
Predicate Head::predicate() const {
	return _predicate;
}

//  @brief print(ostream & output)  - Prints the predicate according to the grammar syntax
//  @param output - ostream
void Head::print(ostream & output) const {
	_predicate.print(output);
}

//  @brief fill_symbol_table(SymbolTable & table) - Fills out a Symbol Table with tokens from the predicate and its symbols (variables and constants)
//  @param table - SymbolTable
void Head::fill_symbol_table(SymbolTable & table) const {
	_predicate.fill_symbol_table(table);
}
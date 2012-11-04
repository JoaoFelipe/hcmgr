/**
	HornClause.cpp
	Class name: HornClause 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the Horn Clause for the grammar
			    hornclause -> LEFTPAREN head [body] RIGHTPAREN

*/


#include "stdafx.h"
#include "HornClause.h"
#include "const.h"

//  @brief HornClause(const Head & h) - HornClause class Constructor using a Head parameter and default body
//  @param h - reference to Head
HornClause::HornClause(const Head & h): _head(h), _body(0) {}

//  @brief HornClause(const Head & h, const Body & b) - HornClause class Constructor using Head and Body parameters
//  @param h, b - references to a Head and Body 
HornClause::HornClause(const Head & h, const Body & b): _head(h), _body(new Body(b)) {}

//  @brief HornClause(const HornClause & hc) - HornClause class copy Constructor
//  @param hc - reference to another HornClause
HornClause::HornClause(const HornClause & hc): _head(hc._head), _body(new Body(*hc._body)){}

//  @brief operator=(const HornClause & other) - Assignment operator
//  @param hc - reference to another HornClause
HornClause & HornClause::operator=(const HornClause & other) {
	if (this != &other) {
		head(other.head());
		body(other.body());
	}
	return *this;
}

//  @brief ~HornClause() - HornClause class Destructor
HornClause::~HornClause() {
	delete _body;
}

//  @brief head(const Head & h)  - Setter method for the HornClause Head
//  @param h - reference to a Head	
void HornClause::head(const Head & h) {
	_head = h;
}

//  @brief head()  - Getter method for the HornClause Head
//  @return Head - the HornClause Head
Head HornClause::head() const {
	return _head;
}

//  @brief head(const Body & b)  - Setter method for the HornClause Body
//  @param b - reference to a Body
void HornClause::body(const Body & b) {
	delete _body;
	_body = new Body(b);
}

//  @brief head()  - Getter method for the HornClause Head
//  @return Body - the HornClause Body
Body HornClause::body() const {
	return *_body;
}

//  @brief print(ostream & output)  - Prints the Horn Clause according to the grammar syntax
//  @param output - ostream
void HornClause::print(ostream & output) const {
	output << LEFTPAREN;
	_head.print(output);
	if (_body != 0) {
		output << " ";
		_body->print(output);
	}
	output << RIGHTPAREN;
}


//  @brief fill_symbol_table(SymbolTable & table)  - Fills out a Symbol Table with tokens from the Horn Clause Head and Body
//  @param table - SymbolTable 
void HornClause::fill_symbol_table(SymbolTable & table) const{
	_head.fill_symbol_table(table);
	if (_body != 0) {
		_body->fill_symbol_table(table);
	}
}
/**
	HornClause.h
	Class name: HornClause 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the Horn Clause for the grammar
			    hornclause -> LEFTPAREN head [body] RIGHTPAREN
*/
#ifndef HORN_CLAUSE_H
#define HORN_CLAUSE_H

#include <vector>
#include "body.h"
#include "head.h"
#include "SymbolTable.h"
#include <ostream>
#include <iostream>

using namespace std;

class HornClause
{
private:
// Head of the Horn Clause
	Head _head;
// Body of the Horn Clause
	Body * _body;  
public:

//  @brief HornClause(const Head & h) - HornClause class Constructor using a Head parameter and default body
//  @param h - reference to Head
	HornClause(const Head & h);
	
//  @brief HornClause(const Head & h, const Body & b) - HornClause class Constructor using Head and Body parameters
//  @param h, b - references to a Head and Body 
	HornClause(const Head & h, const Body & b);

//  @brief HornClause(const HornClause & hc) - HornClause class copy Constructor
//  @param hc - reference to another HornClause
	HornClause(const HornClause & hc);

//  @brief operator=(const HornClause & other) - Assignment operator
//  @param hc - reference to another HornClause
	HornClause & operator=(const HornClause & other);

//  @brief ~HornClause() - HornClause class Destructor
	~HornClause();

//  @brief head(const Head & h)  - Setter method for the HornClause Head
//  @param h - reference to a Head	
	void head(const Head & h);
 
//  @brief head()  - Getter method for the HornClause Head
//  @return Head - the HornClause Head
	Head head() const;

//  @brief head(const Body & b)  - Setter method for the HornClause Body
//  @param b - reference to a Body
	void body(const Body & b);

//  @brief head()  - Getter method for the HornClause Head
//  @return Body - the HornClause Body
	Body body() const;

//  @brief print(ostream & output)  - Prints the Horn Clause according to the grammar syntax
//  @param output - ostream
	void print(ostream & = cout) const; 

//  @brief fill_symbol_table(SymbolTable & table)  - Fills out a Symbol Table with tokens from the Horn Clause Head and Body
//  @param table - SymbolTable 
	void fill_symbol_table(SymbolTable & table) const;

};

#endif
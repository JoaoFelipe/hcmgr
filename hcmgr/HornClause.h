/**
	HornClause.h
	Class name: HornClause 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the Horn Clause for the grammar
			    hornclause -> LEFTPAREN head [body] RIGHTPAREN
*/
#ifndef HORN_CLAUSE_H
#define HORN_CLAUSE_H

#include <vector>
#include "body.h"
#include "head.h"
#include "SubstitutionList.h"
#include "Predicate.h"
#include "SymbolTable.h"
#include "PredicateEntry.h"
#include <ostream>
#include <iostream>
#include <memory>
using namespace std;

class HornClause
{
private:
// Head of the Horn Clause
	shared_ptr<Head> _head;
// Body of the Horn Clause
	shared_ptr<Body> _body;  
public:

// @brief HornClause class Constructor using a Head parameter and default body
// @param h - reference to Head
	HornClause(const Head & h);
	
// @brief HornClause class Constructor using Head and Body parameters
// @param h, b - references to a Head and Body 
	HornClause(const Head & h, const Body & b);

// @brief HornClause class Constructor using Head and Body shared_ptr parameters
// @param h, b - shared_ptr to a Head and Body 
	HornClause(const shared_ptr<Head> h, const shared_ptr<Body> b);

// @brief HornClause class copy Constructor
// @param hc - reference to another HornClause
	HornClause(const HornClause & hc);

// @brief Assignment operator
// @param hc - reference to another HornClause
	HornClause & operator=(const HornClause & other);

// @brief Comparisson operator
// @param hc - reference to another HornClause
	bool operator==(const HornClause & other);

// @brief Setter method for the HornClause Head
// @param h - reference to a Head	
	void head(const Head & h);
 
// @brief Getter method for the HornClause Head
// @return Head - the HornClause Head
	shared_ptr<Head> head() const;

// @brief Setter method for the HornClause Body
// @param b - reference to a Body
	void body(const Body & b);

// @brief Getter method for the HornClause Head
// @return Body - the HornClause Body
	shared_ptr<Body> body() const;

// @brief Prints the Horn Clause according to the grammar syntax
// @param output - ostream
	void print(ostream & = cout) const; 

// @brief Fills out a Symbol Table with tokens from the Horn Clause Head and Body
// @param table - SymbolTable 
	void fill_symbol_table();

// @brief Getter method for the predicates from the body of the HornClause
// @return vector<Predicate> 
	vector<Predicate> body_predicates();

// @brief Getter method for the predicates from the head of the HornClause
// @return vector<Predicate>
	vector<Predicate> head_predicates();

// @brief Verifies if HornClause is a fact - only head and no body
// @return bool	
	bool is_fact() const;

// @brief Verifies if HornClause is goal - only body and no head
// @return bool
	bool is_goal() const;

// @brief Verifies if HornClause is true - no body or head
// @return bool
	bool is_true() const;

// @brief Verifies if body and head of the HornClause are valid
// @return bool
	bool is_valid();

// @brief Unifies two Horn Clauses
// @param other - reference to a HornClause
// @return shared_ptr<HornClause> - unification result	
	shared_ptr<HornClause> unify(HornClause & other);
};

// @brief Struct to matches predicate to substitution list
// @return shared_ptr<HornClause> - unification result
struct Matches {
	Predicate predicate_base;
	SubstitutionList subst;

	Matches(Predicate p, SubstitutionList s): predicate_base(p), subst(s) {}

    bool operator()(Predicate predicate) {
		return predicate_base.predicate_entry()->matches(predicate.predicate_entry(), subst);
    }
};

struct Substitute {
	SubstitutionList subst;

	Substitute(SubstitutionList s): subst(s) {}

	shared_ptr<Predicate> transform(Predicate predicate) {
		shared_ptr<Predicate> result = dynamic_pointer_cast<PredicateEntry>(predicate.predicate_entry())->substitute(subst);
		result->fill_symbol_table();
		return result;
	}

    Predicate operator()(Predicate predicate) {
		return *transform(predicate);
    }
};

#endif
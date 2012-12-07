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
#include "SubstitutionList.h"
#include "const.h"

// @brief HornClause class Constructor using a Head parameter and default body
// @param h - reference to Head
HornClause::HornClause(const Head & h): _head(shared_ptr<Head>(new Head(h))), _body(shared_ptr<Body>()) {}

// @brief HornClause class Constructor using Head and Body parameters
// @param h, b - references to a Head and Body 
HornClause::HornClause(const Head & h, const Body & b): _head(shared_ptr<Head>(new Head(h))), _body(new Body(b)) {}

// @brief HornClause class Constructor using Head and Body shared_ptr parameters
// @param h, b - shared_ptr to a Head and Body 
HornClause::HornClause(const shared_ptr<Head> h, const shared_ptr<Body> b) : _head(h), _body(b) {}



// @brief HornClause class copy Constructor
// @param hc - reference to another HornClause
HornClause::HornClause(const HornClause & hc): _head(hc._head){
	if (hc._head) {
		_head = shared_ptr<Head>(new Head(*hc._head));
	}
	if (hc._body) {
		_body = shared_ptr<Body>(new Body(*hc._body));
	}
}

// @brief Assignment operator
// @param hc - reference to another HornClause
HornClause & HornClause::operator=(const HornClause & other) {
	if (this != &other) {
		head(*other.head());
		body(*other.body());
	}
	return *this;
}

// @brief Setter method for the HornClause Head
// @param h - reference to a Head	
void HornClause::head(const Head & h) {
	_head = shared_ptr<Head>(new Head(h));
}

// @brief Getter method for the HornClause Head
// @return Head - the HornClause Head
shared_ptr<Head> HornClause::head() const {
	return _head;
}

// @brief Setter method for the HornClause Body
// @param b - reference to a Body
void HornClause::body(const Body & b) {
	_body = shared_ptr<Body>(new Body(b));
}

// @brief Getter method for the HornClause Head
// @return Body - the HornClause Body
shared_ptr<Body> HornClause::body() const {
	return _body;
}

// @brief Prints the Horn Clause according to the grammar syntax
// @param output - ostream
void HornClause::print(ostream & output) const {
	output << LEFTPAREN;
	if (_head) {
		_head->print(output);
	}
	if (_body) {
		output << " ";
		_body->print(output);
	}
	output << RIGHTPAREN;
}


// @brief Fills out a Symbol Table with tokens from the Horn Clause Head and Body
// @param table - SymbolTable 
void HornClause::fill_symbol_table(SymbolTable & table){
	_head->fill_symbol_table(table);
	if (_body) {
		_body->fill_symbol_table(table);
	}
}


shared_ptr<HornClause> HornClause::unify(HornClause & other) {
	Predicate predicate_head = head()->predicate();
	vector<Predicate> other_predicates = other.body()->predicates();
	vector<Predicate> predicates = body()->predicates();

	SubstitutionList subst;

	vector<Predicate> new_body;
	for (auto i = other_predicates.begin(); i != other_predicates.end(); ++i) {
		if (predicate_head.can_unify(*i)) {
			if (predicate_head.predicate_entry()->matches(i->predicate_entry(), subst)) {
				for (auto j = predicates.begin(); j != predicates.end(); ++j) {
					new_body.push_back(*j);
				}
			} else {
				return shared_ptr<HornClause>();
			}
		} else {
			new_body.push_back(*i);
		}
	}

	//post proccess
	shared_ptr<Head> head_result(other.head());
	shared_ptr<Body> body_result;

	Predicate other_predicate_head = other.head()->predicate();
	vector<Predicate> body_after_replace;
	
	for (auto i = new_body.begin(); i != new_body.end(); ++i) {
		if (other_predicate_head.predicate_entry()->matches(i->predicate_entry(), subst)) {
			head_result = shared_ptr<Head>();
		} else {
			body_after_replace.push_back(*i);
		}
	}

	if (body_after_replace.size() != 0) {
		body_result = shared_ptr<Body>(new Body(body_after_replace));
	} 

	return shared_ptr<HornClause>(new HornClause(head_result, body_result));
}
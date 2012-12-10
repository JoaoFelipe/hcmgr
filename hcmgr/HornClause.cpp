/**
	HornClause.cpp
	Class name: HornClause 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the Horn Clause for the grammar
			    hornclause -> LEFTPAREN head [body] RIGHTPAREN

*/


#include "stdafx.h"
#include "HornClause.h"
#include "SubstitutionList.h"
#include "PredicateEntry.h"
#include "const.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>



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

// @brief Comparisson operator
// @param hc - reference to another HornClause
bool HornClause::operator==(const HornClause & other) {
	ostringstream ths;
	print(ths);
	ostringstream oth;
	other.print(oth);
	string this_str(ths.str());
	string other_str(oth.str());
	bool b = (this_str == other_str);
	return b;
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
	if (is_true()) {
		output << "True";
		return;
	}
	
	output << LEFTPAREN;
	if (is_goal()) {
		output << "Goal";
	}


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
void HornClause::fill_symbol_table(){
	if (_head) {
		_head->fill_symbol_table();
	}
	if (_body) {
		_body->fill_symbol_table();
	}
}

// @brief Getter method for the predicates from the body of the HornClause
// @return vector<Predicate> 
vector<Predicate> HornClause::body_predicates() {
	if (_body) {
		return _body->predicates();
	}
	return vector<Predicate>();
}

// @brief Getter method for the predicates from the head of the HornClause
// @return vector<Predicate>
vector<Predicate> HornClause::head_predicates() {
	if (_head) {
		return _head->predicates();
	}
	return vector<Predicate>();
}

// @brief Verifies if HornClause is a fact - only head and no body
// @return bool
bool HornClause::is_fact() const {
	return (_head && !_body);
}

// @brief Verifies if HornClause is goal - only body and no head
// @return bool
bool HornClause::is_goal() const {
	return (!_head && _body);
}

// @brief Verifies if HornClause is true - no body or head
// @return bool
bool HornClause::is_true() const {
	return (!_head && !_body);
}

// @brief Verifies if body and head of the HornClause are valid
// @return bool
bool HornClause::is_valid() {
	bool result = true;
	if (_head) {
		result = result && _head->is_valid();
	}
	if (_body) {
		result = result && _body->is_valid();
	}
	return result;
}

// @brief Unifies two Horn Clauses
// @param other - reference to a HornClause
// @return shared_ptr<HornClause> - unification resultshared_ptr<HornClause> HornClause::unify(HornClause & other) {
shared_ptr<HornClause> unify(HornClause & other){
	shared_ptr<SymbolTable> table = SymbolTable::instance();
	if (!other.is_valid()) {
		return shared_ptr<HornClause>();
	}
	if (is_goal() || !is_valid()) {
		return shared_ptr<HornClause>(new HornClause(other.head(), other.body()));
	}
	Predicate predicate_head = head()->predicate();
	vector<Predicate> other_body_predicates = other.body_predicates();
	vector<Predicate> body_predicates = this->body_predicates();

	SubstitutionList subst;

	vector<Predicate> new_body;
	for (auto i = other_body_predicates.begin(); i != other_body_predicates.end(); ++i) {
		SubstitutionList temp(subst);
		if (predicate_head.predicate_entry()->matches(i->predicate_entry(), temp)) {
			subst.add_all(temp);
			back_insert_iterator<vector<Predicate>> inserter(new_body);
			copy(body_predicates.begin(), body_predicates.end(), inserter);
		} else {
			new_body.push_back(*i);
		}
	}

	//post proccess
	Substitute substitute(subst);

	shared_ptr<Head> head_result;
	shared_ptr<Body> body_result;

	bool other_has_head = true;
	vector<Predicate> other_head_predicates = other.head_predicates();
	shared_ptr<Predicate> other_predicate_head;
	if (other_head_predicates.size() == 0) {
		other_has_head = false;
	} else {
		head_result = shared_ptr<Head>(new Head(substitute(other.head()->predicate())));
		other_predicate_head = substitute.transform(other_head_predicates[0]);
	}


	vector<Predicate> body_substitutions_replace;
	back_insert_iterator<vector<Predicate>> inserter(body_substitutions_replace);
	transform(new_body.begin(), new_body.end(), inserter, substitute);

	 
	vector<Predicate> body_after_replace;
	
	for (auto i = body_substitutions_replace.begin(); i != body_substitutions_replace.end(); ++i) {
		SubstitutionList subst_temp;

		if (other_has_head && other_predicate_head->predicate_entry()->matches(i->predicate_entry(), subst_temp)) {
			head_result = shared_ptr<Head>();
		} else {
			SubstitutionList subst_temp2;
			auto it = find_if(body_after_replace.begin(), body_after_replace.end(), Matches(*i, subst_temp2));
			if (it == body_after_replace.end()) {
				body_after_replace.push_back(*i);
			}
		}
	}

	
	if (body_after_replace.size() != 0) {
		body_result = shared_ptr<Body>(new Body(body_after_replace));
	} 

	return shared_ptr<HornClause>(new HornClause(head_result, body_result));
}
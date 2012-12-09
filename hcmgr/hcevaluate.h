/**
  hcevaluate.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the functions to evaluate the Predicate
*/

#ifndef HCEVALUATE_H
#define HCEVALUATE_H 

#include "stdafx.h"
#include "HornClause.h"
#include "SymbolTable.h"
#include <string>
#include <memory>
#include <vector>
using namespace std; 

// @brief Tries to evaluate the predicate passed as text, using the deductive database
// @param text is the Predicate Goal, db is the deductive database, table is the SymbolTable, output is ostream
// @return int indicating success (0-SUCCESS)
int evaluate(string& text, vector<shared_ptr<HornClause>> & db, ostream & output);

// @brief Tries to find a solution recursively for the goal
// @param goal is a hornclause with just the body, db is the deductive database, table is the SymbolTable, output is ostream, count is the current iteration
// @return The found solution.
shared_ptr<HornClause> find_solution(HornClause goal, vector<shared_ptr<HornClause>> db, ostream & output, int & count);


#endif
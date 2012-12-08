/**
  hcevaluate.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the method to evaluate the Predicate

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


int evaluate(string& text, vector<HornClause> & db, SymbolTable table, ostream & output);

shared_ptr<HornClause> find_solution(HornClause goal, vector<HornClause> db, SymbolTable table, ostream & output, int & count);


#endif
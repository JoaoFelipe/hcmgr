/**
  hcevaluate.cpp
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Definition of the functions to evaluate the Predicate
*/

#include "stdafx.h" 
#include "hcevaluate.h"
#include "parser.h"
#include "const.h"

// @brief Tries to evaluate the predicate passed as text, using the deductive database
// @param text is the Predicate Goal, db is the deductive database, table is the SymbolTable, output is ostream
// @return int indicating success (0-SUCCESS)
int evaluate(string& text, vector<shared_ptr<HornClause>> & db, ostream & output) {
	Parser parser(text);
	shared_ptr<HornClause> goal = parser.parse_goal();
	if (!goal) {
		output << "Invalid Predicate Syntax" << endl;
		return 3;
	}
	goal->fill_symbol_table();
	int count = 0;
	shared_ptr<HornClause> y = find_solution(*goal, db, output, count);
	if (y) {
		return 0;
	} else {
		if (count >= MAX_LOOPS) {
			output << "The program reached the max number of recursions. Maybe it is not a infinite loop, but we decided to stop." << endl;
			return 2;
		}
		output << "No result." << endl;
		return 1;
	}

}

// @brief Tries to find a solution recursively for the goal
// @param goal is a hornclause with just the body, db is the deductive database, table is the SymbolTable, output is ostream, count is the current iteration
// @return The found solution.
shared_ptr<HornClause> find_solution(HornClause goal, vector<shared_ptr<HornClause>> db, ostream & output, int & count) {
	if (count >= MAX_LOOPS) {
		return shared_ptr<HornClause>();
	}
	
	vector<shared_ptr<HornClause>> db2(db);
	db2.push_back(shared_ptr<HornClause>(new HornClause(goal)));
	for (auto i = db.begin(); i != db.end(); ++i) {
		shared_ptr<HornClause> x = (*i)->unify(goal);
		if (x && !(*x == goal) ) {
			if (x->is_true()) {
				
				goal.print(output);
				output << " unified with ";
				(*i)->print(output);
				output << ": ";
				x->print(output);
				output << endl;
				return x;
			}
			x->fill_symbol_table();
			shared_ptr<HornClause> y = find_solution(*x, db2, output, ++count);
			if (y) {
				goal.print(output);
				output << " unified with ";
				(*i)->print(output);
				output << ": ";
				x->print(output);
				output << endl;
				return shared_ptr<HornClause>(new HornClause(*y));
			}
		}
		
	}
	return shared_ptr<HornClause>();
}
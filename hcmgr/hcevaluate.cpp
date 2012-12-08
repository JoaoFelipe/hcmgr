#include "stdafx.h" 
#include "hcevaluate.h"
#include "parser.h"
#include "const.h"


int evaluate(string& text, vector<HornClause> & db, SymbolTable table, ostream & output) {
	Parser parser(text);
	shared_ptr<HornClause> goal = parser.parse_goal();
	if (!goal) {
		output << "Invalid Predicate Syntax" << endl;
	}
	goal->fill_symbol_table(table);
	int count = 0;
	shared_ptr<HornClause> y = find_solution(*goal, db, table, output, count);
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

shared_ptr<HornClause> find_solution(HornClause goal, vector<HornClause> db, SymbolTable table, ostream & output, int & count) {
	if (count >= MAX_LOOPS) {
		return shared_ptr<HornClause>();
	}
	
	vector<HornClause> db2(db);
	db2.push_back(goal);
	for (auto i = db.begin(); i != db.end(); ++i) {
		shared_ptr<HornClause> x = i->unify(goal);
		if (x && !(*x == goal) ) {
			if (x->is_true()) {
				
				goal.print(output);
				output << " unified with ";
				i->print(output);
				output << ": ";
				x->print(output);
				output << endl;
				return x;
			}
			x->fill_symbol_table(table);
			shared_ptr<HornClause> y = find_solution(*x, db2, table, output, ++count);
			if (y) {
				goal.print(output);
				output << " unified with ";
				i->print(output);
				output << ": ";
				x->print(output);
				output << endl;
				return shared_ptr<HornClause>(new HornClause(*y));
			}
		}
		
	}
	return shared_ptr<HornClause>();
}
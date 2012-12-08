#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\FunctionEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\UnboundSymbol.h"
#include "..\hcmgr\TermSymbol.h"
#include "..\hcmgr\HornClause.h"
#include "..\hcmgr\Head.h"
#include "..\hcmgr\Body.h"
#include "..\hcmgr\Parser.h"

#include "..\hcmgr\ConstantEntry.h"
#include "..\hcmgr\SymbolTable.h"
#include "..\hcmgr\Predicate.h"
#include "..\hcmgr\Name.h"
#include "..\hcmgr\hcevaluate.h"
#include "..\hcmgr\const.h"


#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(EvaluateTest)
	{
	public:

		TEST_METHOD(evaluate_fact)
		{
			vector<HornClause> v;
			Parser parser("( (a) )");
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(a)";

			ostringstream s;
			Assert::AreEqual(0, evaluate(predicate_query,  v, table, s));
			ostringstream result; result << "(Goal ((a))) unified with ((a)): True" << endl;
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(evaluate_one_step)
		{
			vector<HornClause> v;
			Parser parser("( (b) ) ( (a) ((b)) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(a)";

			ostringstream s;
			Assert::AreEqual(0, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "(Goal ((b))) unified with ((b)): True" << endl;
			result << "(Goal ((a))) unified with ((a) ((b))): (Goal ((b)))" << endl;
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(evaluate_two_steps)
		{
			vector<HornClause> v;
			Parser parser("( (c) ) ( (a) ((b)) ) ( (b) ((c)) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(a)";

			ostringstream s;
			Assert::AreEqual(0, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "(Goal ((c))) unified with ((c)): True" << endl;
			result << "(Goal ((b))) unified with ((b) ((c))): (Goal ((c)))" << endl;
			result << "(Goal ((a))) unified with ((a) ((b))): (Goal ((b)))" << endl;
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(evaluate_unnecessary_steps)
		{
			vector<HornClause> v;
			Parser parser("( (c) ) ( (a) ((b)) ) ( (b) ((e)) ) ( (b) ((c)) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(a)";

			ostringstream s;
			Assert::AreEqual(0, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "(Goal ((c))) unified with ((c)): True" << endl;
			result << "(Goal ((b))) unified with ((b) ((c))): (Goal ((c)))" << endl;
			result << "(Goal ((a))) unified with ((a) ((b))): (Goal ((b)))" << endl;
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(evaluate_book)
		{
			vector<HornClause> v;
			Parser parser("( (ancestor X Y) ((parent X Z) (ancestor Z Y)) ) ( (ancestor X X) ) ( (parent 0 1) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(parent X 1)";

			ostringstream s;
			Assert::AreEqual(0, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "(Goal ((parent X 1))) unified with ((parent 0 1)): True" << endl;
			Assert::AreEqual(result.str(), s.str());
		}
		
		TEST_METHOD(evaluate_book_ancestor)
		{
			vector<HornClause> v;
			Parser parser("( (ancestor X Y) ((parent X Z) (ancestor Z Y)) ) ( (ancestor X X) ) ( (parent 0 1) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(ancestor 0 1)";

			ostringstream s;
			Assert::AreEqual(0, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "(Goal ((parent 0 1))) unified with ((parent 0 1)): True" << endl;
			result << "(Goal ((parent 0 Z) (ancestor Z 1))) unified with ((ancestor X X)): (Goal ((parent 0 1)))" << endl;
			result << "(Goal ((ancestor 0 1))) unified with ((ancestor X Y) ((parent X Z) (ancestor Z Y))): (Goal ((parent 0 Z) (ancestor Z 1)))" << endl;
			
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(evaluate_book_ancestor_fail)
		{
			vector<HornClause> v;
			Parser parser("( (ancestor X Y) ((parent X Z) (ancestor Z Y)) ) ( (ancestor X X) ) ( (parent 0 1) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(ancestor 1 0)";

			ostringstream s;
			Assert::AreEqual(1, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "No result." << endl;
			
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(evaluate_book_ancestor_unbound)
		{
			vector<HornClause> v;
			Parser parser("( (ancestor X Y) ((parent X Z) (ancestor Z Y)) ) ( (ancestor X X) ) ( (parent 0 1) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(ancestor X 1)";

			ostringstream s;
			Assert::AreEqual(0, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "(Goal ((ancestor 1 1))) unified with ((ancestor X X)): True" << endl;
			result << "(Goal ((parent X Z) (ancestor Z 1))) unified with ((parent 0 1)): (Goal ((ancestor 1 1)))" << endl;
			result << "(Goal ((ancestor X 1))) unified with ((ancestor X Y) ((parent X Z) (ancestor Z Y))): (Goal ((parent X Z) (ancestor Z 1)))" << endl;
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(evaluate_book_loop)
		{
			MAX_LOOPS = 10;

			vector<HornClause> v;
			Parser parser("( (a) ((b)) ) ( (b) ((c)) )  ( (c) ((a)) )");
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());
			v.push_back(*parser.parse_horn_clause());

			SymbolTable table;

			for (HornClause i : v) {
				i.fill_symbol_table(table);
			}
			string predicate_query = "(a)";

			ostringstream s;
			Assert::AreEqual(2, evaluate(predicate_query,  v, table, s));
			ostringstream result; 
			result << "The program reached the max number of recursions. Maybe it is not a infinite loop, but we decided to stop." << endl;
			Assert::AreEqual(result.str(), s.str());
		}

	};
}
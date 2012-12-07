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


#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(HornClauseTest)
	{
	public:

		TEST_METHOD(CreateHornClause_WithoutBody)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			Head head(predicate);
			HornClause hc(head);

			ostringstream s;
			hc.print(s);
			ostringstream result; result << "((abs 1 A))";
			Assert::AreEqual(result.str(), s.str());
		}
		
		TEST_METHOD(CreateHornClause_WithBody)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("sum")), v2);

			vector<Predicate> predicates;
			predicates.push_back(predicate);
			predicates.push_back(predicate2);

			Head head(predicate);
			Body body(predicates);
			HornClause hc(head, body);

			ostringstream s;
			hc.print(s);
			ostringstream result; result << "((abs 1 A) ((abs 1 A) (sum 2 B)))";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(CopyHornClause_WithBody)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("sum")), v2);

			vector<Predicate> predicates;
			predicates.push_back(predicate);
			predicates.push_back(predicate2);

			Head head(predicate);
			Body body(predicates);
			HornClause hc(head, body);
			HornClause chc(hc);

			ostringstream s;
			chc.print(s);
			ostringstream result; result << "((abs 1 A) ((abs 1 A) (sum 2 B)))";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(EqualOperatorHornClause_WithBody)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("sum")), v2);

			vector<Predicate> predicates;
			predicates.push_back(predicate);
			predicates.push_back(predicate2);

			Head head(predicate);
			Body body(predicates);
			HornClause hc(head, body);
			HornClause chc = hc;

			ostringstream s;
			chc.print(s);
			ostringstream result; result << "((abs 1 A) ((abs 1 A) (sum 2 B)))";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(GetSetHeadHornClause)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("sum")), v2);

			vector<Predicate> predicates;
			predicates.push_back(predicate);
			predicates.push_back(predicate2);

			Head head(predicate);
			Body body(predicates);
			HornClause hc(head, body);
			
			Head head2(predicate2);

			hc.head(head2);
			Head head_result = *hc.head();

			ostringstream s;
			head_result.print(s);
			ostringstream result; result << "(sum 2 B)";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(GetSetBodyHornClause)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("sum")), v2);

			vector<Predicate> predicates;
			predicates.push_back(predicate);
			predicates.push_back(predicate2);

			Head head(predicate);
			Body body(predicates);
			HornClause hc(head, body);
			
			vector<Predicate> predicates2;
			predicates2.push_back(predicate2);
			predicates2.push_back(predicate);
			
			Body body2(predicates2);

			hc.body(body2);
			Body body_result = *hc.body();

			ostringstream s;
			body_result.print(s);
			ostringstream result; result << "((sum 2 B) (abs 1 A))";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(FillSymbolTablePredicatesContainer)
		{
			vector<shared_ptr<Symbol>> h;
			h.push_back(shared_ptr<Symbol>(new TermSymbol(string("3"))));
			h.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("C"))));
			Predicate hpredicate(Name(string("new")), h);

			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("sum")), v2);

			vector<Predicate> predicates;
			predicates.push_back(predicate);
			predicates.push_back(predicate2);

			Head head(hpredicate);
			Body body(predicates);
			HornClause hc(head, body);

			SymbolTable table;

			hc.fill_symbol_table(table);

			Assert::IsNotNull(table.find("Predicate:new 3 C").get());
			Assert::IsNotNull(table.find("Constant:3").get());
			Assert::IsNull(table.find("Unbound:C").get());

			Assert::IsNotNull(table.find("Predicate:abs 1 A").get());
			Assert::IsNotNull(table.find("Constant:1").get());
			Assert::IsNull(table.find("Unbound:A").get());

			Assert::IsNotNull(table.find("Predicate:sum 2 B").get());
			Assert::IsNotNull(table.find("Constant:2").get());
			Assert::IsNull(table.find("Unbound:B").get());
		}

		TEST_METHOD(UnifyHornClase_Simple) 
		{
			SymbolTable table;
			Parser parser(string("((b) ((a))) ((c) ((b)))"));
			shared_ptr<HornClause> hc1 = parser.parse_horn_clause();
			shared_ptr<HornClause> hc2 = parser.parse_horn_clause();
			hc1->fill_symbol_table(table);
			hc2->fill_symbol_table(table);
			
			shared_ptr<HornClause> hc_result = hc1->unify(*hc2);
			
			ostringstream s;
			hc_result->print(s);
			ostringstream result; result << "((c) ((a)))";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(UnifyHornClase_Simple_Predicates_Complex_Clauses) 
		{
			SymbolTable table;
			Parser parser(string("((b) ((a) (e))) ((c) ((b) (d)))"));
			shared_ptr<HornClause> hc1 = parser.parse_horn_clause();
			shared_ptr<HornClause> hc2 = parser.parse_horn_clause();
			hc1->fill_symbol_table(table);
			hc2->fill_symbol_table(table);

			shared_ptr<HornClause> hc_result = hc1->unify(*hc2);
			
			ostringstream s;
			hc_result->print(s);
			ostringstream result; result << "((c) ((a) (e) (d)))";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(UnifyHornClase_Eliminate_Matches) 
		{
			SymbolTable table;
			Parser parser(string("((a) ((b))) ((b) ((a) (c)))"));
			shared_ptr<HornClause> hc1 = parser.parse_horn_clause();
			shared_ptr<HornClause> hc2 = parser.parse_horn_clause();
			hc1->fill_symbol_table(table);
			hc2->fill_symbol_table(table);

			shared_ptr<HornClause> hc_result = hc1->unify(*hc2);
			
			ostringstream s;
			hc_result->print(s);
			ostringstream result; result << "( ((c)))";
			Assert::AreEqual(result.str(), s.str());
		}


	};
}
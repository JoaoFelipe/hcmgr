#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\FunctionEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\UnboundSymbol.h"
#include "..\hcmgr\TermSymbol.h"

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
	TEST_CLASS(PredicateTest)
	{
	public:
		
		TEST_METHOD(CreatePredicate)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			
			Assert::AreEqual(string("abs"), predicate.name().value());
			Assert::AreEqual(string("1"), dynamic_pointer_cast<TermSymbol>(predicate.symbols()[0])->value());
			Assert::AreEqual(string("A"), dynamic_pointer_cast<UnboundSymbol>(predicate.symbols()[1])->value());
		}

		TEST_METHOD(CopyPredicate)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			Predicate cpredicate(predicate);

			Assert::AreEqual(string("abs"), cpredicate.name().value());
			Assert::AreEqual(string("1"), dynamic_pointer_cast<TermSymbol>(cpredicate.symbols()[0])->value());
			Assert::AreEqual(string("A"), dynamic_pointer_cast<UnboundSymbol>(cpredicate.symbols()[1])->value());
		}

		TEST_METHOD(GetSetNamePredicate)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			Assert::AreEqual(string("abs"), predicate.name().value());
			predicate.name(Name("sum"));
			Assert::AreEqual(string("sum"), predicate.name().value());
		}

		TEST_METHOD(GetSetSymbolsPredicate)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			
			Assert::AreEqual(string("1"), dynamic_pointer_cast<TermSymbol>(predicate.symbols()[0])->value());
			Assert::AreEqual(string("A"), dynamic_pointer_cast<UnboundSymbol>(predicate.symbols()[1])->value());
		
			Assert::AreEqual(string("abs"), predicate.name().value());
			predicate.symbols(v2);
			Assert::AreEqual(string("2"), dynamic_pointer_cast<TermSymbol>(predicate.symbols()[0])->value());
			
		}

		TEST_METHOD(PrintPredicate)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			ostringstream s;
			predicate.print(s);
			ostringstream result; result << "(abs 1 A)";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(CanUnifyPredicate_True)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			Predicate predicate2(Name(string("abs")), v2);
	
			Assert::AreEqual(true, predicate.can_unify(predicate2));
		}

		TEST_METHOD(CanUnifyPredicate_InvalidName)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			Predicate predicate2(Name(string("sum")), v2);
	
			Assert::AreEqual(false, predicate.can_unify(predicate2));
		}

		TEST_METHOD(CanUnifyPredicate_InvalidParamCount)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("abs")), v2);
	
			Assert::AreEqual(false, predicate.can_unify(predicate2));
		}

		TEST_METHOD(FillSymbolTablePredicate)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("a"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("a"))));
			Predicate predicate(Name(string("abs")), v);

			SymbolTable table;
			
			Assert::IsNull(table.find("Predicate:abs a A a").get());

			predicate.fill_symbol_table(table);

			Assert::IsNotNull(table.find("Predicate:abs a A a").get());
			Assert::IsNotNull(table.find("Bound:a").get());
			Assert::IsNull(table.find("Unbound:A").get());
		}

	};
}
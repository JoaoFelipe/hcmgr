#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\FunctionEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\UnboundSymbol.h"
#include "..\hcmgr\TermSymbol.h"
#include "..\hcmgr\PredicatesContainer.h"

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
	TEST_CLASS(PredicatesContainerTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}
		
		TEST_METHOD(PredicatesContainerBody)
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

			PredicatesContainer container(predicates);

			ostringstream s;
			container.print(s);
			ostringstream result; result << "(abs 1 A) (sum 2 B)";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(CopyPredicatesContainer)
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

			PredicatesContainer container(predicates);
			PredicatesContainer ccontainer(container);

			ostringstream s;
			ccontainer.print(s);
			ostringstream result; result << "(abs 1 A) (sum 2 B)";
			Assert::AreEqual(result.str(), s.str());
		}


		TEST_METHOD(GetSetPredicatesContainer)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate p1(Name(string("abs")), v);

			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate p2(Name(string("sum")), v2);

			vector<Predicate> predicates;
			predicates.push_back(p1);
			predicates.push_back(p2);

			PredicatesContainer container(predicates);

			vector<Predicate> get_predicates = container.predicates();
			unsigned int two = 2;
			Assert::AreEqual(two, get_predicates.size());

			Predicate predicate1 = get_predicates[0];
			Assert::AreEqual(string("abs"), predicate1.name().value());
			Assert::AreEqual(string("1"), dynamic_pointer_cast<TermSymbol>(predicate1.symbols()[0])->value());
			Assert::AreEqual(string("A"), dynamic_pointer_cast<UnboundSymbol>(predicate1.symbols()[1])->value());
		
			Predicate predicate2 = get_predicates[1];
			Assert::AreEqual(string("sum"), predicate2.name().value());
			Assert::AreEqual(string("2"), dynamic_pointer_cast<TermSymbol>(predicate2.symbols()[0])->value());
			Assert::AreEqual(string("B"), dynamic_pointer_cast<UnboundSymbol>(predicate2.symbols()[1])->value());
		
			vector<Predicate> predicates2;
			predicates2.push_back(p2);
			predicates2.push_back(p1);

			container.predicates(predicates2);
			get_predicates = container.predicates();
			Assert::AreEqual(two, get_predicates.size());

			predicate1 = get_predicates[0];
			Assert::AreEqual(string("sum"), predicate1.name().value());
			Assert::AreEqual(string("2"), dynamic_pointer_cast<TermSymbol>(predicate1.symbols()[0])->value());
			Assert::AreEqual(string("B"), dynamic_pointer_cast<UnboundSymbol>(predicate1.symbols()[1])->value());

			predicate2 = get_predicates[1];
			Assert::AreEqual(string("abs"), predicate2.name().value());
			Assert::AreEqual(string("1"), dynamic_pointer_cast<TermSymbol>(predicate2.symbols()[0])->value());
			Assert::AreEqual(string("A"), dynamic_pointer_cast<UnboundSymbol>(predicate2.symbols()[1])->value());
		

		}

		TEST_METHOD(SizePredicatesContainer)
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

			PredicatesContainer container(predicates);

			Assert::AreEqual(2, container.size());
		}

		TEST_METHOD(FillSymbolTablePredicatesContainer)
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

			PredicatesContainer container(predicates);

			shared_ptr<SymbolTable> table = SymbolTable::instance();

			container.fill_symbol_table();

			Assert::IsNotNull(table->find("Predicate:abs 1 A").get());
			Assert::IsNotNull(table->find("Constant:1").get());
			Assert::IsNull(table->find("Unbound:A").get());

			Assert::IsNotNull(table->find("Predicate:sum 2 B").get());
			Assert::IsNotNull(table->find("Constant:2").get());
			Assert::IsNull(table->find("Unbound:B").get());
		}


	};
}
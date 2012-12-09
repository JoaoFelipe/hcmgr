#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\FunctionEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\UnboundSymbol.h"
#include "..\hcmgr\TermSymbol.h"
#include "..\hcmgr\Head.h"

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
	TEST_CLASS(HeadTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}
		
		TEST_METHOD(CreateHead)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			Head head(predicate);

			ostringstream s;
			head.print(s);
			ostringstream result; result << "(abs 1 A)";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(CopyHead)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			Head head(predicate);
			Head chead(head);
			
			ostringstream s;
			chead.print(s);
			ostringstream result; result << "(abs 1 A)";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(GetSetPredicate)
		{
			vector<shared_ptr<Symbol>> v;
			v.push_back(shared_ptr<Symbol>(new TermSymbol(string("1"))));
			v.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("A"))));
			Predicate predicate(Name(string("abs")), v);
			Head head(predicate);

			Predicate get_predicate = head.predicate();
			Assert::AreEqual(string("abs"), get_predicate.name().value());
			Assert::AreEqual(string("1"), dynamic_pointer_cast<TermSymbol>(get_predicate.symbols()[0])->value());
			Assert::AreEqual(string("A"), dynamic_pointer_cast<UnboundSymbol>(get_predicate.symbols()[1])->value());
		
			vector<shared_ptr<Symbol>> v2;
			v2.push_back(shared_ptr<Symbol>(new TermSymbol(string("2"))));
			v2.push_back(shared_ptr<Symbol>(new UnboundSymbol(string("B"))));
			Predicate predicate2(Name(string("sum")), v2);

			head.predicate(predicate2);
			get_predicate = head.predicate();
			Assert::AreEqual(string("sum"), get_predicate.name().value());
			Assert::AreEqual(string("2"), dynamic_pointer_cast<TermSymbol>(get_predicate.symbols()[0])->value());
			Assert::AreEqual(string("B"), dynamic_pointer_cast<UnboundSymbol>(get_predicate.symbols()[1])->value());
		}


	};
}
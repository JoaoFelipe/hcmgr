#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\FunctionEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\UnboundSymbol.h"
#include "..\hcmgr\TermSymbol.h"
#include "..\hcmgr\Body.h"

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
	TEST_CLASS(BodyTest)
	{
	public:
		
		TEST_METHOD(CreateBody)
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

			Body body(predicates);

			ostringstream s;
			body.print(s);
			ostringstream result; result << "((abs 1 A) (sum 2 B))";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(CopyBody)
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

			Body body(predicates);
			Body cbody(body);

			ostringstream s;
			cbody.print(s);
			ostringstream result; result << "((abs 1 A) (sum 2 B))";
			Assert::AreEqual(result.str(), s.str());
		}



	};
}
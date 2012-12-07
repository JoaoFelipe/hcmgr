#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\PredicateEntry.h"
#include "..\hcmgr\SymbolTable.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(SymbolTableTest)
	{
	public:
		
		TEST_METHOD(CreateSymbolTable)
		{
			SymbolTable symbol_table;
			ostringstream s;
			symbol_table.print(s);
			ostringstream expected;
			Assert::AreEqual(expected.str(), s.str());

		}

		TEST_METHOD(AddSymbolTable)
		{
			SymbolTable symbol_table;
			shared_ptr<BoundEntry> bound = shared_ptr<BoundEntry>(new BoundEntry("a"));
			symbol_table.add(bound);
			ostringstream s;
			symbol_table.print(s);
			ostringstream expected; expected << "Bound: a" << endl;
			Assert::AreEqual(expected.str(), s.str());
		}

		TEST_METHOD(FindSymbolTable)
		{
			SymbolTable symbol_table;
			shared_ptr<BoundEntry> bound = shared_ptr<BoundEntry>(new BoundEntry("a"));
			symbol_table.add(bound);
			shared_ptr<BoundEntry> result = dynamic_pointer_cast<BoundEntry>(symbol_table.find("Bound:a"));
			Assert::AreEqual(bound->text(), result->text());
		}

		TEST_METHOD(PrintPredicatesSymbolTable)
		{
			SymbolTable symbol_table;
			shared_ptr<BoundEntry> bound = shared_ptr<BoundEntry>(new BoundEntry("a"));
			symbol_table.add(bound);
			vector<shared_ptr<SymbolTableEntry>> v; v.push_back(bound);
			shared_ptr<PredicateEntry> predicate = shared_ptr<PredicateEntry>(new PredicateEntry(string("abs"), v));
			symbol_table.add(predicate);
			ostringstream s;
			symbol_table.print_predicates(s);
			ostringstream expected; expected << predicate->text() << endl;
			Assert::AreEqual(expected.str(), s.str());
		}

	};
}
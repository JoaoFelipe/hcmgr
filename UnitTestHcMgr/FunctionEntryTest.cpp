#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\UnboundEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\ConstantEntry.h"
#include "..\hcmgr\FunctionEntry.h"
#include "..\hcmgr\SymbolValueEntry.h"
#include "..\hcmgr\PredicateEntry.h"
#include "..\hcmgr\SymbolTable.h"
#include "..\hcmgr\SubstitutionList.h"
#include "..\hcmgr\SymbolTable.h"
#include "..\hcmgr\Parser.h"
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(FunctionEntryTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}
		
		TEST_METHOD(CreateFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(2, entry.value());
			Assert::AreEqual(string("[+ a 2]"), entry.text());
		}

		TEST_METHOD(CopyFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			FunctionEntry centry(entry);
			Assert::AreEqual(2, centry.value());
			Assert::AreEqual(string("[+ a 2]"), centry.text());
		}

		TEST_METHOD(CloneFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			shared_ptr<FunctionEntry> centry = dynamic_pointer_cast<FunctionEntry>(entry.clone());
			Assert::AreEqual(2, centry->value());
			Assert::AreEqual(string("[+ a 2]"), centry->text());
		}

		TEST_METHOD(GetConstantValueFunctionEntry_valid)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			shared_ptr<ConstantEntry> centry = dynamic_pointer_cast<ConstantEntry>(entry.get_constant_value());
			Assert::AreEqual(2, centry->value());
			Assert::AreEqual(true, bool(centry));
		}

		TEST_METHOD(GetConstantValueFunctionEntry_invalid)
		{
			shared_ptr<ConstantEntry> t1(new ConstantEntry(2));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(0));
			FunctionEntry entry(string("/"), t1, t2);
			shared_ptr<ConstantEntry> centry = dynamic_pointer_cast<ConstantEntry>(entry.get_constant_value());
			Assert::AreEqual(false, bool(centry));
		}

		TEST_METHOD(EqualOperatorFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<ConstantEntry> t3(new ConstantEntry(0));
			FunctionEntry entry1(string("+"), t1, t2);
			FunctionEntry entry2(string("+"), t1, t2);
			FunctionEntry entry3(string("+"), t3, t2);
			ConstantEntry entry4(0);
			SymbolTableEntry & e1 = entry1;
			SymbolTableEntry & e4 = entry4;
			Assert::AreEqual(true,  entry1 == entry2);
			Assert::AreEqual(false,  entry1 == entry3);
			Assert::AreEqual(false,  e1 == e4);
		}

		TEST_METHOD(TypeFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(string("Function"), entry.type());
		}

		TEST_METHOD(IsFunctionFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("*"), t1, t2);
			Assert::AreEqual(true, entry.is_function());
		}

		//SymbolValueEntry
		TEST_METHOD(IsEvaluableFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(true, entry.is_evaluable());
		}

		//SymbolEntry
		TEST_METHOD(EqualFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(true,  entry.equals("Function:[+ a 2]"));
			Assert::AreEqual(false,  entry.equals("Function:[+ 0 2]"));
			Assert::AreEqual(false,  entry.equals("2"));
		}

		TEST_METHOD(UnificationFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("-"), t1, t2);
			SubstitutionList subst;
			Assert::AreEqual(string("-2"),  entry.unification(subst));
		}

		TEST_METHOD(UnificationFunctionEntry_fail)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(0));
			FunctionEntry entry(string("%"), t1, t2);
			SubstitutionList subst;
			Assert::AreEqual(string("[% a 0]"),  entry.unification(subst));
		}

		
		TEST_METHOD(MatchesBoundEntry_Predicate)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> entry(new FunctionEntry(string("+"), t1, t2));
			SubstitutionList subst;
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), vector<shared_ptr<SymbolTableEntry>>()));
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Unbounds)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> entry(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<UnboundEntry> other(new UnboundEntry(string("B")));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Constant)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> entry(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<ConstantEntry> other(new ConstantEntry(2));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Bound)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(0));
			shared_ptr<FunctionEntry> entry(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<BoundEntry> other(new BoundEntry(string("b")));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Constant_Fail)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> entry(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<ConstantEntry> other(new ConstantEntry(1));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Bound_Fail)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> entry(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<BoundEntry> other(new BoundEntry(string("b")));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		//SymbolTableEntry
		TEST_METHOD(IsPredicateFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(false, entry.is_predicate());
		}

		TEST_METHOD(IsUnboundFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(false, entry.is_unbound());
		}


		TEST_METHOD(IsConstantFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(false, entry.is_constant());
		}

		TEST_METHOD(IsBoundFunctionEntry)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			FunctionEntry entry(string("+"), t1, t2);
			Assert::AreEqual(false, entry.is_bound());
		}

		TEST_METHOD(IsValidFunctionEntry_fail)
		{
			Parser parser("[/ 1 0]");
			shared_ptr<Symbol> func = parser.parse_function();
			shared_ptr<SymbolTableEntry> entry = func->convertToSymbolTableEntry();

			Assert::IsFalse(entry->is_valid());
		}

		TEST_METHOD(IsValidFunctionEntry_pass)
		{
			Parser parser("[/ 1 1]");
			shared_ptr<Symbol> func = parser.parse_function();
			shared_ptr<SymbolTableEntry> entry = func->convertToSymbolTableEntry();

			Assert::IsTrue(entry->is_valid());
		}
		



	};
}
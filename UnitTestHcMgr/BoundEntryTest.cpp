#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\UnboundEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\ConstantEntry.h"
#include "..\hcmgr\SymbolValueEntry.h"
#include "..\hcmgr\PredicateEntry.h"
#include "..\hcmgr\SymbolTable.h"
#include "..\hcmgr\SubstitutionList.h"
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(BoundEntryTest)
	{
	public:
		
		TEST_METHOD(CreateBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(0, entry.value());
			Assert::AreEqual(string("a"), entry.text());
		}

		TEST_METHOD(CopyBoundEntry)
		{
			BoundEntry entry(string("a"));
			BoundEntry centry(entry);
			Assert::AreEqual(0, centry.value());
			Assert::AreEqual(string("a"), centry.text());
		}

		TEST_METHOD(CloneBoundEntry)
		{
			BoundEntry entry(string("a"));
			shared_ptr<BoundEntry> centry = dynamic_pointer_cast<BoundEntry>(entry.clone());
			Assert::AreEqual(0, centry->value());
			Assert::AreEqual(string("a"), centry->text());
		}

		TEST_METHOD(GetConstantValueBoundEntry)
		{
			BoundEntry entry(string("a"));
			shared_ptr<ConstantEntry> centry = dynamic_pointer_cast<ConstantEntry>(entry.get_constant_value());

			Assert::AreEqual(0, centry->value());
		}

		TEST_METHOD(EqualOperatorBoundEntry)
		{
			BoundEntry entry1(string("a"));
			BoundEntry entry2(string("a"));
			BoundEntry entry3(string("b"));
			ConstantEntry entry4(0);
			SymbolTableEntry & e1 = entry1;
			SymbolTableEntry & e4 = entry4;
			Assert::AreEqual(true,  entry1 == entry2);
			Assert::AreEqual(false,  entry1 == entry3);
			Assert::AreEqual(false,  e1 == e4);
		}

		TEST_METHOD(TypeBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(string("Bound"), entry.type());
		}

		TEST_METHOD(IsBoundBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(true, entry.is_bound());
		}

		//SymbolValueEntry
		TEST_METHOD(IsEvaluableBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(true, entry.is_evaluable());
		}

		//SymbolEntry
		TEST_METHOD(EqualBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(true,  entry.equals("Bound:a"));
			Assert::AreEqual(false,  entry.equals("Bound:0"));
			Assert::AreEqual(false,  entry.equals("0"));
		}

		TEST_METHOD(UnificationBoundEntry)
		{
			BoundEntry entry(string("a"));
			SubstitutionList subst;
			Assert::AreEqual(string("0/a"),  entry.unification(subst));
		}

		
		TEST_METHOD(MatchesBoundEntry_Predicate)
		{
			shared_ptr<BoundEntry> entry(new BoundEntry(string("a")));
			SubstitutionList subst;
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), vector<shared_ptr<SymbolTableEntry>>()));
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Unbounds)
		{
			shared_ptr<BoundEntry> entry(new BoundEntry(string("a")));
			shared_ptr<UnboundEntry> other(new UnboundEntry(string("B")));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Constant)
		{
			shared_ptr<BoundEntry> entry(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> other(new ConstantEntry(0));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Bound)
		{
			shared_ptr<BoundEntry> entry(new BoundEntry(string("a")));
			shared_ptr<BoundEntry> other(new BoundEntry(string("b")));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Constant_Fail)
		{
			shared_ptr<BoundEntry> entry(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> other(new ConstantEntry(1));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesBoundEntry_Bound_Fail)
		{
			shared_ptr<BoundEntry> entry(new BoundEntry(string("a")));
			shared_ptr<BoundEntry> other(new BoundEntry(string("b")));
			other->value(1);
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		//SymbolTableEntry
		TEST_METHOD(IsPredicateBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(false, entry.is_predicate());
		}

		TEST_METHOD(IsUnboundBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(false, entry.is_unbound());
		}


		TEST_METHOD(IsConstantBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(false, entry.is_constant());
		}

		TEST_METHOD(IsFunctionBoundEntry)
		{
			BoundEntry entry(string("a"));
			Assert::AreEqual(false, entry.is_function());
		}
		



	};
}
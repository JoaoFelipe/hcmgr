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
	TEST_CLASS(ConstantEntrylTest)
	{
	public:
		
		TEST_METHOD(CreateConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(1, entry.value());
		}

		TEST_METHOD(CopyConstantEntry)
		{
			ConstantEntry entry(1);
			ConstantEntry centry(entry);
			Assert::AreEqual(1, centry.value());
		}

		TEST_METHOD(CloneConstantEntry)
		{
			ConstantEntry entry(1);
			shared_ptr<ConstantEntry> centry = dynamic_pointer_cast<ConstantEntry>(entry.clone());
			Assert::AreEqual(1, centry->value());
		}

		TEST_METHOD(GetConstantValueConstantEntry)
		{
			ConstantEntry entry(1);
			shared_ptr<ConstantEntry> centry = dynamic_pointer_cast<ConstantEntry>(entry.get_constant_value());

			Assert::AreEqual(1, centry->value());
		}

		TEST_METHOD(EqualOperatorConstantEntry)
		{
			ConstantEntry entry1(1);
			ConstantEntry entry2(1);
			ConstantEntry entry3(2);
			BoundEntry entry4(string("a"));
			SymbolTableEntry & e1 = entry1;
			SymbolTableEntry & e4 = entry4;
			Assert::AreEqual(true,  entry1 == entry2);
			Assert::AreEqual(false,  entry1 == entry3);
			Assert::AreEqual(false,  e1 == e4);
		}

		TEST_METHOD(TypeConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(string("Constant"), entry.type());
		}

		TEST_METHOD(TextConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(string("1"), entry.text());
		}

		TEST_METHOD(IsConstantConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(true, entry.is_constant());
		}

		//SymbolValueEntry
		TEST_METHOD(IsEvaluableConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(true, entry.is_evaluable());
		}

		//SymbolEntry
		TEST_METHOD(EqualConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(true,  entry.equals("Constant:1"));
			Assert::AreEqual(false,  entry.equals("1"));
			Assert::AreEqual(false,  entry.equals("Bound:1"));
		}

		TEST_METHOD(UnificationConstantEntry)
		{
			ConstantEntry entry(1);
			SubstitutionList subst;
			Assert::AreEqual(string("1"),  entry.unification(subst));
		}

		
		TEST_METHOD(MatchesConstantEntry_Predicate)
		{
			shared_ptr<ConstantEntry> entry(new ConstantEntry(1));
			SubstitutionList subst;
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), vector<shared_ptr<SymbolTableEntry>>()));
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesConstantEntry_Unbounds)
		{
			shared_ptr<ConstantEntry> entry(new ConstantEntry(1));
			shared_ptr<UnboundEntry> other(new UnboundEntry(string("B")));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesConstantEntry_Constant)
		{
			shared_ptr<ConstantEntry> entry(new ConstantEntry(1));
			shared_ptr<ConstantEntry> other(new ConstantEntry(1));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesConstantEntry_Bound)
		{
			shared_ptr<ConstantEntry> entry(new ConstantEntry(0));
			shared_ptr<BoundEntry> other(new BoundEntry(string("a")));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesConstantEntry_Constant_Fail)
		{
			shared_ptr<ConstantEntry> entry(new ConstantEntry(1));
			shared_ptr<ConstantEntry> other(new ConstantEntry(2));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesConstantEntry_Bound_Fail)
		{
			shared_ptr<ConstantEntry> entry(new ConstantEntry(1));
			shared_ptr<BoundEntry> other(new BoundEntry(string("a")));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		//SymbolTableEntry
		TEST_METHOD(IsPredicateConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(false, entry.is_predicate());
		}

		TEST_METHOD(IsUnboundConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(false, entry.is_unbound());
		}


		TEST_METHOD(IsBoundConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(false, entry.is_bound());
		}

		TEST_METHOD(IsFunctionConstantEntry)
		{
			ConstantEntry entry(1);
			Assert::AreEqual(false, entry.is_function());
		}
		



	};
}
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
	TEST_CLASS(UnboundEntrylTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}
		
		TEST_METHOD(CreateUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(string("A"), entry.text());
		}

		TEST_METHOD(CopyUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			UnboundEntry centry(entry);
			Assert::AreEqual(string("A"), entry.text());
		}

		TEST_METHOD(CloneUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			shared_ptr<UnboundEntry> centry = dynamic_pointer_cast<UnboundEntry>(entry.clone());
			Assert::AreEqual(string("A"), centry->text());
		}

		TEST_METHOD(EqualOperatorUnboundEntry)
		{
			UnboundEntry entry1(string("A"));
			UnboundEntry entry2(string("A"));
			UnboundEntry entry3(string("B"));
			BoundEntry entry4(string("1"));
			SymbolTableEntry & e1 = entry1;
			SymbolTableEntry & e4 = entry4;
			Assert::AreEqual(true,  entry1 == entry2);
			Assert::AreEqual(false,  entry1 == entry3);
			Assert::AreEqual(false,  e1 == e4);
		}

		TEST_METHOD(TypeUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(string("Unbound"), entry.type());
		}


		TEST_METHOD(IsUnboundUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(true, entry.is_unbound());
		}

		//SymbolEntry
		TEST_METHOD(EqualUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(true,  entry.equals("Unbound:A"));
			Assert::AreEqual(false,  entry.equals("A"));
			Assert::AreEqual(false,  entry.equals("Bound:A"));
		}

		TEST_METHOD(UnificationUnboundEntry_NotFound)
		{
			UnboundEntry entry(string("A"));
			SubstitutionList subst;
			Assert::AreEqual(string("A"),  entry.unification(subst));
		}

		TEST_METHOD(UnificationUnboundEntry_Constant)
		{
			shared_ptr<UnboundEntry> entry(new UnboundEntry(string("A")));
			SubstitutionList subst;
			shared_ptr<ConstantEntry> c(new ConstantEntry(1));
			subst.add(entry, c);
			Assert::AreEqual(string("1/A"),  entry->unification(subst));
		}

		TEST_METHOD(UnificationUnboundEntry_Bound)
		{
			shared_ptr<UnboundEntry> entry(new UnboundEntry(string("A")));
			SubstitutionList subst;
			shared_ptr<BoundEntry> c(new BoundEntry("a"));
			subst.add(entry, c);
			Assert::AreEqual(string("0/A"),  entry->unification(subst));
		}

		TEST_METHOD(MatchesUnboundEntry_Predicate)
		{
			shared_ptr<UnboundEntry> entry(new UnboundEntry(string("A")));
			SubstitutionList subst;
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), vector<shared_ptr<SymbolTableEntry>>()));
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesUnboundEntry_Unbounds)
		{
			shared_ptr<UnboundEntry> entry(new UnboundEntry(string("A")));
			shared_ptr<UnboundEntry> other(new UnboundEntry(string("B")));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesUnboundEntry_Constant)
		{
			shared_ptr<UnboundEntry> entry(new UnboundEntry(string("A")));
			shared_ptr<ConstantEntry> other(new ConstantEntry(1));
			SubstitutionList subst;
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesUnboundEntry_Constant_Constant)
		{
			shared_ptr<UnboundEntry> entry(new UnboundEntry(string("A")));
			shared_ptr<ConstantEntry> other(new ConstantEntry(1));
			SubstitutionList subst;
			subst.add(entry, other);
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesUnboundEntry_Constant_Constant_Fail)
		{
			shared_ptr<UnboundEntry> entry(new UnboundEntry(string("A")));
			shared_ptr<ConstantEntry> replace(new ConstantEntry(1));
			shared_ptr<ConstantEntry> other(new ConstantEntry(2));
			SubstitutionList subst;
			subst.add(entry, replace);
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		//SymbolTableEntry
		TEST_METHOD(IsPredicateUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(false, entry.is_predicate());
		}

		TEST_METHOD(IsConstantUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(false, entry.is_constant());
		}

		TEST_METHOD(IsBoundUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(false, entry.is_bound());
		}

		TEST_METHOD(IsFunctionUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(false, entry.is_function());
		}
		
		TEST_METHOD(IsEvaluableUnboundEntry)
		{
			UnboundEntry entry(string("A"));
			Assert::AreEqual(false, entry.is_evaluable());
		}


	};
}
#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\UnboundEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\ConstantEntry.h"
#include "..\hcmgr\FunctionEntry.h"
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
	TEST_CLASS(PredicateEntryTest)
	{
	public:
		
		TEST_METHOD(CreatePredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(string("abs"), entry.text());
		}

		TEST_METHOD(CopyPredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			PredicateEntry centry(entry);
			Assert::AreEqual(string("abs"), centry.text());
		}

		TEST_METHOD(ClonePredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			shared_ptr<PredicateEntry> centry = dynamic_pointer_cast<PredicateEntry>(entry.clone());
			Assert::AreEqual(string("abs"), centry->text());
		}


		TEST_METHOD(EqualOperatorPredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			vector<shared_ptr<SymbolTableEntry>> symbols2;
			symbols2.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));

			PredicateEntry entry1(string("abs"), symbols);
			PredicateEntry entry2(string("abs"), symbols);
			PredicateEntry entry3(string("sum"), symbols);
			PredicateEntry entry4(string("abs"), symbols2);
			ConstantEntry entry5(0);
			PredicateEntry entry6(string("abs"), symbols2);
			SymbolTableEntry & e1 = entry1;
			SymbolTableEntry & e5 = entry5;
			Assert::AreEqual(true,  entry1 == entry2);
			Assert::AreEqual(false,  entry1 == entry3);
			Assert::AreEqual(false,  entry1 == entry4);
			Assert::AreEqual(true,  entry4 == entry6);
			Assert::AreEqual(false,  e1 == e5);
		}

		TEST_METHOD(NamePredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(string("abs"), entry.name());
		}

		TEST_METHOD(TypePredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(string("Predicate"), entry.type());
		}

		TEST_METHOD(TextPredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			symbols.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(string("abs 0"), entry.text());
		}

		TEST_METHOD(IsPredicatePredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(true, entry.is_predicate());
		}

		//SymbolEntry
		TEST_METHOD(UnificationPredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			symbols.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			symbols.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			shared_ptr<UnboundEntry> replace(new UnboundEntry(string("B")));
			symbols.push_back(replace);
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> f(new FunctionEntry(string("+"), t1, t2));
			symbols.push_back(f);
			PredicateEntry entry(string("abs"), symbols);
			SubstitutionList subst;
			subst.add(replace, shared_ptr<ConstantEntry>(new ConstantEntry(2)));
			Assert::AreEqual(string("abs 0 0/a A 2/B 2"),  entry.unification(subst));
		}

		
		TEST_METHOD(MatchesPredicateEntry_NonPredicate)
		{
			shared_ptr<PredicateEntry> entry(new PredicateEntry(string("abs"), vector<shared_ptr<SymbolTableEntry>>()));
			shared_ptr<BoundEntry> other(new BoundEntry(string("a")));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesPredicateEntry_DifferentName)
		{
			shared_ptr<PredicateEntry> entry(new PredicateEntry(string("abs"), vector<shared_ptr<SymbolTableEntry>>()));
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs2"), vector<shared_ptr<SymbolTableEntry>>()));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesPredicateEntry_DifferentCount)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			symbols.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			shared_ptr<PredicateEntry> entry(new PredicateEntry(string("abs"), symbols));
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), vector<shared_ptr<SymbolTableEntry>>()));
			SubstitutionList subst;
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesPredicateEntry_Match_Equals)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			symbols.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			symbols.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			shared_ptr<UnboundEntry> replace(new UnboundEntry(string("B")));
			symbols.push_back(replace);
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> f(new FunctionEntry(string("+"), t1, t2));
			symbols.push_back(f);
			shared_ptr<PredicateEntry> entry(new PredicateEntry(string("abs"), symbols));
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), symbols));
			SubstitutionList subst;
			subst.add(replace, shared_ptr<ConstantEntry>(new ConstantEntry(2)));
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesPredicateEntry_Match_Constant_Bound_Unbound)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> f(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<UnboundEntry> replace(new UnboundEntry(string("B")));
			
			vector<shared_ptr<SymbolTableEntry>> symbols;
			symbols.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			symbols.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			symbols.push_back(replace);
			symbols.push_back(f);
			vector<shared_ptr<SymbolTableEntry>> symbols2;
			symbols2.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols2.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			symbols2.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			symbols2.push_back(replace);
			symbols2.push_back(f);
			
			shared_ptr<PredicateEntry> entry(new PredicateEntry(string("abs"), symbols));
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), symbols2));
			SubstitutionList subst;
			subst.add(replace, shared_ptr<ConstantEntry>(new ConstantEntry(2)));
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesPredicateEntry_Match_Unbound_Fail)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> f(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<UnboundEntry> replace(new UnboundEntry(string("B")));
			
			vector<shared_ptr<SymbolTableEntry>> symbols;
			symbols.push_back(f);
			symbols.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			symbols.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			symbols.push_back(replace);
			
			vector<shared_ptr<SymbolTableEntry>> symbols2;
			symbols2.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			symbols2.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols2.push_back(replace);
			symbols2.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			symbols2.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			
			shared_ptr<PredicateEntry> entry(new PredicateEntry(string("abs"), symbols));
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), symbols2));
			SubstitutionList subst;
			subst.add(replace, shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			Assert::AreEqual(false,  entry->matches(other, subst));
		}

		TEST_METHOD(MatchesPredicateEntry_Match_Unbound)
		{
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> f(new FunctionEntry(string("+"), t1, t2));
			shared_ptr<UnboundEntry> replace(new UnboundEntry(string("B")));
			
			vector<shared_ptr<SymbolTableEntry>> symbols;
			symbols.push_back(f);
			symbols.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			symbols.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			symbols.push_back(replace);
			
			vector<shared_ptr<SymbolTableEntry>> symbols2;
			symbols2.push_back(shared_ptr<UnboundEntry>(new UnboundEntry(string("A"))));
			symbols2.push_back(shared_ptr<BoundEntry>(new BoundEntry(string("a"))));
			symbols2.push_back(replace);
			symbols2.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(2)));
			symbols2.push_back(shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			
			shared_ptr<PredicateEntry> entry(new PredicateEntry(string("abs"), symbols));
			shared_ptr<PredicateEntry> other(new PredicateEntry(string("abs"), symbols2));
			SubstitutionList subst;
			subst.add(replace, shared_ptr<ConstantEntry>(new ConstantEntry(0)));
			Assert::AreEqual(true,  entry->matches(other, subst));
		}

		//SymbolTableEntry
		TEST_METHOD(IsBoundPredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(false, entry.is_bound());
		}

		TEST_METHOD(IsUnboundPredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(false, entry.is_unbound());
		}


		TEST_METHOD(IsConstantPredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(false, entry.is_constant());
		}

		TEST_METHOD(IsFunctionBoundEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(false, entry.is_function());
		}
		
		TEST_METHOD(IsEvaluablePredicateEntry)
		{
			vector<shared_ptr<SymbolTableEntry>> symbols;
			PredicateEntry entry(string("abs"), symbols);
			Assert::AreEqual(false, entry.is_evaluable());
		}



	};
}
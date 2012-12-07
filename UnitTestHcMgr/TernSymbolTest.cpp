#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\TermSymbol.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\ConstantEntry.h"
#include "..\hcmgr\SymbolTable.h"
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(TermSymbolTest)
	{
	public:
		
		TEST_METHOD(CreateBoundTermSymbol)
		{
			TermSymbol symbol(string("a"));
			Assert::AreEqual(string("a"), symbol.value());
		}

		TEST_METHOD(CreateNumberTermSymbol)
		{
			TermSymbol symbol(string("1"));
			Assert::AreEqual(string("1"), symbol.value());
		}

		TEST_METHOD(CopyTermSymbol)
		{
			TermSymbol symbol(string("a"));
			TermSymbol csymbol(symbol);
			Assert::AreEqual(string("a"), csymbol.value());
		}

		TEST_METHOD(CloneTermSymbol)
		{
			TermSymbol symbol(string("1"));
			shared_ptr<TermSymbol> csymbol = dynamic_pointer_cast<TermSymbol>(symbol.clone());
			Assert::AreEqual(string("1"), csymbol->value());
		}

		TEST_METHOD(SetValueTermSymbol)
		{
			TermSymbol symbol(string("a"));
			symbol.value("b");
			Assert::AreEqual(string("b"), symbol.value());
		}

		TEST_METHOD(TextBoundTermSymbol)
		{
			TermSymbol symbol(string("a"));
			Assert::AreEqual(string("Variable:a"), symbol.text());
		}

		TEST_METHOD(TextUnBoundTermSymbol)
		{
			TermSymbol symbol(string("1"));
			Assert::AreEqual(string("Constant:1"), symbol.text());
		}

		TEST_METHOD(PrintTermSymbol)
		{
			TermSymbol symbol(string("a"));
			ostringstream s;
			symbol.print(s);
			ostringstream result; result << "a";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(convertToSymbolTableEntryTermSymbol_New)
		{
			TermSymbol symbol(string("a"));
			SymbolTable table;
			BoundEntry expected("a");
			shared_ptr<BoundEntry> result = dynamic_pointer_cast<BoundEntry>(symbol.convertToSymbolTableEntry(table));
			Assert::AreEqual(expected.text(), result->text());
		}

		TEST_METHOD(convertToSymbolTableEntryTermSymbol_Existent)
		{
			TermSymbol symbol(string("1"));
			SymbolTable table;
			shared_ptr<ConstantEntry> expected = shared_ptr<ConstantEntry>(new ConstantEntry(1));
			table.add(expected);
			shared_ptr<SymbolTableEntry> expected_address = table.find(symbol.text());
			shared_ptr<SymbolTableEntry> result = symbol.convertToSymbolTableEntry(table);
			Assert::AreEqual(expected_address->text(), result->text());
			ostringstream e_address; e_address << dynamic_pointer_cast<void>(expected_address);
			ostringstream r_address; r_address << dynamic_pointer_cast<void>(result);
			Assert::AreEqual(e_address.str(), r_address.str());
		}

		TEST_METHOD(GetRealSymbolTableEntryTermSymbol_Bound)
		{
			TermSymbol symbol(string("a"));
			BoundEntry expected("a");
			unsigned int one = 1;
			vector<shared_ptr<SymbolTableEntry>> result = symbol.getRealSymbolTableEntry();
			Assert::AreEqual(one, result.size());
			Assert::AreEqual(expected.text(), result[0]->text());
		}

		TEST_METHOD(GetRealSymbolTableEntryTermSymbol_Number)
		{
			TermSymbol symbol(string("1"));
			ConstantEntry expected(1);
			unsigned int one = 1;
			vector<shared_ptr<SymbolTableEntry>> result = symbol.getRealSymbolTableEntry();
			Assert::AreEqual(one, result.size());
			Assert::AreEqual(expected.text(), result[0]->text());
		}

	};
}
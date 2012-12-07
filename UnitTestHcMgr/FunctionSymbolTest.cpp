#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\FunctionEntry.h"
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
	TEST_CLASS(FunctionSymbolTest)
	{
	public:
		
		TEST_METHOD(CreateFunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			Assert::AreEqual(string("[+ a 2]"), symbol.text());
		}

		TEST_METHOD(CopyFunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			FunctionSymbol csymbol(symbol);
			Assert::AreEqual(string("[+ a 2]"), csymbol.text());
		}

		TEST_METHOD(CloneFunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			shared_ptr<FunctionSymbol> csymbol = dynamic_pointer_cast<FunctionSymbol>(symbol.clone());
			Assert::AreEqual(string("[+ a 2]"), csymbol->text());
		}

		TEST_METHOD(GetSetOperationFunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			Assert::AreEqual(string("+"), symbol.operation());
			symbol.operation("-");
			Assert::AreEqual(string("-"), symbol.operation());
		}

		TEST_METHOD(GetSetTerm1FunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			Assert::AreEqual(string("a"), symbol.term1());
			symbol.term1("b");
			Assert::AreEqual(string("b"), symbol.term1());
		}
		
		TEST_METHOD(GetSetTerm2FunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			Assert::AreEqual(string("2"), symbol.term2());
			symbol.term2("b");
			Assert::AreEqual(string("b"), symbol.term2());
		}

		TEST_METHOD(PrintFunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			ostringstream s;
			symbol.print(s);
			ostringstream result; result << "[+ a 2]";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(ConvertToSymbolTableEntryFunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			SymbolTable table;
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			shared_ptr<FunctionEntry> expected(new FunctionEntry(string("+"), t1, t2));

			shared_ptr<FunctionEntry> result = dynamic_pointer_cast<FunctionEntry>(symbol.convertToSymbolTableEntry(table));
			Assert::AreEqual(expected->text(), result->text());
		}

		TEST_METHOD(GetRealSymbolTableEntryFunctionSymbol)
		{
			FunctionSymbol symbol(string("+"), string("a"), string("2"));
			shared_ptr<BoundEntry> t1(new BoundEntry(string("a")));
			shared_ptr<ConstantEntry> t2(new ConstantEntry(2));
			vector<shared_ptr<SymbolTableEntry>> result = symbol.getRealSymbolTableEntry();
			unsigned int two = 2;
			Assert::AreEqual(two, result.size());
			Assert::AreEqual(t1->text(), result[0]->text());
			Assert::AreEqual(t2->text(), result[1]->text());



		}

	};
}
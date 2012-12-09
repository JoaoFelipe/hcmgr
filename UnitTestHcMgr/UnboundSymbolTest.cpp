#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\UnboundSymbol.h"
#include "..\hcmgr\UnboundEntry.h"
#include "..\hcmgr\SymbolTable.h"
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(UnboundSymbolTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}
		
		TEST_METHOD(CreateUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			Assert::AreEqual(string("A"), symbol.value());
		}

		TEST_METHOD(CopyUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			UnboundSymbol csymbol(symbol);
			Assert::AreEqual(string("A"), csymbol.value());
		}

		TEST_METHOD(CloneUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			shared_ptr<UnboundSymbol> csymbol = dynamic_pointer_cast<UnboundSymbol>(symbol.clone());
			Assert::AreEqual(string("A"), csymbol->value());
		}

		TEST_METHOD(SetValueUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			symbol.value("B");
			Assert::AreEqual(string("B"), symbol.value());
		}

		TEST_METHOD(TextUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			Assert::AreEqual(string("Unbound:A"), symbol.text());
		}

		TEST_METHOD(PrintUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			ostringstream s;
			symbol.print(s);
			ostringstream result; result << "A";
			Assert::AreEqual(result.str(), s.str());
		}

		TEST_METHOD(ConvertToSymbolTableEntryUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			UnboundEntry expected("A");
			shared_ptr<UnboundEntry> result = dynamic_pointer_cast<UnboundEntry>(symbol.convertToSymbolTableEntry());
			Assert::AreEqual(expected.text(), result->text());
		}

		TEST_METHOD(GetRealSymbolTableEntryUnboundSymbol)
		{
			UnboundSymbol symbol(string("A"));
			unsigned int zero = 0;
			Assert::AreEqual(zero, symbol.getRealSymbolTableEntry().size());
		}

	};
}
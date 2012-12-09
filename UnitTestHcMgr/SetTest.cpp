#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\SymbolTable.h"

#include "..\hcmgr\const.h"
#include "..\hcmgr\hcset.h"


#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(SetTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}

		TEST_METHOD(set_symbol_table_empty)
		{
			ostringstream s;
			Assert::AreEqual(0, set_variable(string("a 2"), s));
			ostringstream result;
			Assert::AreEqual(result.str(), s.str());
			shared_ptr<BoundEntry> bound = dynamic_pointer_cast<BoundEntry>(SymbolTable::instance()->find("Bound:a"));
			Assert::AreEqual(2, bound->value());
		}

		TEST_METHOD(set_symbol_table_with_var)
		{
			BoundEntry b("a");
			ostringstream s;
			Assert::AreEqual(0, set_variable(string("a 2"), s));
			ostringstream result;
			Assert::AreEqual(result.str(), s.str());
			shared_ptr<BoundEntry> bound = dynamic_pointer_cast<BoundEntry>(SymbolTable::instance()->find("Bound:a"));
			Assert::AreEqual(2, bound->value());
		}

		TEST_METHOD(set_symbol_table_fail_bound)
		{
			ostringstream s;
			Assert::AreEqual(1, set_variable(string("A 2"), s));
			ostringstream result; result << "Invalid Bound Syntax" << endl;
			Assert::AreEqual(result.str(), s.str());
		}


		TEST_METHOD(set_symbol_table_fail_number)
		{
			ostringstream s;
			Assert::AreEqual(1, set_variable(string("a a"), s));
			ostringstream result; result << "Invalid Number Syntax" << endl;
			Assert::AreEqual(result.str(), s.str());
		}
	};
}
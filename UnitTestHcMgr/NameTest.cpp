#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\Name.h"
#include <iostream>
#include <sstream>
#include "..\hcmgr\SymbolTable.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(NameTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}
		
		TEST_METHOD(CreateName)
		{
			Name name(string("bla"));
			Assert::AreEqual(string("bla"), name.value());
		}

		TEST_METHOD(CopyName)
		{
			Name name(string("bla"));
			Name name2(name);
			Assert::AreEqual(string("bla"), name2.value());
		}

		TEST_METHOD(SetValueName)
		{
			Name name(string("bla"));
			name.value("new");
			Assert::AreEqual(string("new"), name.value());
		}

		TEST_METHOD(PrintName)
		{
			Name name(string("bla"));
			ostringstream s;
			name.print(s);
			ostringstream result; result << "bla";
			Assert::AreEqual(result.str(), s.str());
		}

	};
}
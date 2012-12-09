#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "..\hcmgr\FunctionSymbol.h"
#include "..\hcmgr\FunctionEntry.h"
#include "..\hcmgr\BoundEntry.h"
#include "..\hcmgr\UnboundSymbol.h"
#include "..\hcmgr\TermSymbol.h"
#include "..\hcmgr\HornClause.h"
#include "..\hcmgr\Head.h"
#include "..\hcmgr\Body.h"
#include "..\hcmgr\Parser.h"

#include "..\hcmgr\ConstantEntry.h"
#include "..\hcmgr\SymbolTable.h"
#include "..\hcmgr\Predicate.h"
#include "..\hcmgr\Name.h"


#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestHcMgr
{		
	TEST_CLASS(ParserTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Setup) 
		{
			SymbolTable::instance()->erase();
		}

		TEST_METHOD(EofParser)
		{
			Parser parser("aaa");
			Assert::IsFalse(parser.eof());
			parser.next();
			Assert::IsTrue(parser.eof());
		}

		TEST_METHOD(ReadCurrentParser)
		{
			Parser parser("aaa");
			string current;
			parser.read_current(current);
			Assert::AreEqual(string("aaa"), current);
		}

		TEST_METHOD(CheckLeftParenthesisParser_Fail)
		{
			Parser parser("aaa");
			Assert::IsFalse(parser.check_left_parenthesis());
		}

		TEST_METHOD(CheckLeftParenthesisParser_Pass)
		{
			Parser parser("(aaa");
			Assert::IsTrue(parser.check_left_parenthesis());
		}

		TEST_METHOD(CheckRightParenthesisParser_Fail)
		{
			Parser parser("aaa");
			Assert::IsFalse(parser.check_right_parenthesis());
		}

		TEST_METHOD(CheckRightParenthesisParser_Pass)
		{
			Parser parser(")aaa");
			Assert::IsTrue(parser.check_right_parenthesis());
		}

		TEST_METHOD(CheckLeftBracketParser_Fail)
		{
			Parser parser("aaa");
			Assert::IsFalse(parser.check_left_bracket());
		}

		TEST_METHOD(CheckLeftBracketParser_Pass)
		{
			Parser parser("[aaa");
			Assert::IsTrue(parser.check_left_bracket());
		}

		TEST_METHOD(CheckRightBracketParser_Fail)
		{
			Parser parser("aaa");
			Assert::IsFalse(parser.check_right_bracket());
		}

		TEST_METHOD(CheckRightBracketParser_Pass)
		{
			Parser parser("]aaa");
			Assert::IsTrue(parser.check_right_bracket());
		}

		TEST_METHOD(CheckLabelParser_Fail)
		{
			Parser parser("]aaa");
			Assert::IsFalse(parser.check_label());
		}

		TEST_METHOD(CheckLabelParser_Fail_Zero)
		{
			Parser parser("");
			Assert::IsFalse(parser.check_label());
		}

		TEST_METHOD(CheckLabelParser_pass_lowercase)
		{
			Parser parser("aaa");
			Assert::IsTrue(parser.check_label());
		}

		TEST_METHOD(CheckLabelParser_pass_uppercase)
		{
			Parser parser("AAA");
			Assert::IsTrue(parser.check_label());
		}

		
		TEST_METHOD(CheckNumberParser_Fail)
		{
			Parser parser("]aaa");
			Assert::IsFalse(parser.check_number());
		}

		TEST_METHOD(CheckNumberParser_Fail_Zero)
		{
			Parser parser("");
			Assert::IsFalse(parser.check_number());
		}

		TEST_METHOD(CheckNumberParser_pass)
		{
			Parser parser("123");
			Assert::IsTrue(parser.check_number());
		}

		TEST_METHOD(CheckUnboundParser_Fail)
		{
			Parser parser("a");
			Assert::IsFalse(parser.check_unbound());
		}

		TEST_METHOD(CheckUnboundParser_Fail_Size)
		{
			Parser parser("abc");
			Assert::IsFalse(parser.check_unbound());
		}

		TEST_METHOD(CheckUnboundParser_pass)
		{
			Parser parser("A");
			Assert::IsTrue(parser.check_unbound());
		}

		TEST_METHOD(CheckBoundParser_Fail)
		{
			Parser parser("A");
			Assert::IsFalse(parser.check_bound());
		}

		TEST_METHOD(CheckBoundParser_Fail_Size)
		{
			Parser parser("ABC");
			Assert::IsFalse(parser.check_bound());
		}

		TEST_METHOD(CheckBoundParser_pass)
		{
			Parser parser("a");
			Assert::IsTrue(parser.check_bound());
		}

		TEST_METHOD(CheckOperatorParser_Fail)
		{
			Parser parser("A");
			Assert::IsFalse(parser.check_operator());
		}

		TEST_METHOD(CheckOperatorParser_Fail_Size)
		{
			Parser parser("");
			Assert::IsFalse(parser.check_operator());
		}

		TEST_METHOD(CheckOperatorParser_pass)
		{
			Parser parser("+ - * / %");
			Assert::IsTrue(parser.check_operator());
			parser.next();
			Assert::IsTrue(parser.check_operator());
			parser.next();
			Assert::IsTrue(parser.check_operator());
			parser.next();
			Assert::IsTrue(parser.check_operator());
			parser.next();
			Assert::IsTrue(parser.check_operator());
		}

		TEST_METHOD(CheckTermParser_Fail)
		{
			Parser parser("A");
			Assert::IsFalse(parser.check_term());
		}

		TEST_METHOD(CheckTermParser_Fail_Size)
		{
			Parser parser("ABC");
			Assert::IsFalse(parser.check_term());
		}

		TEST_METHOD(CheckTermParser_pass_bound)
		{
			Parser parser("a");
			Assert::IsTrue(parser.check_term());
		}

		TEST_METHOD(CheckTermParser_pass_number)
		{
			Parser parser("1");
			Assert::IsTrue(parser.check_term());
		}


		TEST_METHOD(ParseHornClauseParser_FailLeftParenthesis)
		{
			Parser parser("abs 1");
			Assert::IsFalse(parser.parse_horn_clause());
		}

		TEST_METHOD(ParseHornClauseParser_FailHead)
		{
			Parser parser("(abs 1");
			Assert::IsFalse(parser.parse_horn_clause());
		}

		TEST_METHOD(ParseHornClauseParser_FailRightParenthesis)
		{
			Parser parser("((abs 1)");
			Assert::IsFalse(parser.parse_horn_clause());
		}

		TEST_METHOD(ParseHornClauseParser_FailBody)
		{
			Parser parser("((abs 1) ())");
			Assert::IsFalse(parser.parse_horn_clause());
		}

		TEST_METHOD(ParseHornClauseParser_PassWithoutBody)
		{
			Parser parser("((abs 1))");
			Assert::IsTrue(parser.parse_horn_clause());
		}

		TEST_METHOD(ParseHornClauseParser_PassWithBody)
		{
			Parser parser("((abs 1) ((sum 2)))");
			Assert::IsTrue(parser.parse_horn_clause());
		}

		TEST_METHOD(ParseHead_FailPredicate)
		{
			Parser parser("abs 1");
			Assert::IsFalse(parser.parse_head());
		}

		TEST_METHOD(ParseHead_Pass)
		{
			Parser parser("(abs 1)");
			Assert::IsTrue(parser.parse_head());
		}

		TEST_METHOD(ParsePredicate_FailLeftParenthesis)
		{
			Parser parser("abs 1)");
			Assert::IsFalse(parser.parse_predicate());
		}

		TEST_METHOD(ParsePredicate_FailName)
		{
			Parser parser("(1)");
			Assert::IsFalse(parser.parse_predicate());
		}

		TEST_METHOD(ParsePredicate_FailSymbols)
		{
			Parser parser("(a (1)");
			Assert::IsFalse(parser.parse_predicate());
		}

		TEST_METHOD(ParsePredicate_FailRightParenthesis)
		{
			Parser parser("(abs 1");
			Assert::IsFalse(parser.parse_predicate());
		}

		TEST_METHOD(ParsePredicate_Pass)
		{
			Parser parser("(abs 1 a A)");
			Assert::IsTrue(parser.parse_predicate());
		}

		TEST_METHOD(ParsePredicate_Pass2)
		{
			Parser parser("(abs [ / 1 x ])");
			Assert::IsTrue(parser.parse_predicate());
		}

		TEST_METHOD(ParseName_Fail)
		{
			Parser parser("(abs 1");
			Assert::IsFalse(parser.parse_name());
		}

		TEST_METHOD(ParseName_Pass)
		{
			Parser parser("abs");
			Assert::IsTrue(parser.parse_name());
		}

		TEST_METHOD(ParseSymbols_FailEOF)
		{
			Parser parser("a b c");
			Assert::IsFalse(parser.parse_symbols());
		}

		TEST_METHOD(ParseSymbols_Pass)
		{
			Parser parser("a b c)");
			Assert::IsTrue(parser.parse_symbols());
		}

		TEST_METHOD(ParseSymbol_PassUnbound)
		{
			Parser parser("A");
			Assert::IsTrue(parser.parse_symbol());
		}

		TEST_METHOD(ParseSymbol_PassTermNumber)
		{
			Parser parser("1");
			Assert::IsTrue(parser.parse_symbol());
		}

		TEST_METHOD(ParseSymbol_PassTermBound)
		{
			Parser parser("a");
			Assert::IsTrue(parser.parse_symbol());
		}

		TEST_METHOD(ParseSymbol_PassFunction)
		{
			Parser parser("[ + a b ]");
			Assert::IsTrue(parser.parse_symbol());
		}

		TEST_METHOD(ParseFunction_FailLeftBrackets)
		{
			Parser parser("+ a b ]");
			Assert::IsFalse(parser.parse_function());
		}

		TEST_METHOD(ParseFunction_FailOperator)
		{
			Parser parser("[ a b ]");
			Assert::IsFalse(parser.parse_function());
		}

		TEST_METHOD(ParseFunction_FailFirstTerm)
		{
			Parser parser("[ + A b ]");
			Assert::IsFalse(parser.parse_function());
		}

		TEST_METHOD(ParseFunction_FailSecondTerm)
		{
			Parser parser("[ + a B ]");
			Assert::IsFalse(parser.parse_function());
		}

		TEST_METHOD(ParseFunction_FailRightBrackets)
		{
			Parser parser("[ + a b");
			Assert::IsFalse(parser.parse_function());
		}

		TEST_METHOD(ParseFunction_PassFunction)
		{
			Parser parser("[ + a b ]");
			Assert::IsTrue(parser.parse_function());
		}

		TEST_METHOD(ParseFunction_PassFunctionNoSpace)
		{
			Parser parser("[+ a b]");
			Assert::IsTrue(parser.parse_function());
		}

		TEST_METHOD(ParseBody_FailLeftParenthesis)
		{
			Parser parser(")");
			Assert::IsFalse(parser.parse_body());
		}

		TEST_METHOD(ParseBody_FailPredicate)
		{
			Parser parser("((()");
			Assert::AreEqual(0, parser.parse_body()->size());
		}

		TEST_METHOD(ParseBody_FailRightParenthesis)
		{
			Parser parser("((a)");
			Assert::AreEqual(0, parser.parse_body()->size());
		}

		TEST_METHOD(ParseBody_Pass)
		{
			Parser parser("((a)))");
			Assert::IsTrue(parser.parse_body());
		}

		TEST_METHOD(ParseGoal_FailPredicate)
		{
			Parser parser("abs 1");
			Assert::IsFalse(parser.parse_goal());
		}

		TEST_METHOD(ParseGoal_Pass)
		{
			Parser parser("(abs 1)");
			Assert::IsTrue(parser.parse_goal());
		}

		TEST_METHOD(ParseBoundEntry_Pass)
		{
			Parser parser("a");
			Assert::IsTrue(parser.parse_bound_entry());
		}

		TEST_METHOD(ParseBoundEntry_Fail)
		{
			Parser parser("A");
			Assert::IsFalse(parser.parse_bound_entry());
		}

		TEST_METHOD(ParseBoundEntry_Fail_number)
		{
			Parser parser("1");
			Assert::IsFalse(parser.parse_bound_entry());
		}

		TEST_METHOD(ParseNumber_Fail)
		{
			Parser parser("a");
			Assert::IsFalse(parser.parse_number());
		}

		TEST_METHOD(ParseNumber_Pass)
		{
			Parser parser("1");
			Assert::IsTrue(parser.parse_number());
		}

		TEST_METHOD(ParseNumber_Pass_CheckNumber)
		{
			Parser parser("1");
			Assert::AreEqual(1, *parser.parse_number());
		}
	};
}
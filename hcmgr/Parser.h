/**
	Parser.h
	Class name: Parser 
	Written by: Amanda Silva and João Pimentel
	For:		CSE 425 Lab 3
	Purpose:    Declaration of the class Parser
*/

#ifndef PARSER_H
#define PARSER_H 

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "HornClause.h"
#include <memory>
#include "BoundEntry.h"
using namespace std; 


class Parser {
public:


// @brief Initializes the variables with default values
	Parser();

	
// @brief Initializes the variables with default values and a string to be parsed
// @param string with the content to be parsed
	Parser(const string & str);


// @brief initializes the filename with a received parameter, opens it and initializes other variables with default values
// @param filename for the file with the tokens to be read
// @return bool
	bool open(const string & filename);

// @brief initialize the parser to be able to parse
// @param string with the content to be parsed
	void Parser::start(const string & str);

// @brief verifies if the parser reached the end of the file
// @return bool
	bool eof() const;

// @brief if it is not the end of the file, it starts parsing the first position of the next possible line
// @return void
	void next_line();


// @brief reads current token ignoring spaces and line breaks  
// @param result is a reference to an empty string variable that will receive the value of the valid read token 
// @return void
	void read_current(string & result);

// @brief similar to read_current method logic, but it just moves the position to start reading the next token 
// @see Parser::read_current(string & result)
// @return void
	void next();

// @brief checks if the current token is a left parenthesis 
// @return bool
	bool check_left_parenthesis();

// @brief checks if the current token is a right parenthesis 
// @return bool
	bool check_right_parenthesis();
	
// @brief checks if the current token is a left bracket 
// @return bool
	bool check_left_bracket();

// @brief checks if the current token is a right bracket 
// @return bool
	bool check_right_bracket();

// @brief checks if the current token is a label (it is all uppercase or all lowercase)
// @return bool
	bool check_label();

// @brief checks if the current token is a number 
// @return bool
	bool check_number();

// @brief checks if the current token is a unbound 
// @return bool
	bool check_unbound(); 

// @brief checks if the current token is a bound 
// @return bool
	bool check_bound();


// @brief checks if the current token is a operator
// @return bool
	bool check_operator();

// @brief checks if the current token is a term (number or bound) 
// @return bool
	bool check_term();

// @brief checks the Horn Clause syntax. 
// @return shared_ptr<HornClause>
	shared_ptr<HornClause> parse_horn_clause();

// @brief checks the Head syntax. 
// @return shared_ptr<Head>
	shared_ptr<Head> parse_head();

// @brief checks the Predicate syntax. 
// @return shared_ptr<Predicate>
	shared_ptr<Predicate> parse_predicate();

// @brief checks the Name syntax. 
// @return shared_ptr<Name>
	shared_ptr<Name> parse_name();

// @brief checks the Symbol syntax list. 
// @return shared_ptr<vector<shared_ptr<Symbol>>>
	shared_ptr<vector<shared_ptr<Symbol>>> Parser::parse_symbols();

// @brief checks the Symbol syntax.  
// @return shared_ptr<Symbol>
	shared_ptr<Symbol> parse_symbol();

// @brief checks the Function syntax. 
// @return shared_ptr<Symbol>
	shared_ptr<Symbol> parse_function(); 

// @brief checks the Body syntax. 
// @return shared_ptr<Body>
	shared_ptr<Body> parse_body();

// @brief checks the Predicate syntax. 
// @return shared_ptr<HornClause>
	shared_ptr<HornClause> parse_goal();

// @brief checks the Bound syntax. 
// @return shared_ptr<BoundEntry>
	shared_ptr<BoundEntry> parse_bound_entry();

// @brief checks the Number syntax. 
// @return shared_ptr<int>
	shared_ptr<int> parse_number();

private:
	string _file_name;
	string _current_line;
	stringstream _file;
	unsigned int _position;
};



#endif
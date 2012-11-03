/**
	Parser.h
	Class name: Parser 
	Written by: Amanda Silva and João Pimentel
	For:		CSE 425 Lab 2 - Question 4 - Part 1
	Purpose:    Declaration of the class Parser
*/

#ifndef PARSER_H
#define PARSER_H 

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "HornClause.h"

using namespace std; 


class Parser {
public:


//  @brief Parser() - Default Constructor of the Parser class - Initializes the variables with default values
	Parser();


//  @brief Parser::open(const string & filename) - initializes the filename with a received parameter, opens it and initializes other variables with default values
//  @param filename for the file with the tokens to be read
//  @return void
	void open(const string & filename);

//  @brief Parser::is_open() - verifies if the file is open
//  @return bool
	bool is_open() const;

//  @brief Parser::eof() - verifies if the parser reached the end of the file
//  @return bool
	bool eof() const;

//  @brief Parser::close() - closes the file
//  @return void
	void close();

//  @brief Parser::next_line() - if it is not the end of the file, it starts parsing the first position of the next possible line
//  @return void
	void next_line();


//  @brief Parser::read_current(string & result) - reads current token ignoring spaces and line breaks  
//  @param result is a reference to an empty string variable that will receive the value of the valid read token 
//  @return void
	void read_current(string & result);

//  @brief Parser::next() - similar to read_current method logic, but it just moves the position to start reading the next token 
//  @see Parser::read_current(string & result)
//  @return void
	void next();

//  @brief Parser::check_left_parenthesis() - checks if the current token is a left parenthesis 
//  @return bool
	bool check_left_parenthesis();

//  @brief Parser::check_right_parenthesis() - checks if the current token is a right parenthesis 
//  @return bool
	bool check_right_parenthesis();

//  @brief Parser::check_label() - checks if the current token is a label (it is all uppercase or all lowercase)
//  @return bool
	bool check_label();

//  @brief Parser::check_number() - checks if the current token is a number 
//  @return bool
	bool check_number();

//  @brief Parser::check_symbol() - checks if the current token is a symbol (label or number)
//  @return bool
	bool check_symbol();

//  @brief Parser::parse_horn_clause() - checks the Horn Clause syntax. If it is valid, it returns the Horn Clause, if not it returns 0. 
//  @return HornClause *
	HornClause * parse_horn_clause();

//  @brief Parser::parse_head() - checks the Head syntax. If it is valid, it returns the Head, if not it returns 0. 
//  @return Head *
	Head * parse_head();

//  @brief Parser::parse_predicate() - checks the Predicate syntax. If it is valid, it returns the Predicate, if not it returns 0. 
//  @return Predicate *
	Predicate * parse_predicate();

//  @brief Parser::parse_name() - checks the Name syntax. If it is valid, it returns the Name, if not it returns 0. 
//  @return Name *
	Name * parse_name();

//  @brief Parser::parse_symbols() - checks the Symbol syntax list. If it is valid, it returns the list if Symbols, if not it returns 0. 
//  @return vector<Symbol> *
	vector<Symbol> * parse_symbols();

//  @brief Parser::parse_body() - checks the Body syntax. If it is valid, it returns the Body, if not it returns 0. 
//  @return Body *
	Body * parse_body();

private:
	string _file_name;
	string _current_line;
	ifstream _file;
	unsigned int _position;
};



#endif
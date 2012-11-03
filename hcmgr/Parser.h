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
	Parser();
	void open(const string & filename);
	bool is_open() const;
	bool eof() const;
	void close();

	void next_line();
	void read_current(string & result);
	void next();

	bool check_left_parenthesis();
	bool check_right_parenthesis();
	bool check_label();
	bool check_number();
	bool check_symbol();

	HornClause * parse_horn_clause();
	Head * parse_head();
	Predicate * parse_predicate();
	Name * parse_name();
	vector<Symbol> * parse_symbols();
	Body * parse_body();

private:
	string _file_name;
	string _current_line;
	ifstream _file;
	unsigned int _position;
};



#endif
/**
	Parser.cpp
	Class name: Parser 
	Written by: Amanda Silva and João Pimentel
	For:		CSE 425 Lab 2 - Question 4 - Part 1
	Purpose:    Implementation of the class Parser
*/


#include "stdafx.h"
#include "Parser.h"
#include "const.h"
#include "string_utils.h"

using namespace std; 

// @brief Initializes the variables with default values
Parser::Parser(): _file_name(""), _current_line(""), _file(), _position(0) {}

// @brief initializes the filename with a received parameter, opens it and initializes other variables with default values
// @param filename for the file with the tokens to be read
// @return void
void Parser::open(const string & filename) {
	_file_name = filename;
	_file.open(filename.c_str());
	_current_line =  "";
	_position = 0;
}

// @brief verifies if the file is open
// @return bool
bool Parser::is_open() const {
	return _file.is_open();
}

// @brief verifies if the parser reached the end of the file
// @return bool
bool Parser::eof() const {
	return _file.eof() && _position == _current_line.size();
}

// @brief closes the file
// @return void
void Parser::close() {
	_file.close();
}

// @brief if it is not the end of the file, it starts parsing the first position of the next possible line
// @return void
void Parser::next_line() {
	if (!_file.eof()) {
		getline(_file, _current_line);
		_position = 0;
	} else {
		 _position = _current_line.size();
	}
}

// @brief reads current token ignoring line breaks. It stops when it finds something that is not alphanumeric, such as parenthesis  
// @param result is a reference to an empty string variable that will receive the value of the valid read token 
// @return void
void Parser::read_current(string & result) {
	unsigned int i = _position;
	while (!eof() && result.size() == 0) {
		
		if (i == _current_line.size()) {
			next_line();
		}	
		for (i = _position; i < _current_line.size() && isspace(_current_line.at(i)); ++i) {} 
		if (i != _current_line.size()) {
			char c = _current_line.at(i);
			if (!isalnum(c)) {
				result += c;
			} else {
				for (; i < _current_line.size() && isalnum(_current_line.at(i)); ++i) { 
					result += _current_line.at(i);
				}
			}
		} 
	}
}

// @brief similar to read_current method logic, but it just moves the position to start reading the next token 
// @see Parser::read_current(string & result)
// @return void
void Parser::next() {
	string temp_result = "";
	while (!eof() && temp_result.size() == 0) {
		if (_position == _current_line.size()) {
			next_line();
		}
		for (;	_position < _current_line.size() && isspace(_current_line.at(_position)); ++_position) {} 
		if (_position != _current_line.size()) {
			char c = _current_line.at(_position);
			if (!isalnum(c)) {
				temp_result += c;
				++_position;
			} else {
				for (; _position < _current_line.size() && isalnum(_current_line.at(_position)); ++_position) { 
					temp_result += _current_line.at(_position);
				}
			}
		}
	}
	if (_position == _current_line.size()) {
		next_line();
	}
}
	
// @brief checks if the current token is a left parenthesis 
// @return bool
bool Parser::check_left_parenthesis() {
	string left_parenthesis;
	read_current(left_parenthesis);
	return (left_parenthesis == LEFTPAREN);
}

// @brief checks if the current token is a right parenthesis 
// @return bool
bool Parser::check_right_parenthesis() {
	string right_parenthesis;
	read_current(right_parenthesis);
	return (right_parenthesis == RIGHTPAREN); 
}

// @brief checks if the current token is a label (it is all uppercase or all lowercase)
// @return bool
bool Parser::check_label() {
	string label;
	read_current(label);
	if (label.size() == 0) {
		return false;
	}
	if (is_upper(label.at(0))) {
		return check_string(label, is_upper);
	} else if (is_lower(label.at(0))){
		return check_string(label, is_lower);
	}
	return false;
}

// @brief checks if the current token is a number 
// @return bool
bool Parser::check_number() {
	string number;
	read_current(number);
	return check_string(number, is_number);
}

// @brief checks if the current token is a symbol (label or number)
// @return bool
bool Parser::check_symbol() {
	return check_label() || check_number();
}

// @brief checks the Horn Clause syntax. If it is valid, it returns the Horn Clause, if not it returns 0. 
// @return HornClause * or NONE if there is a syntax error
HornClause * Parser::parse_horn_clause() {
	if (!check_left_parenthesis()) {
		return NONE;
	}
	next();

	Head * head = parse_head();
	if (head == NONE) {
		return NONE;
	}
	
	Body * body = parse_body();
	
	if (!check_right_parenthesis()) {
		delete head;
		delete body;
		return NONE;
	}
	next();

	HornClause * result = NONE;
	if (body == NONE) {
		result = new HornClause(*head);
	} else if (body->size() >= 1) {
		result = new HornClause(*head, *body);
	} else {
		delete body;
		result = NONE;
	}

	delete head;
	delete body;

	return result;	
}

// @brief checks the Head syntax. If it is valid, it returns the Head, if not it returns 0. 
// @return Head * or NONE if there is a syntax error
Head * Parser::parse_head() {
	Predicate * predicate = parse_predicate();
	if (predicate == NONE) {
		return NONE;
	}

	Head * result = new Head(*predicate);
	delete predicate;
	return result;
}

// @brief checks the Predicate syntax. If it is valid, it returns the Predicate, if not it returns 0. 
// @return Predicate * or NONE if there is a syntax error
Predicate * Parser::parse_predicate() {
	if (!check_left_parenthesis()) {
		return NONE;
	}
	next();

	Name * name = parse_name();
	if (name == NONE) {
		return NONE;
	}

	vector<Symbol> * symbols = parse_symbols();
	if (symbols == NONE) {
		delete name;
		return NONE;
	}

	if (!check_right_parenthesis()) {
		delete name;
		delete symbols;
		return NONE;
	}
	next();

	Predicate * result = new Predicate(*name, *symbols);
	delete name;
	delete symbols;

	return result;
}

// @brief checks the Name syntax. If it is valid, it returns the Name, if not it returns 0. 
// @return Name * or NONE if there is a syntax error
Name * Parser::parse_name() {
	if (!check_label()) {
		return NONE;
	}
	string name;
	read_current(name);
	next();
	return new Name(name);
}

// @brief checks the Symbol syntax list. If it is valid, it returns the list if Symbols, if not it returns 0. 
// @return vector<Symbol> * or NONE if there is a syntax error
vector<Symbol> * Parser::parse_symbols() {
	vector<Symbol> * result = new vector<Symbol>();

	while (!eof() && !check_right_parenthesis()) {
		if (!check_symbol()) {
			delete result;
			return NONE;
		}
		string symbol;
		read_current(symbol);
		result->push_back(Symbol(symbol));
		next();
	}
	if (eof()) {
		delete result;
		return NONE;
	}
	return result;
}


// @brief checks the Body syntax. If it is valid, it returns the Body, if not it returns 0. 
// @return Body * or NONE if there is a syntax error
Body * Parser::parse_body() {
	if (!check_left_parenthesis()) {
		return NONE;
	}
	next();

	vector<Predicate> predicates;

	while (!eof() && !check_right_parenthesis()) {
		Predicate * predicate = parse_predicate();
		if (predicate == NONE) {			
			Body * body = new Body(vector<Predicate>());
			return body;
		}
		predicates.push_back(*predicate);
		delete predicate;
	}
	
	if (eof() || !check_right_parenthesis()) {
		Body * body = new Body(vector<Predicate>());
		return body;
	}
	next();

	Body * result = new Body(predicates);
	return result;
}



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
#include "UnboundSymbol.h"
#include "TermSymbol.h"
#include "FunctionSymbol.h"

using namespace std; 

// @brief Initializes the variables with default values
Parser::Parser(): _file_name(""), _current_line(""), _file(), _position(0) {}

// @brief Initializes the variables with default values and a string to be parsed
// @param string with the content to be parsed
Parser::Parser(const string & str): _file_name("temp"), _current_line(""), _file(stringstream(str)), _position(0) {}

// @brief initializes the filename with a received parameter, opens it and initializes other variables with default values
// @param filename for the file with the tokens to be read
// @return void
bool Parser::open(const string & filename) {
	_file_name = filename;
	_current_line =  "";
	_position = 0;
	ifstream file(filename.c_str());
    if (file) {
        file.seekg(0, ios::end);
        streampos length = file.tellg();
        file.seekg(0, ios::beg);

        vector<char> buffer((unsigned int)length);
        file.read(&buffer[0],length);
        _file.rdbuf()->pubsetbuf(&buffer[0],length);
		return true;
    } else {
		return false;
	}
	//_file.open(filename.c_str());
	
}

// @brief initialize the parser to be able to parse
// @param stream with the content to be parsed
// @return bool
void Parser::start(const string & str) {
	_file_name = "temp";
	_current_line =  "";
	_position = 0;
	_file = stringstream(str);
}

// @brief verifies if the parser reached the end of the file
// @return bool
bool Parser::eof() const {
	return _file.eof() && _position == _current_line.size();
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

// @brief checks if the current token is a left bracket 
// @return bool
bool Parser::check_left_bracket() {
	string left_bracket;
	read_current(left_bracket);
	return (left_bracket == LEFTBRACKET);
}

// @brief checks if the current token is a right bracket 
// @return bool
bool Parser::check_right_bracket() {
	string right_bracket;
	read_current(right_bracket);
	return (right_bracket == RIGHTBRACKET); 
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

// @brief checks if the current token is a unbound 
// @return bool
bool Parser::check_unbound() {
	string label;
	read_current(label);
	if (label.size() != 1) {
		return false;
	}
	return is_upper(label.at(0)) == 1;
}

// @brief checks if the current token is a bound 
// @return bool
bool Parser::check_bound() {
	string label;
	read_current(label);
	if (label.size() != 1) {
		return false;
	}
	return is_lower(label.at(0)) == 1;
}

// @brief checks if the current token is a operator
// @return bool
bool Parser::check_operator() {
	string op;
	read_current(op);
	if (op.size() == 0) {
		return false;
	}
	return (op == "+" || op == "-" || op == "*" || op == "/" || op == "%");
}


// @brief checks if the current token is a term (number or bound) 
// @return bool
bool Parser::check_term() {
	return check_bound() || check_number();
}

// @brief checks the Horn Clause syntax. If it is valid, it returns the Horn Clause, if not it returns 0. 
// @return HornClause * or NONE if there is a syntax error
shared_ptr<HornClause> Parser::parse_horn_clause() {
	if (!check_left_parenthesis()) {
		return shared_ptr<HornClause>();
	}
	next();

	shared_ptr<Head> head = parse_head();
	if (!head) {
		return shared_ptr<HornClause>();
	}
	
	shared_ptr<Body> body = parse_body();
	
	if (!check_right_parenthesis()) {
		return shared_ptr<HornClause>();
	}
	next();

	shared_ptr<HornClause> result = shared_ptr<HornClause>();
	if (!body) {
		result = shared_ptr<HornClause>(new HornClause(*head));
	} else if (body->size() >= 1) {
		result = shared_ptr<HornClause>(new HornClause(*head, *body));
	} else {
		result = shared_ptr<HornClause>();
	}
	
	return result;	
}

// @brief checks the Head syntax. If it is valid, it returns the Head, if not it returns 0. 
// @return shared_ptr<Head> or NONE if there is a syntax error
shared_ptr<Head> Parser::parse_head() {
	shared_ptr<Predicate> predicate = parse_predicate();
	if (!predicate) {
		return shared_ptr<Head>();
	}
	shared_ptr<Head> result = shared_ptr<Head>(new Head(*predicate));
	return result;
}

// @brief checks the Predicate syntax. If it is valid, it returns the Predicate, if not it returns 0. 
// @return shared_ptr<Predicate> or NONE if there is a syntax error
shared_ptr<Predicate> Parser::parse_predicate() {
	if (!check_left_parenthesis()) {
		return shared_ptr<Predicate>();
	}
	next();

	shared_ptr<Name> name = parse_name();
	if (!name) {
		return shared_ptr<Predicate>();
	}

	shared_ptr<vector<shared_ptr<Symbol>>> symbols = parse_symbols();
	if (!symbols) {
		return shared_ptr<Predicate>();
	}

	if (!check_right_parenthesis()) {
		return shared_ptr<Predicate>();
	}
	next();

	shared_ptr<Predicate> result = shared_ptr<Predicate>(new Predicate(*name, *symbols));

	return result;
}

// @brief checks the Name syntax. If it is valid, it returns the Name, if not it returns 0. 
// @return shared_ptr<Name> or NONE if there is a syntax error
shared_ptr<Name> Parser::parse_name() {
	if (!check_label()) {
		return shared_ptr<Name>();
	}
	string name;
	read_current(name);
	next();
	return shared_ptr<Name>(new Name(name));
}

// @brief checks the Symbol syntax list. If it is valid, it returns the list if Symbols, if not it returns 0. 
// @return vector<Symbol> * or NONE if there is a syntax error
shared_ptr<vector<shared_ptr<Symbol>>> Parser::parse_symbols() {
	shared_ptr<vector<shared_ptr<Symbol>>> result = shared_ptr<vector<shared_ptr<Symbol>>>(new vector<shared_ptr<Symbol>>());

	while (!eof() && !check_right_parenthesis()) {
		
		shared_ptr<Symbol> symbol = parse_symbol();
		if (!symbol) {
			return shared_ptr<vector<shared_ptr<Symbol>>>();
		}
		
		result->push_back(symbol);
	}
	if (eof()) {
		return shared_ptr<vector<shared_ptr<Symbol>>>();
	}
	return result;
}

// @brief checks the Symbol syntax. If it is valid, it returns the Symbol, if not it returns 0. 
// @return shared_ptr<Symbol> 
shared_ptr<Symbol> Parser::parse_symbol() {
	if (check_unbound()) {
		string symbol;
		read_current(symbol);
		next();
		return shared_ptr<Symbol>(new UnboundSymbol(symbol));
	}
	if (check_term()) {
		string symbol;
		read_current(symbol);
		next();
		return shared_ptr<Symbol>(new TermSymbol(symbol));
	}
	return parse_function();
}

// @brief checks the Function syntax. If it is valid, it returns the Symbol, if not it returns 0. 
// @return shared_ptr<Symbol> 
shared_ptr<Symbol> Parser::parse_function() {
	if (!check_left_bracket()) {
		return shared_ptr<Symbol>();
	}
	next();

	if (!check_operator()) {
		return shared_ptr<Symbol>();
	}
	string text_operator;
	read_current(text_operator);
	next();

	if (!check_term()) {
		return shared_ptr<Symbol>();
	}
	string term1;
	read_current(term1);
	next();

	if (!check_term()) {
		return shared_ptr<Symbol>();
	}
	string term2;
	read_current(term2);
	next();

	if (!check_right_bracket()) {
		return shared_ptr<Symbol>();
	}
	next();

	return shared_ptr<Symbol>(new FunctionSymbol(text_operator, term1, term2));


}

// @brief checks the Body syntax. If it is valid, it returns the Body, if not it returns 0. 
// @return shared_ptr<Body> or NONE if there is a syntax error
shared_ptr<Body> Parser::parse_body() {
	if (!check_left_parenthesis()) {
		return shared_ptr<Body>();
	}
	next();

	vector<Predicate> predicates;

	while (!eof() && !check_right_parenthesis()) {
		shared_ptr<Predicate> predicate = parse_predicate();
		if (!predicate) {			
			shared_ptr<Body> body = shared_ptr<Body>(new Body(vector<Predicate>()));
			return body;
		}
		predicates.push_back(*predicate);
	}
	
	if (eof() || !check_right_parenthesis()) {
		shared_ptr<Body> body = shared_ptr<Body>(new Body(vector<Predicate>()));
		return body;
	}
	next();

	shared_ptr<Body> result = shared_ptr<Body>(new Body(predicates));
	return result;
}



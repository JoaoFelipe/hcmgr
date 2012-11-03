#include "stdafx.h"
#include "Parser.h"
#include "const.h"
#include "string_utils.h"

using namespace std; 

Parser::Parser(): _file_name(""), _current_line(""), _file(), _position(0) {}

void Parser::open(const string & filename) {
	_file_name = filename;
	_file.open(filename.c_str());
	_current_line =  "";
	_position = 0;
}

bool Parser::is_open() const {
	return _file.is_open();
}

bool Parser::eof() const {
	return _file.eof() && _position == _current_line.size();
}

void Parser::close() {
	_file.close();
}

void Parser::next_line() {
	if (!_file.eof()) {
		getline(_file, _current_line);
		_position = 0;
	} else {
		 _position = _current_line.size();
	}
}

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
	

bool Parser::check_left_parenthesis() {
	string left_parenthesis;
	read_current(left_parenthesis);
	return (left_parenthesis == LEFTPAREN);
}

bool Parser::check_right_parenthesis() {
	string right_parenthesis;
	read_current(right_parenthesis);
	return (right_parenthesis == RIGHTPAREN); 
}

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

bool Parser::check_number() {
	string number;
	read_current(number);
	return check_string(number, is_number);
}

bool Parser::check_symbol() {
	return check_label() || check_number();
}

HornClause * Parser::parse_horn_clause() {
	if (!check_left_parenthesis()) {
		return 0;
	}
	next();

	Head * head = parse_head();
	if (head == 0) {
		return 0;
	}
	
	Body * body = parse_body();
	
	if (!check_right_parenthesis()) {
		delete head;
		delete body;
		return 0;
	}
	next();

	HornClause * result = 0;
	if (body == 0) {
		result = new HornClause(*head);
	} else if (body->size() >= 1) {
		result = new HornClause(*head, *body);
	} else {
		delete body;
		result = 0;
	}

	delete head;
	delete body;

	return result;	
}

Head * Parser::parse_head() {
	Predicate * predicate = parse_predicate();
	if (predicate == 0) {
		return 0;
	}

	Head * result = new Head(*predicate);
	delete predicate;
	return result;
}

Predicate * Parser::parse_predicate() {
	if (!check_left_parenthesis()) {
		return 0;
	}
	next();

	Name * name = parse_name();
	if (name == 0) {
		return 0;
	}

	vector<Symbol> * symbols = parse_symbols();
	if (symbols == 0) {
		delete name;
		return 0;
	}

	if (!check_right_parenthesis()) {
		delete name;
		delete symbols;
		return 0;
	}
	next();

	Predicate * result = new Predicate(*name, *symbols);
	delete name;
	delete symbols;

	return result;
}

Name * Parser::parse_name() {
	if (!check_label()) {
		return 0;
	}
	string name;
	read_current(name);
	next();
	return new Name(name);
}

vector<Symbol> * Parser::parse_symbols() {
	vector<Symbol> * result = new vector<Symbol>();

	while (!eof() && !check_right_parenthesis()) {
		if (!check_symbol()) {
			delete result;
			return 0;
		}
		string symbol;
		read_current(symbol);
		result->push_back(Symbol(symbol));
		next();
	}
	if (eof()) {
		delete result;
		return 0;
	}
	return result;
}

Body * Parser::parse_body() {
	if (!check_left_parenthesis()) {
		return 0;
	}
	next();

	vector<Predicate> predicates;

	while (!eof() && !check_right_parenthesis()) {
		Predicate * predicate = parse_predicate();
		if (predicate == 0) {			
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



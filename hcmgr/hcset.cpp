/**
	hcset.cpp
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Definition of the function to set the variable value

*/


#include "stdafx.h"
#include "const.h"
#include "hcprocess.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "BoundEntry.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cctype>
#include <memory>

using namespace std;


// @brief Parse a bound and a number from the text and set the value in the SymbolTable
// @param text is the bound and value, output is ostream
// @return int indicating success (0-SUCCESS)
int set_variable(string& text, ostream & output) {
	shared_ptr<SymbolTable> table = SymbolTable::instance();
	Parser parser(text);
	shared_ptr<BoundEntry> bound = parser.parse_bound_entry();
	if (!bound) {
		output << "Invalid Bound Syntax" << endl;
		return 1;
	}
	shared_ptr<int> number = parser.parse_number();
	if (!number) {
		output << "Invalid Number Syntax" << endl;
		return 1;
	}
	shared_ptr<BoundEntry> entry = dynamic_pointer_cast<BoundEntry>(table->find(bound->type() + ":" + bound->text()));
	if (!entry){
		entry = bound;
		entry->value(*number);
		table->add(entry);
	}
	entry->value(*number);
	return 0;
}
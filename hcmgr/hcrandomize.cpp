/**
  hcrandomize.cpp
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the method to gerenerate a random value up to a max value.
*/

#include "stdafx.h"
#include "hcrandomize.h"
#include "Parser.h"
#include <limits.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;

// @brief Parse a bound and a optional number from the text and set the value in the SymbolTable to a random value between 0 and the number
// @param text is the bound and the optional value, output is ostream
// @return int indicating success (0-SUCCESS)
int randomize_variable(string& text, ostream & output) {
	shared_ptr<SymbolTable> table = SymbolTable::instance();
	Parser parser(text);
	shared_ptr<BoundEntry> bound = parser.parse_bound_entry();
	if (!bound) {
		output << "Invalid Bound Syntax" << endl;
		return 1;
	}
	shared_ptr<int> number = parser.parse_number();
	int value = -1;
	if (!number) {
		value = getRandomValue(INT_MAX);
	} else {
		value = getRandomValue(*number);
	}

	shared_ptr<BoundEntry> entry = dynamic_pointer_cast<BoundEntry>(table->find(bound->type() + ":" + bound->text()));
	if (!entry){
		entry = bound;
		entry->value(value);
		table->add(entry);
	}
	entry->value(value);
	return 0;
}

// @brief Returns a random value from 0 to a given unsinged int max range (or INT_MAX)
// @param unsigned int max
// @return int - random value
int getRandomValue(unsigned int max){
	
	return ((rand() % max) + 1); //Define range and get result random number
}


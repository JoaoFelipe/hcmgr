/**
	hcprocess.cpp
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Implementation of the method to process the Horn Clauses line by line from the file

*/


#include "stdafx.h"
#include "const.h"
#include "hcprocess.h"
#include "Parser.h"
#include "SymbolTable.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cctype>
#include "Name.h"


using namespace std;

// @brief Manipulates the file to parse the Horn Clauses line by line
// @param filename
// @return int - 0 = SUCCESS
int process(string & filename, vector<shared_ptr<HornClause>> & horn_clauses, ostream & output) {
	Parser parser;	
	if (parser.open(filename)) {
		int i = 0;
		while (!parser.eof()) {
			// Read each horn clause from file
			shared_ptr<HornClause> hc = parser.parse_horn_clause();
			// If invalid syntax, skip line
			if (!hc) {
				parser.next_line();
			} else {
				// Fill the symbol table by the Horn Clause
				++i;
				hc->fill_symbol_table();
				horn_clauses.push_back(hc);
			}
		}
		// If not found some horn clauses
		if (i == 0) { 
			return INVALID_FILE_ERROR;
		}
	} else{
		return OPEN_FILE_ERROR;
	}
	return SUCCESS;
}


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

using namespace std;

//  @brief process(string& filename) - Manipulates the file to parse the Horn Clauses line by line
//  @param filename
//  @return int - 0 = SUCCESS
int process(string & filename) {
	SymbolTable table;
	Parser parser;
	parser.open(filename);
	if (parser.is_open()) {
		int i = 0;
		while (!parser.eof()) {
			// Read each horn clause from file
			HornClause * hc = parser.parse_horn_clause();
			// If invalid syntax, skip line
			if (hc == NONE) {
				parser.next_line();
			} else {
				// Fill the symbol table by the Horn Clause
				++i;
				hc->fill_symbol_table(table);
			}

			delete hc;
			
		}
		parser.close();
		// If found some horn clauses
		if (i != 0) { 
			table.print_predicates();
			cout << endl;
			table.unifications();
		} else {
			return INVALID_FILE_ERROR;
		}

	} else{
		return OPEN_FILE_ERROR;
	}
	return SUCCESS;
}


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

void process(string& filename){
	SymbolTable table;
	Parser parser;
	parser.open(filename);
	if (parser.is_open()) {
		int i = 0;
		while (!parser.eof()) {
			HornClause * hc = parser.parse_horn_clause();
			if (hc == 0) {
				parser.next_line();
			} else {
				hc->fill_symbol_table(table);
			}

			delete hc;
			
		}
		parser.close();
		table.print_predicates();
		cout << endl;
		table.unifications();

	} else{
		throw OPEN_FILE_ERROR;
	}

}


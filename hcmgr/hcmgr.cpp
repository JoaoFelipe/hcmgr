/**
  hcmgt.cpp 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Entry point for the application (main), also checks if the arguments are correct
*/

#include "stdafx.h"
#include "const.h"
#include "hcprocess.h"
#include "hcset.h"
#include "hcevaluate.h"
#include "hcrandomize.h"
#include "HornClause.h"
#include "SymbolTable.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <memory>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()


using namespace std;

// @brief prints out a help message, passing the parameters received by main
// @param argc - number of arguments
// @param argv - array of arguments
void help_message(int argc, char * argv[]) {
	cout << "Usage information:" << endl;
	cout << argv[PROGRAM_NAME] << " [process <filename>]" << endl;
	cout << "    <filename> is the file with input horn clauses" << endl;
}

// @brief prints out a help message that tells how to use the interpreter functions
void help_message_inside() {
	cout << "Use one of the following commands:"<< endl;
	cout << "  process <filename> -- loads a file of Horn clauses into the program" << endl;
	cout << "  evaluate <predicate> -- resolves the predicate given in the command" << endl;
	cout << "  randomize <variable> [<max>] -- generates a randomized value for a bound variable" << endl;
	cout << "  set <variable> <value> -- sets a bound variable to the given value" << endl;
	cout << "  print -- prints out the contents of the symbol table including" << endl;
	cout << "  db -- prints out the processed horn clauses from the deductive database" << endl;
	cout << "  help -- shows this help message" << endl;
}

// @brief verifies if the program arguments are valid
// @param argc - number of arguments
// @param argv - array of arguments
// @param filename - empty string that will be assigned to the second argument.
// @return int indicating SUCCESS or ARGUMENT_ERROR or ZERO_PARAM
int check_arguments(int argc, char * argv[], string & filename) {	
	if (argc == ZERO_PARAM) {
		return ZERO_PARAM;
	}
	if(argc != TWO_PARAM || string(argv[OPERATION]) != "process"){
		return ARGUMENT_ERROR;
	}
	filename += argv[FILE_NAME];
	return SUCCESS;
}

// @brief entry point for the application
// @param argc - number of arguments
// @param argv - array of arguments
// @return int indicating SUCCESS
int main(int argc, char * argv[])
{
	srand(unsigned(time(0)));   // Initialize random number generator.
	string filename;

	int check = check_arguments(argc, argv, filename);
	if (check == ARGUMENT_ERROR) {
		cout << "Invalid Argument format" << endl;
		help_message(argc, argv);
		return ARGUMENT_ERROR;
	}

	shared_ptr<SymbolTable> symbol_table = SymbolTable::instance();
	vector<shared_ptr<HornClause>> deductive_database;

	cout << "HCMGR Interpreter" << endl;
	
	if (check == SUCCESS) {
		symbol_table->erase();
		deductive_database = vector<shared_ptr<HornClause>>();
		cout << "Processing file " << filename << endl;				
		check = process(filename, deductive_database, cout);
		if (check == OPEN_FILE_ERROR) {
			cout << "Unable to open file "<< filename << endl;
		} else if (check == INVALID_FILE_ERROR) {
			cout << "No valid horn clauses were found in the file." << endl;
		}
	}
	cout << "Type 'help'" << endl;
	bool executing = true;
	string line;
	while (executing) {
		cout << "> ";
		getline(cin, line);
		
		istringstream is(line);
		string upper;
		is >> upper;

		transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
		if (upper == "EXIT") {
			executing = false;
			continue;
		}
		string param; getline(is, param);
		if (param.size() >= 2 && param.at(0) == ' ') {
			param = param.substr(1);
		}
		
		if (upper == "PROCESS") {
			cout << "Erasing deductive database" << endl;		
			symbol_table->erase();
			deductive_database = vector<shared_ptr<HornClause>>();
			cout << "Processing file " << param << endl;				
			check = process(param, deductive_database, cout);
			if (check == OPEN_FILE_ERROR) {
				cout << "Unable to open file "<< param << endl;
			} else if (check == INVALID_FILE_ERROR) {
				cout << "No valid horn clauses were found in the file." << endl;
			}
		}
		
		if (upper == "EVALUATE") {
			SymbolTable::instance()->backup();
			evaluate(param, deductive_database, cout);
			SymbolTable::instance()->restore();
		}

		if (upper == "RANDOMIZE") {
			randomize_variable(param, cout);
		}

		if (upper == "SET") {
			set_variable(param, cout);
		}

		if (upper == "PRINT") {
			symbol_table->print(cout);
		}

		if (upper == "DB") {
			for (auto hc : deductive_database) {
				hc->print(cout);
				cout << endl;
			}
		}

		if (upper == "HELP") {
			help_message_inside();
		}

		
	}


	

	return SUCCESS;
}


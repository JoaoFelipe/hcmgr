/**
  const.h 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Entry point for the application (main) and checking if the arguments are correct
*/

#include "stdafx.h"
#include "const.h"
#include "hcprocess.h"
#include <string>
#include <iostream>

using namespace std;

//  @brief help_message(int argc, char * argv[]) - prints out a help message, passing the parameters received by main
//  @param argc - number of arguments
//  @param argv - array of arguments
void help_message(int argc, char * argv[]) {
	cout << "Usage information:" << endl;
	cout << argv[PROGRAM_NAME] << " process <filename>" << endl;
	cout << "    <filename> is the file with input horn clauses" << endl;
}

//  @brief check_arguments(int argc, char * argv[], string& filename) - verifies if the program arguments are valid
//  @param argc - number of arguments
//  @param argv - array of arguments
//  @param filename - empty string that will be assigned to the second argument.
//  @return int indicating SUCCESS or ARGUMENT_ERROR
int check_arguments(int argc, char * argv[], string & filename) {	
	if(argc != TWO_PARAM || string(argv[OPERATION]) != "process"){
		return ARGUMENT_ERROR;
	}
	filename += argv[FILE_NAME];
	return SUCCESS;
}

//  @brief int main(int argc, char * argv[]) - entry point for the application
//  @param argc - number of arguments
//  @param argv - array of arguments
//  @return int indicating SUCCESS
int main(int argc, char * argv[])
{
	string filename;

	int check = check_arguments(argc, argv, filename);
	if (check == ARGUMENT_ERROR) {
		cout << "Invalid Argument format" << endl;
		help_message(argc, argv);
		return ARGUMENT_ERROR;
	}

	check = process(filename);
	if (check == OPEN_FILE_ERROR) {
		cout << "Unable to open file "<< filename << endl;
		return OPEN_FILE_ERROR;
	} else if (check == INVALID_FILE_ERROR) {
		cout << "No valid horn clauses were found in the file." << endl;
		return INVALID_FILE_ERROR;
	}

	return SUCCESS;
}


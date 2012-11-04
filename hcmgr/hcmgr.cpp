// hcmgr.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "const.h"
#include "hcprocess.h"
#include <string>
#include <iostream>
using namespace std;


void help_message(int argc, char * argv[]) {
	cout << "Usage information:" << endl;
	cout << argv[0] << " process <filename>" << endl;
	cout << "    <filename> is the file with input horn clauses" << endl;
}

// Function verifies if the paramters are valid
int check_arguments(int argc, char * argv[], string& filename){	
	if(argc != 3 || string(argv[1]) != "process"){
		return ARGUMENT_ERROR;
	}
	filename += argv[2];
	return SUCCESS;
}


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


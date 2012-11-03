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
void check_arguments(int argc, char * argv[], string& filename){	
	if(argc != 3 || string(argv[1]) != "process"){
		throw ARGUMENT_ERROR;
	}
	filename += argv[2];
}


int main(int argc, char * argv[])
{
	string filename;
	try{
		check_arguments(argc, argv, filename);
		process(filename);




	} catch (int exception){
		switch (exception)
		{
		case ARGUMENT_ERROR:
			cout << "Invalid Argument format" << endl;
			help_message(argc, argv);
			break;
		case OPEN_FILE_ERROR:
			cout << "Unable to open file "<< filename << endl;
			break;


		default:
			break;
		}
		
	}


	return 0;
}


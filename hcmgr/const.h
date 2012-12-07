/**
  const.h 
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    File to declare and assign the global system constants
*/

#ifndef CONST_H
#define CONST_H 

#include "stdafx.h"
#include <string>

using namespace std; 

// Constant of success
const int SUCCESS = 0;

// Constant of error when the command-line parameters are bad-formed
const int ARGUMENT_ERROR = 1;

// Constant of error when the file cannot be open correctly
const int OPEN_FILE_ERROR = 2;

// Constant of error when the file doesn't have any valid horn clauses
const int INVALID_FILE_ERROR = 3;

// Constant of error when there is a try to divide by 0
const int DIVIDE_BY_ZERO_ERROR = 4;

// Constant of the char to represent the left parenthesis syntax token
const char C_LEFTPAREN = '(';

// Constant of the char to represent the right parenthesis syntax token
const char C_RIGHTPAREN = ')';

// Constant of the string to represent the left parenthesis syntax token
const string LEFTPAREN = string("(");

// Constant of the string to represent the right parenthesis syntax token
const string RIGHTPAREN = string(")");

// Constant of the char to represent the left bracket syntax token
const char C_LEFTBRACKET = '[';

// Constant of the char to represent the right bracket syntax token
const char C_RIGHTBRACKET = ']';

// Constant of the string to represent the left bracket syntax token
const string LEFTBRACKET= string("[");

// Constant of the string to represent the right bracket syntax token
const string RIGHTBRACKET = string("]");


// Constant for program name argument position
const int PROGRAM_NAME = 0;

// Constant for program receiving two arguments (not considering the program name)
const int TWO_PARAM = 3;

// Constant for program operation argument (process)
const int OPERATION = 1;

// Constant for filename argument
const int FILE_NAME = 2;

// Constant for Null Pointers
const int NONE = 0;

struct null_deleter
{
    void operator()(void const *) const
    {
    }
};

#endif
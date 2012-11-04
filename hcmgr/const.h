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

// Constant of the char to represent the left parenthesis syntax token
const char C_LEFTPAREN = '(';

// Constant of the char to represent the right parenthesis syntax token
const char C_RIGHTPAREN = ')';

// Constant of the string to represent the left parenthesis syntax token
const string LEFTPAREN = string("(");

// Constant of the string to represent the right parenthesis syntax token
const string RIGHTPAREN = string(")");


#endif
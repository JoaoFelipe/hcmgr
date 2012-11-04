/**
  string_utils.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Auxiliar Functions
*/

#ifndef STRING_UTILS_H
#define STRING_UTILS_H 

#include "stdafx.h"
#include <string>

using namespace std; 

// @brief Checks if the char is lowercase and alphanumeric
// @return int - returns zero if it is false
int is_lower (const char c);

// @brief Checks if the char is uppercase and alphanumeric
// @return int - returns zero if it is false
int is_upper (const char c);

// @brief Checks if the char is numeric
// @return int - returns zero if it is false
int is_number (const char c);

// @brief Applies a checker function to each character of the string
// @return bool 
bool check_string(const string & str, int (*checker)(const char));

#endif
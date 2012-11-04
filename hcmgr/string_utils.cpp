/**
	string_utils.cpp
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Auxiliar Functions
*/


#include "stdafx.h"
#include "string_utils.h"

// @brief Checks if the char is lowercase and alphanumeric
// @return int - returns zero if it is false
int is_lower (const char c) {
	return (islower(c) && isalpha(c));
}

// @brief Checks if the char is uppercase and alphanumeric
// @return int - returns zero if it is false
int is_upper (const char c) {
	return (isupper(c) && isalpha(c));
}

// @brief Checks if the char is numeric
// @return int - returns zero if it is false
int is_number (const char c) {
	return (isdigit(c));
}

// @brief Applies a checker function to each character of the string
// @return bool 
bool check_string(const string & str, int (*checker)(const char)) {
	if (str.size() == 0) {
		return false;
	}
	for (unsigned int i = 0; i < str.size(); ++i) {
		if (!checker(str.at(i))) {
			return false;
		}
	}
	return true;
}
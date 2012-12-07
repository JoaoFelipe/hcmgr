/**
  operations_utils.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Auxiliar Functions
*/

#ifndef OPERATIONS_UTILS_H
#define OPERATIONS_UTILS_H 

#include "stdafx.h"
#include "const.h"
#include <string>

using namespace std; 

// @brief Return the operation of the string
// @param number, number
// @return number
template <typename number>
number operation(string s, number a, number b) {
	if (s == "+") return sum(a, b);
	if (s == "-") return difference(a, b);
	if (s == "*") return product(a, b);
	if (s == "/") return quotient(a, b);
	if (s == "%") return rest(a, b);
	return a;
}

// @brief Calculate the sum
// @param number, number
// @return number
template <typename number>
number sum(number a, number b) {
	return a + b;
}

// @brief Calculate the difference
// @param number, number
// @return number
template <typename number>
number difference(number a, number b) {
	return a - b;
}

// @brief Calculate the product
// @param number, number
// @return number
template <typename number>
number product(number a, number b) {
	return a * b;
}

// @brief Calculate the quotient
// @param number, number
// @return number
template <typename number>
number quotient(number a, number b) {
	if (b == 0) {
		throw DIVIDE_BY_ZERO_ERROR;
	}
	return a / b;
}

// @brief Calculate the rest
// @param number, number
// @return number
template <typename number>
number rest(number a, number b) {
	if (b == 0) {
		throw DIVIDE_BY_ZERO_ERROR;
	}
	return a % b;
}

#endif
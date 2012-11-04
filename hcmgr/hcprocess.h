/**
  hcprocess.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 2
	Purpose:    Declaration of the method to process the Horn Clauses line by line in the file

*/

#ifndef HCPROCESS_H
#define HCPROCESS_H 

#include "stdafx.h"
#include <string>
using namespace std; 

// @brief Manipulates the file to parse the Horn Clauses line by line
// @param filename
// @return int - 0 = SUCCESS
int process(string& filename);

#endif
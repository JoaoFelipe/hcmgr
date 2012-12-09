/**
  hcrandomize.h
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Declaration of the method to gerenerate a random value up to a max value.

*/

#ifndef HCRANDOMIZE_H
#define HCRANDOMIZE_H 

#include "stdafx.h"
using namespace std; 

// @brief Returns a random value from 0 to a given unsinged int max range (or INT_MAX)
// @param unsigned int max
// @return int - random value
int getRandomValue(unsigned int max);

#endif
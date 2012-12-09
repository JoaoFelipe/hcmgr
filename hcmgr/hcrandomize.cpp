/**
  hcrandomize.cpp
	Written by: Amanda Silva and João Pimentel
	For:	    CSE 425 Lab 3
	Purpose:    Implementation of the method to gerenerate a random value up to a max value.
*/

#include <stdio.h>
#include "stdafx.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;

// @brief Returns a random value from 0 to a given unsinged int max range (or INT_MAX)
// @param unsigned int max
// @return int - random value
int getRandomValue(unsigned int max){
	srand(unsigned(time(0)));   // Initialize random number generator.
	return ((rand() % max) + 1); //Define range and get result random number
}


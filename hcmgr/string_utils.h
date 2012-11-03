#ifndef STRING_UTILS_H
#define STRING_UTILS_H 

#include "stdafx.h"
#include <string>

using namespace std; 

int is_lower (char c);
int is_upper (char c);
int is_number (char c);
bool check_string(string & str, int (*checker)(char));

#endif
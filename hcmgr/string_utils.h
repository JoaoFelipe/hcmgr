#ifndef STRING_UTILS_H
#define STRING_UTILS_H 

#include "stdafx.h"
#include <string>

using namespace std; 

int is_lower (const char c);
int is_upper (const char c);
int is_number (const char c);
bool check_string(const string & str, int (*checker)(const char));

#endif
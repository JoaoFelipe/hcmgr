#include "stdafx.h"
#include "string_utils.h"


int is_lower (const char c) {
	return (islower(c) && isalpha(c));
}

int is_upper (const char c) {
	return (isupper(c) && isalpha(c));
}

int is_number (const char c) {
	return (isdigit(c));
}

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
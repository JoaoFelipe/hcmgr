#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class Symbol
{
private:
    string _value;
public:
    Symbol(string& v);
	Symbol(const Symbol& s);
 
    void value(string& v);
    string& value();

	void print(ostream & = cout) const; 
};
 

#endif
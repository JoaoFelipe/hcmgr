#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>
#include "SymbolTableEntry.h"

using namespace std;

class Symbol
{
private:
    string _value;
public:
    Symbol(const string& v);
	Symbol(const Symbol& s);
 
    void value(const string& v);
    string value() const;

	string text() const;

	void print(ostream & = cout) const; 

	SymbolTableEntry * convertToSymbolTableEntry() const;
};
 

#endif
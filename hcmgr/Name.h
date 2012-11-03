#ifndef NAME_H
#define NAME_H

#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class Name
{
private:
    string _value;
public:
    Name(string& v);
	Name(const Name& n);
 
    void value(string& v);
    string& value();

	void print(ostream & = cout) const; 
};


#endif
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
    Name(const string& v);
	Name(const Name& n);
 
    void value(const string& v);
    string value() const;

	void print(ostream & = cout) const; 
};


#endif
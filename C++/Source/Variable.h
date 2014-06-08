//Created: September 18, 2008
//Revised: February 14, 2010

#pragma once

#include "Includes.h"

// a representation of a variable id / value pairing
class Variable {
public:
	// constructors and destructors
	Variable(const char * _id = "", const char * _value = "");
	Variable(const Variable & x);
	Variable & operator = (const Variable & x);
	~Variable(void);
	
	// set methods
	void id(const char * _id);
	void value(const char * _value);
	
	// get methods
	char * id() const;
	char * value() const;

	// parse variable from string
	bool parseFrom(const char * _data);
	
	// equality operators
	bool operator == (const Variable & x) const;
	bool operator != (const Variable & x) const;
	
	// print function
	void printOn(ostream & o) const;
	
private:
	// variable data
	char * _id;
	char * _value;
};

ostream & operator << (ostream & o, const Variable & x);

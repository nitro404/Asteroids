//Created: January 15, 2009
//Revised: February 27, 2010

#pragma once

#include "Includes.h"
#include "Variable.h"

//#pragma warning(disable: 4786)

// a collection of variable objects with custom functions for accessing/manipulating values easily
class Variables {
public:
	// constructors and destructors
	Variables();
	Variables(const Variables & x);
	Variables & operator = (const Variables & x);
	~Variables(void);
	
	// manipulation functions
	bool add(const Variable * x);
	bool remove(int _index);
	bool remove(const Variable * x);
	void clear();
	
	// get / checker methods
	int size() const;
	bool contains(const Variable * x) const;
	int indexOf(const Variable * x) const;
	Variable * elementAt(int _index) const;
	char * getValue(const char * _variableName);
	bool hasValue(const char * _variableName);

	// parse variables from a file
	bool parseFrom(const char * _fileName, bool _append = false);
	
	// equality operators
	bool operator == (const Variables & x) const;
	bool operator != (const Variables & x) const;
	
	// print function
	void printOn(ostream & o) const;
	
private:
	// collection of variables
	vector<Variable *> * _variables;
};

ostream & operator << (ostream & o, const Variables & x);

//Created: January 15, 2009
//Revised: February 27, 2010

#include "Variables.h"

Variables::Variables() {
	this->_variables = new vector<Variable *>;
}

Variables::Variables(const Variables & x) {
	this->_variables = new vector<Variable *>;
	for(int i=0;i<x.size();i++) {
		this->_variables->push_back( new Variable( *(x.elementAt(i)) ) );
	}
}

Variables & Variables::operator = (const Variables & x) {
	delete this->_variables;

	this->_variables = new vector<Variable *>;
	for(int i=0;i<x.size();i++) {
		this->_variables->push_back( new Variable( *(x.elementAt(i)) ) );
	}

	return *this;
}

Variables::~Variables(void) {
	for(unsigned int i=0;i<this->_variables->size();i++) {
		delete this->_variables->at(i);
	}
	delete this->_variables;
}


bool Variables::add(const Variable * x) {
	if(x == NULL || this->contains(x)) {
		return false;
	}
	
	this->_variables->push_back( new Variable(*(x)) );
	
	return true;
}

bool Variables::remove(int _index) {
	if(_index < 0 || _index >= size()) {
		return false;
	}
	
	this->_variables->erase(this->_variables->begin() + _index);
	
	return true;
}

bool Variables::remove(const Variable * x) {
	if(x == NULL) {
		return false;
	}

	int index = this->indexOf(x);
	if(index < 0) {
		return false;
	}

	this->_variables->erase(this->_variables->begin() + index);
	
	return true;
}

void Variables::clear() {
	this->_variables->clear();
}

int Variables::size() const {
	return this->_variables->size();
}

bool Variables::contains(const Variable * x) const {
	if(x == NULL) {
		return false;
	}

	for(int i=0;i<size();i++) {
		if( *(this->elementAt(i)) == *(x) ) {
			return true;
		}
	}
	return false;
}

int Variables::indexOf(const Variable * x) const {
	if(x == NULL) {
		return -1;
	}

	for(int i=0;i<size();i++) {
		if( *(this->elementAt(i)) == *(x) ) {
			return i;
		}
	}
	return -1;
}

Variable * Variables::elementAt(int _index) const {
	if(_index < 0 || _index >= size()) {
		return NULL;
	}

	return this->_variables->at(_index);
}

char * Variables::getValue(const char * _variableName) {
	if(_variableName == NULL || strlen(_variableName) == 0) {
		return NULL;
	}

	for(int i=0;i<size();i++) {
		if( _stricmp(this->elementAt(i)->id(), _variableName) == 0 ) {
			return this->elementAt(i)->value();
		}
	}
	return NULL;
}

bool Variables::hasValue(const char * _variableName) {
	if(_variableName == NULL || strlen(_variableName) == 0) {
		return false;
	}

	for(int i=0;i<size();i++) {
		if( _stricmp(this->elementAt(i)->id(), _variableName) == 0 ) {
			return true;
		}
	}
	return false;
}

bool Variables::parseFrom(const char * _fileName, bool _append) {
	if(_fileName == NULL || strlen(_fileName) == 0) {
		return false;
	}
	
	const int MAX_STRING_LENGTH = 1024;
	unsigned int i;
	char temp[MAX_STRING_LENGTH];
	Variable * v;
	bool duplicate;
	
	ifstream fpt(_fileName);
	if(fpt == NULL) {
		return false;
	}
	
	if(_append) {
		if(this->_variables == NULL) {
			this->_variables = new vector<Variable *>;
		}
	}
	else {
		if(this->_variables != NULL) {
			delete this->_variables;
		}
		this->_variables = new vector<Variable *>;
	}
	
	while(!fpt.eof()) {
		fpt.getline(temp, MAX_STRING_LENGTH);
		v = new Variable();
		if(v->parseFrom(temp)) {
			duplicate = false;
			for(i=0;i<this->_variables->size();i++) {
				if(*this->_variables->at(i) == *v) {
					duplicate = true;
					delete v;
					break;
				}
			}
			if(!duplicate) {
				this->_variables->push_back(v);
			}
		}
		else {
			delete v;
		}
	}
	
	return true;
}

bool Variables::operator == (const Variables & x) const {
	bool contains;
	for(unsigned int i=0;i<this->_variables->size();i++) {
		contains = false;
		for(int j=0;j<x.size();j++) {
			if( *(this->_variables->at(i)) == *(x._variables->at(j)) ) {
				contains = true;
				break;
			}
		}
		if(!contains) {
			return false;
		}
	}
	return true;
}

bool Variables::operator != (const Variables & x) const {
	return !operator == (x);
}

void Variables::printOn(ostream & o) const {
	for(unsigned int i=0;i<this->_variables->size();i++) {
		o << this->_variables->at(i)->id() << ": " << this->_variables->at(i)->value();
		
		if(i < this->_variables->size() - 1) {
			o << endl;
		}
	}
}

ostream & operator << (ostream & o, const Variables & x) {
	x.printOn(o);
	return o;
}

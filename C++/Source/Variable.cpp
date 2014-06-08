//Created: September 18, 2008
//Revised: February 14, 2010

#include "Variable.h"

Variable::Variable(const char * _id, const char * _value) {
	if(_id == NULL) {
		this->_id = new char[1];
		this->_id[0] = '\0';
	}
	else {
		this->_id = new char[strlen(_id) + 1];
		strcpy_s(this->_id,strlen(_id) + 1, _id);
	}
	
	if(_value == NULL) {
		this->_value = new char[1];
		this->_value[0] = '\0';
	}
	else {
		this->_value = new char[strlen(_value) + 1];
		strcpy_s(this->_value, strlen(_value) + 1, _value);
	}
}

Variable::Variable(const Variable & x) {
	this->_id = new char[strlen(x._id) + 1];
	strcpy_s(this->_id, strlen(x._id) + 1, x._id);
	
	this->_value = new char[strlen(x._value) + 1];
	strcpy_s(this->_value, strlen(x._value) + 1, x._value);
}

Variable & Variable::operator = (const Variable & x) {
	delete [] this->_id;
	delete [] this->_value;

	this->_id = new char[strlen(x._id) + 1];
	strcpy_s(this->_id, strlen(x._id) + 1, x._id);

	this->_value = new char[strlen(x._value) + 1];
	strcpy_s(this->_value, strlen(x._value) + 1, x._value);

	return *this;
}

Variable::~Variable(void) {
	delete [] this->_id;
	delete [] this->_value;
}

void Variable::id(const char * _id) {
	delete [] this->_id;
	
	if(_id == NULL) {
		this->_id = new char[1];
		this->_id[0] = '\0';
	}
	else {
		this->_id = new char[strlen(_id) + 1];
		strcpy_s(this->_id, strlen(_id) + 1, _id);
	}
}

void Variable::value(const char * _value) {
	delete [] this->_value;
	
	if(_value == NULL) {
		this->_value = new char[1];
		this->_value[0] = '\0';
	}
	else {
		this->_value = new char[strlen(_value) + 1];
		strcpy_s(this->_value, strlen(_value) + 1, _value);
	}
}

char * Variable::id() const  { return this->_id; }
char * Variable::value() const  { return this->_value; }

bool Variable::parseFrom(const char * _data) {
	if(_data == NULL || strlen(_data) < 1) {
		return false;
	}
	
	Variable * v = NULL;
	int separatorIndex = -1;
	char separatorChar = ':';
	int i, j;
	int start = -1;
	int end = -1;
	char * id = NULL;
	char * value = NULL;
	bool emptyID;
	
	for(i=0;i<(int)strlen(_data);i++) {
		if(_data[i] == separatorChar) {
			separatorIndex = i;
			break;
		}
	}
	
	if(separatorIndex == -1 || separatorIndex == 0) {
		return false;
	}
	emptyID = true;
	for(i=0;i<separatorIndex;i++) {
		if(_data[i] != ' ' && _data[i] != '\t') {
			emptyID = false;
			break;
		}
	}
	if(emptyID) {
		return false;
	}
	
	start = 0;
	end = separatorIndex - 1;
	for(i=start;i<=end;i++) {
		start = i;
		if(_data[i] != ' ' && _data[i] != '\t') {
			break;
		}
	}
	for(i=end;i>=start;i--) {
		end = i;
		if(_data[i] != ' ' && _data[i] != '\t') {
			break;
		}
	}
	if(start > end) {
		return false;
	}
	id = new char[end - start + 2];
	j = 0;
	for(i=start;i<=end;i++) {
		id[j++] = _data[i];
	}
	id[j] = '\0';
	if(strlen(id) == 0) {
		delete [] id;
		return false;
	}
	
	start = separatorIndex + 1;
	end = strlen(_data) - 1;
	for(i=start;i<=end;i++) {
		start = i;
		if(_data[i] != ' ' && _data[i] != '\t') {
			break;
		}
	}
	for(i=end;i>=start;i--) {
		end = i;
		if(_data[i] != ' ' && _data[i] != '\t') {
			break;
		}
	}
	if(start > end) {
		delete [] id;
		return false;
	}
	value = new char[end - start + 2];
	j = 0;
	for(i=start;i<=end;i++) {
		value[j++] = _data[i];
	}
	value[j] = '\0';

	if(this->_id != NULL) { delete [] this->_id; }
	if(this->_value != NULL) { delete [] this->_value; }
	
	this->_id = new char[strlen(id) + 1];
	strcpy_s(this->_id, strlen(id) + 1, id);
	
	this->_value = new char[strlen(value) + 1];
	strcpy_s(this->_value, strlen(value) + 1, value);
	
	delete [] id;
	delete [] value;

	return true;
}

bool Variable::operator == (const Variable & x) const {
	return _stricmp(this->_id, x._id) == 0;
}

bool Variable::operator != (const Variable & x) const {
	return !operator == (x);
}

void Variable::printOn(ostream & o) const {
	o << this->_id << ": " << this->_value;
}

ostream & operator << (ostream & o, const Variable & x) {
	x.printOn(o);
	return o;
}

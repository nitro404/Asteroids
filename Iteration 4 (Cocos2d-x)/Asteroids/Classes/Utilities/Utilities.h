#ifndef UTILITIES_H
#define UTILITIES_H

#define USE_STL 1

#include <cocos2d.h>
#include <cstdio>
#include <string>
#include <regex>
#include <iostream>

using namespace cocos2d;

namespace Utilities {
	extern const char newLine[];
	extern bool initialRandomize;
	extern const char * monthStrings[];

	void randomizeSeed();
	void randomSeed(unsigned int seed);
	int randomInteger(int min, int max, bool randomize = false);
	float randomFloat(float min, float max, bool randomize = false);
	int intLength(int n);
	unsigned int stringLength(const char * s);
	const char * toString(int value);
	const char * toString(double value);
#if USE_STL
	std::string trimString(const std::string & data);
#endif // USE_STL
#if USE_STL
	std::string substring(const std::string & data, int start, int end);
#endif // USE_STL
	int compareStrings(const char * s1, const char * s2, bool caseSensitive = true);
#if USE_STL
	int compareStrings(const std::string & s1, const std::string & s2, bool caseSensitive = true);
	int compareStrings(const char * s1, const std::string & s2, bool caseSensitive = true);
	int compareStrings(const std::string & s1, const char * s2, bool caseSensitive = true);
#endif // USE_STL
	int compareStringsIgnoreCase(const char * s1, const char * s2);
#if USE_STL
	int compareStringsIgnoreCase(const std::string & s1, const std::string & s2);
	int compareStringsIgnoreCase(const char * s1, const std::string & s2);
	int compareStringsIgnoreCase(const std::string & s1, const char * s2);
#endif // USE_STL
	int firstIndexOf(const char * data, char c);
	int lastIndexOf(const char * data, char c);
	std::string getVariableID(const char * data);
	std::string getVariableID(const std::string & data);
	std::string getVariableValue(const char * data);
	std::string getVariableValue(const std::string & data);
	bool parseBoolean(const char * data, bool * valid = NULL);
#if USE_STL
	bool parseBoolean(const std::string & data, bool * valid = NULL);
#endif // USE_STL
	int parseInteger(const char * data, bool * valid = NULL);
#if USE_STL
	int parseInteger(const std::string & data, bool * valid = NULL);
#endif // USE_STL
	float parseFloat(const char * data, bool * valid = NULL);
#if USE_STL
	float parseFloat(const std::string & data, bool * valid = NULL);
#endif // USE_STL
	std::string generateFullPath(const char * path, const char * fileName);
	std::string generateFullPath(const std::string & path, const std::string & fileName);
}

#endif // UTILITIES_H

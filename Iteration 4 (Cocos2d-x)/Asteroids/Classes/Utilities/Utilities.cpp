#include "Utilities.h"

#if _WIN32
const char Utilities::newLine[] = "\r\n";
#elif __APPLE__
const char Utilities::newLine[] = "\r";
#else
const char Utilities::newLine[] = "\n";
#endif // _WIN32

bool Utilities::initialRandomize = true;

void Utilities::randomizeSeed() {
	srand(time(NULL));
}

void Utilities::randomSeed(unsigned int seed) {
	srand(seed);
}

int Utilities::randomInteger(int min, int max, bool randomize) {
	if(max <= min) { return min; }

	if(randomize || initialRandomize) {
		randomizeSeed();
		initialRandomize = false;
	}

	return (rand() % (max - min + 1)) + min;
}

float Utilities::randomFloat(float min, float max, bool randomize) {
	if(max <= min) { return min; }

	if(randomize || initialRandomize) {
		randomizeSeed();
		initialRandomize = false;
	}

	return ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * max) + min;
}

int Utilities::intLength(int n) {
	return n < 100000 ? n < 100 ? n < 10 ? 1 : 2 : n < 1000 ? 3 : n < 10000 ? 4 : 5 : n < 10000000 ? n < 1000000 ? 6 : 7 : n < 100000000 ? 8 : n < 1000000000 ? 9 : 10;
}

unsigned int Utilities::stringLength(const char * s) {
	return s == NULL ? 0 : strlen(s);
}

const char * Utilities::toString(int value) {
	static char buffer[32];
#if _WIN32
	sprintf_s(buffer, 32, "%d", value);
#else
	sprintf(buffer, "%d", value);
#endif // _WIN32

	return buffer;
}

const char * Utilities::toString(double value) {
	static char buffer[32];
#if _WIN32
	sprintf_s(buffer, 32, "%f", value);
#else
	sprintf(buffer, "%f", value);
#endif // _WIN32

	return buffer;
}

#if USE_STL
std::string Utilities::trimString(const std::string & data) {
	if(data.empty()) { return std::string(); }
	if(data.length() == 1 && (data[0] == ' ' || data[0] == '\t' || data[0] == '\n' || data[0] == '\r')) { return std::string(); }

	int start = 0;
	int end = data.length();

	for(unsigned int i=0;i<data.length();i++) {
		if(data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\r') {
			break;
		}

		start++;
	}

	for(unsigned int i=data.length() - 1;i>=0;i--) {
		if(data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\r') {
			break;
		}

		end--;
	}

	if(start > end) { return std::string(); }

	return data.substr(start, end - start);
}
#endif // USE_STL

#if USE_STL
std::string Utilities::substring(const std::string & data, int start, int end) {
	if(data.empty() || start > end) { return std::string(); }

	int startPos = start < 0 ? 0 : start;
	int endPos = end > static_cast<int>(data.length()) ? static_cast<int>(data.length()) : end;

	return data.substr(startPos, endPos - startPos);
}
#endif // USE_STL

int Utilities::compareStrings(const char * s1, const char * s2, bool caseSensitive) {
	if(s1 == NULL && s2 == NULL) { return 0; }
	if(s1 == NULL && s2 != NULL) { return -1; }
	if(s1 != NULL && s2 == NULL) { return 1; }

	if(caseSensitive) {
#if _WIN32
		return strcmp(s1, s2);
#else
		return strcmp(s1, s2);
#endif // _WIN32
	}
	else {
		int n1 = stringLength(s1);
		int n2 = stringLength(s2);
		int min = n1 < n2 ? n1 : n2;
		for(int i=0;i<min;i++) {
			char c1 = s1[i];
			char c2 = s2[i];
			if(c1 != c2) {
				c1 |= 0x20;
				c2 |= 0x20;
				if(c1 != c2) {
					c1 &= 0xDF;
					c2 &= 0xDF;
					if(c1 != c2) {
						return c1 - c2;
					}
				}
			}
		}
		return n1 - n2;
	}
}

#if USE_STL
int Utilities::compareStrings(const std::string & s1, const std::string & s2, bool caseSensitive) {
	return compareStrings(s1.data(), s2.data(), caseSensitive);
}

int Utilities::compareStrings(const char * s1, const std::string & s2, bool caseSensitive) {
	return compareStrings(s1, s2.data(), caseSensitive);
}

int Utilities::compareStrings(const std::string & s1, const char * s2, bool caseSensitive) {
	return compareStrings(s1.data(), s2, caseSensitive);
}
#endif // USE_STL

int Utilities::compareStringsIgnoreCase(const char * s1, const char * s2) {
	return compareStrings(s1, s2, false);
}

#if USE_STL
int Utilities::compareStringsIgnoreCase(const std::string & s1, const std::string & s2) {
	return compareStrings(s1.data(), s2.data(), false);
}

int Utilities::compareStringsIgnoreCase(const char * s1, const std::string & s2) {
	return compareStrings(s1, s2.data(), false);
}

int Utilities::compareStringsIgnoreCase(const std::string & s1, const char * s2) {
	return compareStrings(s1.data(), s2, false);
}
#endif // USE_STL

int Utilities::firstIndexOf(const char * data, char c) {
	if(data == NULL) { return -1; }
	
	int length = stringLength(data);
	for(int i=0;i<length;i++) {
		if(data[i] == c) {
			return i;
		}
	}
	return -1;
}

int Utilities::lastIndexOf(const char * data, char c) {
	if(data == NULL) { return -1; }
	
	for(int i=stringLength(data)-1;i>=0;i--) {
		if(data[i] == c) {
			return i;
		}
	}
	return -1;
}

std::string Utilities::getVariableID(const char * data) {
	if(data == NULL) { return std::string(); }

	return getVariableID(std::string(data));
}

std::string Utilities::getVariableID(const std::string & data) {
	if(data.empty()) { return std::string(); }

	std::string formattedData = trimString(data);
	
	if(formattedData.empty()) { return std::string(); }

	int separatorIndex = -1;
	for(unsigned int i=0;i<formattedData.length();i++) {
		if(formattedData[i] == ':' || formattedData[i] == '=') {
			separatorIndex = i;
			break;
		}
	}
	if(separatorIndex < 0) { return std::string(); }

	return trimString(substring(formattedData, 0, separatorIndex));
}

std::string Utilities::getVariableValue(const char * data) {
	return getVariableValue(std::string(data));
}

std::string Utilities::getVariableValue(const std::string & data) {
	if(data.empty()) { return std::string(); }

	std::string formattedData = trimString(data);
	
	if(formattedData.empty()) { return std::string(); }

	int separatorIndex = -1;
	for(unsigned int i=0;i<formattedData.length();i++) {
		if(formattedData[i] == ':' || formattedData[i] == '=') {
			separatorIndex = i;
			break;
		}
	}
	if(separatorIndex < 0) { return std::string(); }

	return trimString(substring(formattedData, separatorIndex + 1, formattedData.length()));
}

bool Utilities::parseBoolean(const char * data, bool * valid) {
	if(data == NULL) {
		if(valid != NULL) { *valid = false; }
		return false;
	}

	std::string trimmedData = trimString(std::string(data));
	if(trimmedData.empty()) {
		if(valid != NULL) { *valid = false; }
		return false;
	}

	if(trimmedData.length() == 1) {
		if(trimmedData[0] == 't' ||
		   trimmedData[0] == '1' ||
		   trimmedData[0] == 'y') {
			if(valid != NULL) { *valid = true; }
			return true;
		}
		else if(trimmedData[0] == 'f' ||
				trimmedData[0] == '0' ||
				trimmedData[0] == 'n') {
			if(valid != NULL) { *valid = true; }
			return false;
		}
	}
	else {
		if(compareStringsIgnoreCase(trimmedData, "true") == 0 ||
		   compareStringsIgnoreCase(trimmedData, "on") == 0 ||
		   compareStringsIgnoreCase(trimmedData, "yes") == 0) {
			if(valid != NULL) { *valid = true; }
			return true;
		}
		else if(compareStringsIgnoreCase(trimmedData, "false") == 0 ||
				compareStringsIgnoreCase(trimmedData, "off") == 0 ||
				compareStringsIgnoreCase(trimmedData, "no") == 0) {
			if(valid != NULL) { *valid = true; }
			return false;
		}
	}

	if(valid != NULL) { *valid = false; }
	return false;
}

#if USE_STL
bool Utilities::parseBoolean(const std::string & data, bool * valid) {
	if(data.empty()) {
		if(valid != NULL) { *valid = false; }
		return false;
	}

	return parseBoolean(data.data(), valid);
}
#endif // USE_STL

int Utilities::parseInteger(const char * data, bool * valid) {
	if(data == NULL || stringLength(data) == 0) {
		if(valid != NULL) { *valid = false; }
		return 0;
	}

#if USE_QT
	QString formattedData = QString(data).trimmed();
	int value = formattedData.toInt(valid);
	return value;
#elif USE_STL
	std::string trimmedData = trimString(std::string(data));
	if(trimmedData.empty()) {
		if(valid != NULL) { *valid = false; }
		return 0;
	}

	for(unsigned int i=0;i<trimmedData.length();i++) {
		if(!(trimmedData[i] == '-' || (trimmedData[i] >= '0' && trimmedData[i] <= '9'))) {
			if(valid != NULL) { *valid = false; }
			return 0;
		}
	}

	if(valid != NULL) { *valid = true; }
	float value = atoi(trimmedData.data());

	return value;
#endif // USE_QT
}

#if USE_STL
int Utilities::parseInteger(const std::string & data, bool * valid) {
	if(data.empty()) {
		if(valid != NULL) { *valid = false; }
		return 0;
	}

	return parseInteger(data.data(), valid);
}
#endif // USE_STL

float Utilities::parseFloat(const char * data, bool * valid) {
	if(data == NULL || stringLength(data) == 0) {
		if(valid != NULL) { *valid = false; }
		return 0.0f;
	}

#if USE_QT
	QString formattedData = QString(data).trimmed();
	float value = formattedData.toFloat(valid);
	return value;
#elif USE_STL
	std::string trimmedData = trimString(std::string(data));
	if(trimmedData.empty()) {
		if(valid != NULL) { *valid = false; }
		return 0.0f;
	}
	
	for(unsigned int i=0;i<trimmedData.length();i++) {
		if(!(trimmedData[i] == '-' || trimmedData[i] == '.' || (trimmedData[i] >= '0' && trimmedData[i] <= '9'))) {
			if(valid != NULL) { *valid = false; }
			return 0.0f;
		}
	}

	if(valid != NULL) { *valid = true; }
	float value = atof(trimmedData.data());

	return value;
#endif // USE_QT
}

#if USE_STL
float Utilities::parseFloat(const std::string & data, bool * valid) {
	if(data.empty()) {
		if(valid != NULL) { *valid = false; }
		return 0.0f;
	}

	return parseFloat(data.data(), valid);
}
#endif // USE_STL


std::string Utilities::generateFullPath(const char * path, const char * fileName) {
	return generateFullPath(std::string(path), std::string(fileName));
}

std::string Utilities::generateFullPath(const std::string & path, const std::string & fileName) {
	std::string trimmedPath = trimString(path);
	std::string trimmedFileName = trimString(fileName);
	std::string fullPath("");

	if(trimmedPath.empty())	 { return trimmedFileName; }
	if(trimmedFileName.empty()) { return trimmedPath; }

	if(compareStrings(trimmedPath, ".") != 0) {
		fullPath.append(trimmedPath);

		if(trimmedPath[trimmedPath.length() - 1] != '/' && trimmedPath[trimmedPath.length() - 1] != '\\') {
			fullPath.append("/");
		}
	}

	fullPath.append(trimmedFileName);

	return fullPath;
}

#ifndef ASTEROID_TYPE_H
#define ASTEROID_TYPE_H

#include "Utilities/Utilities.h"

namespace AsteroidTypes {
	enum AsteroidType {
		Invalid = -1,
		Random,
		Small,
		Large,
		NumberOfTypes
	};
	
	extern const char * typeStrings[];
	extern const AsteroidType defaultType;
	
	bool isValid(AsteroidType type);
	bool isValid(int type);
	const char * toString(AsteroidType type);
	const char * toString(int type);
	AsteroidType parseFrom(const char * data);
	AsteroidType parseFrom(const std::string & data);
}

#endif // ASTEROID_TYPE_H

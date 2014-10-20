#include "GameObjects/AsteroidType.h"

const char * AsteroidTypes::typeStrings[] = { "Random", "Small", "Large" };
const AsteroidTypes::AsteroidType AsteroidTypes::defaultType = AsteroidTypes::Random;

bool AsteroidTypes::isValid(AsteroidType type) {
	return type > Invalid && type < NumberOfTypes;
}

bool AsteroidTypes::isValid(int type) {
	return type > static_cast<int>(Invalid) && type < static_cast<int>(NumberOfTypes);
}

const char * AsteroidTypes::toString(AsteroidType type) {
	return toString(static_cast<int>(type));
}

const char * AsteroidTypes::toString(int type) {
	if(!isValid(type)) { return "Invalid"; }

	return typeStrings[type];
}

AsteroidTypes::AsteroidType AsteroidTypes::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	AsteroidType type = Invalid;

	std::string typeString = Utilities::trimString(std::string(data));

	for(int i=0;i<static_cast<int>(NumberOfTypes);i++) {
		if(Utilities::compareStringsIgnoreCase(typeString.data(), typeStrings[i]) == 0) {
			type = static_cast<AsteroidType>(i);
			break;
		}
	}

	return type;
}

AsteroidTypes::AsteroidType AsteroidTypes::parseFrom(const std::string & data) {
	return parseFrom(data.data());
}

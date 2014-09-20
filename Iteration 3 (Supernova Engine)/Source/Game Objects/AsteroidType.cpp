#include "Game Objects/AsteroidType.h"

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

	char * typeString = Utilities::trimCopyString(data);

	for(int i=0;i<static_cast<int>(NumberOfTypes);i++) {
		if(Utilities::compareStringsIgnoreCase(typeString, typeStrings[i]) == 0) {
			type = static_cast<AsteroidType>(i);
			break;
		}
	}

	delete [] typeString;

	return type;
}

AsteroidTypes::AsteroidType AsteroidTypes::parseFrom(const QString & data) {
	QByteArray dataBytes = data.toLocal8Bit();
	return parseFrom(dataBytes.data());
}

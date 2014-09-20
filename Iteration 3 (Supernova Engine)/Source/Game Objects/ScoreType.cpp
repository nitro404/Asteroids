#include "Game Objects/ScoreType.h"

const char * ScoreTypes::typeStrings[] = { "Space Ship", "Small Asteroid", "Large Asteroid" };
const int ScoreTypes::scoreValues[] = { 50, 5, 10 };
const ScoreTypes::ScoreType ScoreTypes::defaultType = ScoreTypes::SpaceShip;

bool ScoreTypes::isValid(ScoreType type) {
	return type > Invalid && type < NumberOfTypes;
}

bool ScoreTypes::isValid(int type) {
	return type > static_cast<int>(Invalid) && type < static_cast<int>(NumberOfTypes);
}

const char * ScoreTypes::toString(ScoreType type) {
	return toString(static_cast<int>(type));
}

const char * ScoreTypes::toString(int type) {
	if(!isValid(type)) { return "Invalid"; }

	return typeStrings[type];
}

int ScoreTypes::getScoreValue(ScoreType type) {
	if(!isValid(type)) { return 0; }

	return scoreValues[static_cast<int>(type)];
}

int ScoreTypes::getScoreValue(int type) {
	if(!isValid(type)) { return 0; }

	return scoreValues[type];
}

int ScoreTypes::getScoreValue(const char * data) {
	ScoreType type = parseFrom(data);

	if(!isValid(type)) { return 0; }

	return scoreValues[static_cast<int>(type)];
}

int ScoreTypes::getScoreValue(const QString & data) {
	ScoreType type = parseFrom(data);

	if(!isValid(type)) { return 0; }

	return scoreValues[static_cast<int>(type)];
}

ScoreTypes::ScoreType ScoreTypes::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	ScoreType type = Invalid;

	char * typeString = Utilities::trimCopyString(data);

	for(int i=0;i<static_cast<int>(NumberOfTypes);i++) {
		if(Utilities::compareStringsIgnoreCase(typeString, typeStrings[i]) == 0) {
			type = static_cast<ScoreType>(i);
			break;
		}
	}

	delete [] typeString;

	return type;
}

ScoreTypes::ScoreType ScoreTypes::parseFrom(const QString & data) {
	QByteArray dataBytes = data.toLocal8Bit();
	return parseFrom(dataBytes.data());
}

#include "Game Objects/RotationDirection.h"

const char * RotationDirections::rotationDirectionStrings[] = { "Clockwise" "Counter-Clockwise" };
const RotationDirections::RotationDirection RotationDirections::defaultRotationDirection = RotationDirections::Clockwise;

bool RotationDirections::isValid(RotationDirection rotationDirection) {
	return rotationDirection > Invalid && rotationDirection < NumberOfRotationDirections;
}

bool RotationDirections::isValid(int rotationDirection) {
	return rotationDirection > static_cast<int>(Invalid) && rotationDirection < static_cast<int>(NumberOfRotationDirections);
}

const char * RotationDirections::toString(RotationDirection rotationDirection) {
	return toString(static_cast<int>(rotationDirection));
}

const char * RotationDirections::toString(int rotationDirection) {
	if(!isValid(rotationDirection)) { return "Invalid"; }

	return rotationDirectionStrings[rotationDirection];
}

RotationDirections::RotationDirection RotationDirections::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	RotationDirection rotationDirection = Invalid;

	char * directionString = Utilities::trimCopyString(data);

	for(int i=0;i<static_cast<int>(NumberOfRotationDirections);i++) {
		if(Utilities::compareStringsIgnoreCase(directionString, rotationDirectionStrings[i]) == 0) {
			rotationDirection = static_cast<RotationDirection>(i);
			break;
		}
	}

	delete [] directionString;

	return rotationDirection;
}

RotationDirections::RotationDirection RotationDirections::parseFrom(const QString & data) {
	QByteArray dataBytes = data.toLocal8Bit();
	return parseFrom(dataBytes.data());
}

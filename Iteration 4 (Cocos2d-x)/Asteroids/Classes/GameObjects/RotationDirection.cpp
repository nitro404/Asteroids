#include "GameObjects/RotationDirection.h"

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

	std::string directionString = Utilities::trimString(std::string(data));

	for(int i=0;i<static_cast<int>(NumberOfRotationDirections);i++) {
		if(Utilities::compareStringsIgnoreCase(directionString.data(), rotationDirectionStrings[i]) == 0) {
			rotationDirection = static_cast<RotationDirection>(i);
			break;
		}
	}

	return rotationDirection;
}

RotationDirections::RotationDirection RotationDirections::parseFrom(const std::string & data) {
	return parseFrom(data.data());
}

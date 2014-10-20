#include "GameObjects/SpaceShipMovementDirection.h"

const char * SpaceShipMovementDirections::directionStrings[] = { "Idle", "Move Forward", "Move Backward", "Turn Left", "Turn Right" };
const SpaceShipMovementDirections::SpaceShipMovementDirection SpaceShipMovementDirections::defaultDirection = SpaceShipMovementDirections::Idle;

bool SpaceShipMovementDirections::isValid(SpaceShipMovementDirection direction) {
	return direction > Invalid && direction < NumberOfDirections;
}

bool SpaceShipMovementDirections::isValid(int direction) {
	return direction > static_cast<int>(Invalid) && direction < static_cast<int>(NumberOfDirections);
}

const char * SpaceShipMovementDirections::toString(SpaceShipMovementDirection direction) {
	return toString(static_cast<int>(direction));
}

const char * SpaceShipMovementDirections::toString(int direction) {
	if(!isValid(direction)) { return "Invalid"; }

	return directionStrings[direction];
}

SpaceShipMovementDirections::SpaceShipMovementDirection SpaceShipMovementDirections::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	SpaceShipMovementDirection direction = Invalid;

	std::string directionString = Utilities::trimString(std::string(data));

	for(int i=0;i<static_cast<int>(NumberOfDirections);i++) {
		if(Utilities::compareStringsIgnoreCase(directionString.data(), directionStrings[i]) == 0) {
			direction = static_cast<SpaceShipMovementDirection>(i);
			break;
		}
	}

	return direction;
}

SpaceShipMovementDirections::SpaceShipMovementDirection SpaceShipMovementDirections::parseFrom(const std::string & data) {
	return parseFrom(data.data());
}
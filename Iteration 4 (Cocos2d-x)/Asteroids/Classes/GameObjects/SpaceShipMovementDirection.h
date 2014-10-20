#ifndef SPACE_SHIP_MOVEMENT_DIRECTION_H
#define SPACE_SHIP_MOVEMENT_DIRECTION_H

#include "Utilities/Utilities.h"

namespace SpaceShipMovementDirections {
	enum SpaceShipMovementDirection {
		Invalid = -1,
		Idle,
		MoveForward,
		MoveBackward,
		TurnLeft,
		TurnRight,
		NumberOfDirections
	};
	
	extern const char * directionStrings[];
	extern const SpaceShipMovementDirection defaultDirection;
	
	bool isValid(SpaceShipMovementDirection direction);
	bool isValid(int direction);
	const char * toString(SpaceShipMovementDirection direction);
	const char * toString(int direction);
	SpaceShipMovementDirection parseFrom(const char * data);
	SpaceShipMovementDirection parseFrom(const std::string & data);
}

#endif // SPACE_SHIP_MOVEMENT_DIRECTION_H

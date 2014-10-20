#ifndef ROTATION_DIRECTION_H
#define ROTATION_DIRECTION_H

#include "Utilities/Utilities.h"

namespace RotationDirections {
	enum RotationDirection {
		Invalid = -1,
		Clockwise,
		CounterClockwise,
		NumberOfRotationDirections
	};
	
	extern const char * rotationDirectionStrings[];
	extern const RotationDirection defaultRotationDirection;
	
	bool isValid(RotationDirection rotationDirection);
	bool isValid(int rotationDirection);
	const char * toString(RotationDirection rotationDirection);
	const char * toString(int rotationDirection);
	RotationDirection parseFrom(const char * data);
	RotationDirection parseFrom(const std::string & data);
}

#endif // ROTATION_DIRECTION_H

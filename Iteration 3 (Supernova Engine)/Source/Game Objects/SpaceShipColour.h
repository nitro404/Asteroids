#ifndef SPACE_SHIP_COLOUR_H
#define SPACE_SHIP_COLOUR_H

#include <QString.h>
#include "Utilities/Utilities.h"
#include "Utilities/Colour.h"

namespace SpaceShipColours {
	enum SpaceShipColour {
		Invalid = -1,
		Red,
		Blue,
		Green,
		Yellow,
		NumberOfColours
	};
	
	extern const Colour colours[];
	extern const char * colourStrings[];
	extern const SpaceShipColour defaultColour;
	
	bool isValid(SpaceShipColour colour);
	bool isValid(int colour);
	bool isValid(const Colour & colour);
	const char * toString(SpaceShipColour colour);
	const char * toString(int colour);
	const char * toString(const Colour & colour);
	Colour getColour(SpaceShipColour colour);
	Colour getColour(int colour);
	SpaceShipColour getColour(const Colour & colour);
	Colour getColour(const char * data);
	Colour getColour(const QString & data);
	SpaceShipColour parseFrom(const char * data);
	SpaceShipColour parseFrom(const QString & data);
}

#endif // SPACE_SHIP_COLOUR_H

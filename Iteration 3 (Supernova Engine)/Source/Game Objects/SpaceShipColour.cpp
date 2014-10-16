#include "Game Objects/SpaceShipColour.h"

const Colour SpaceShipColours::colours[] = { Colour::Red, Colour::Blue, Colour::Lime, Colour::Yellow };
const char * SpaceShipColours::colourStrings[] = { "Red", "Blue", "Green", "Yellow" };
const SpaceShipColours::SpaceShipColour SpaceShipColours::defaultColour = SpaceShipColours::Red;

bool SpaceShipColours::isValid(SpaceShipColour colour) {
	return colour > Invalid && colour < NumberOfColours;
}

bool SpaceShipColours::isValid(int colour) {
	return colour > static_cast<int>(Invalid) && colour < static_cast<int>(NumberOfColours);
}

bool SpaceShipColours::isValid(const Colour & colour) {
	for(int i=0;i<NumberOfColours;i++) {
		if(colour == colours[i]) {
			return true;
		}
	}
	return false;
}

const char * SpaceShipColours::toString(SpaceShipColour colour) {
	return toString(static_cast<int>(colour));
}

const char * SpaceShipColours::toString(int colour) {
	if(!isValid(colour)) { return "Invalid"; }

	return colourStrings[colour];
}

const char * SpaceShipColours::toString(const Colour & colour) {
	for(int i=0;i<NumberOfColours;i++) {
		if(colour == colours[i]) {
			return colourStrings[i];
		}
	}
	return NULL;
}

Colour SpaceShipColours::getColour(SpaceShipColour colour) {
	if(!isValid(colour)) { return Colour::White; }

	return colours[static_cast<int>(colour)];
}

Colour SpaceShipColours::getColour(int colour) {
	if(!isValid(colour)) { return Colour::White; }

	return colours[colour];
}

SpaceShipColours::SpaceShipColour SpaceShipColours::getColour(const Colour & colour) {
	for(int i=0;i<NumberOfColours;i++) {
		if(colour == colours[i]) {
			return static_cast<SpaceShipColour>(i);
		}
	}
	return Invalid;
}

Colour SpaceShipColours::getColour(const char * data) {
	SpaceShipColour colour = parseFrom(data);

	if(!isValid(colour)) { return Colour::White; }

	return colours[colour];
}

Colour SpaceShipColours::getColour(const QString & data) {
	SpaceShipColour colour = parseFrom(data);

	if(!isValid(colour)) { return Colour::White; }

	return colours[colour];
}

SpaceShipColours::SpaceShipColour SpaceShipColours::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	SpaceShipColour colour = Invalid;

	char * colourString = Utilities::trimCopyString(data);

	for(int i=static_cast<int>(Invalid)+1;i<static_cast<int>(NumberOfColours);i++) {
		if(Utilities::compareStringsIgnoreCase(colourString, colourStrings[i]) == 0) {
			colour = static_cast<SpaceShipColour>(i);
			break;
		}
	}

	delete [] colourString;

	return colour;
}

SpaceShipColours::SpaceShipColour SpaceShipColours::parseFrom(const QString & data) {
	QByteArray dataBytes = data.toLocal8Bit();
	return parseFrom(dataBytes.data());
}

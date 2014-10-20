#include "SpriteAnimationSystem/SpriteAnimationType.h"

const char * SpriteAnimationTypes::spriteAnimationTypeStrings[] = { "Single", "Loop" };
const SpriteAnimationTypes::SpriteAnimationType SpriteAnimationTypes::defaultSpriteAnimationType = SpriteAnimationTypes::Single;

bool SpriteAnimationTypes::isValid(SpriteAnimationType type) {
	return type > Invalid && type < NumberOfSpriteAnimationTypes;
}

bool SpriteAnimationTypes::isValid(int type) {
	return type > static_cast<int>(Invalid) && type < static_cast<int>(NumberOfSpriteAnimationTypes);
}

const char * SpriteAnimationTypes::toString(SpriteAnimationType type) {
	return toString(static_cast<int>(type));
}

const char * SpriteAnimationTypes::toString(int type) {
	if(!isValid(type)) { return "Invalid"; }

	return spriteAnimationTypeStrings[type];
}

SpriteAnimationTypes::SpriteAnimationType SpriteAnimationTypes::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	SpriteAnimationType type = Invalid;

	std::string typeString = Utilities::trimString(std::string(data));

	for(int i=0;i<static_cast<int>(NumberOfSpriteAnimationTypes);i++) {
		if(Utilities::compareStringsIgnoreCase(typeString.data(), spriteAnimationTypeStrings[i]) == 0) {
			type = static_cast<SpriteAnimationType>(i);
			break;
		}
	}

	return type;
}

SpriteAnimationTypes::SpriteAnimationType SpriteAnimationTypes::parseFrom(const std::string & data) {
	return parseFrom(data.data());
}

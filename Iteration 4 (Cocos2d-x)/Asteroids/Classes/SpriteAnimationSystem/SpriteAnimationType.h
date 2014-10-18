#ifndef SPRITE_ANIMATION_TYPE_H
#define SPRITE_ANIMATION_TYPE_H

#include "Utilities/Utilities.h"

namespace SpriteAnimationTypes {
	enum SpriteAnimationType {
		Invalid = -1,
		Single,
		Loop,
		Custom,
		NumberOfSpriteAnimationTypes
	};
	
	extern const char * spriteAnimationTypeStrings[];
	extern const SpriteAnimationType defaultSpriteAnimationType;
	
	bool isValid(SpriteAnimationType type);
	bool isValid(int type);
	const char * toString(SpriteAnimationType type);
	const char * toString(int type);
	SpriteAnimationType parseFrom(const char * data);
	SpriteAnimationType parseFrom(const std::string & data);
}

#endif // SPRITE_ANIMATION_TYPE_H

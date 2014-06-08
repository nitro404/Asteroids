#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(Sprite * externalSpriteSheet,
						 int xOffset,
						 int yOffset,
						 int width,
						 int height,
						 int xIncrement,
						 int yIncrement,
						 int numberOfSprites)
							: spriteSheet(externalSpriteSheet) {
	// parse and create a specified number of sprites from a sprite (texture) incrementally using given offsets,
	// width, height and horizontal/vertical increments
	for(int i=0;i<numberOfSprites;i++) {
		sprites.push_back(new Sprite(xOffset + (xIncrement * i),
									 yOffset + (yIncrement * i),
									 width,
									 height,
									 spriteSheet->getTexture(),
									 spriteSheet->getSprite()));
	}
}

SpriteSheet::SpriteSheet(Sprite * externalSpriteSheet,
						 SpriteSheetOffset * offsets,
						 int numberOfSprites)
							: spriteSheet(externalSpriteSheet) {
	// parse and create a specified number of sprites from a sprite (texture) from the specified collection of offsets
	for(int i=0;i<numberOfSprites;i++) {
		sprites.push_back(new Sprite(offsets[i].x,
									 offsets[i].y,
									 offsets[i].w,
									 offsets[i].h,
									 spriteSheet->getTexture(),
									 spriteSheet->getSprite()));
	}
}

SpriteSheet::~SpriteSheet() {
	for(unsigned int i=0;i<sprites.size();i++) {
		if(sprites.at(i) != NULL) { delete sprites.at(i); }
	}
}

Sprite * SpriteSheet::getSprite(int index) {
	// extract a specific sprite from the sprite sheet
	return sprites.at(index);
}

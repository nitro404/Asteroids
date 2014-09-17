#include "Includes.h"
#include "Sprite.h"

struct SpriteSheetOffset {
	int x, y;
	int w, h;
};

// an abstraction for easily parsing through a sprite sheet image and extracting / creating sprite abstractions for each sprite contained within the image
class SpriteSheet {
public:
	// create a specified number of sprites from a collection of offsets (x, y, w, h) within a given sprite sheet image (game sprite)
	SpriteSheet::SpriteSheet(Sprite * externalSpriteSheet, SpriteSheetOffset * offsets, int numberOfSprites);
	// create a specified number of sprites from an offset and set of constant increments / dimensions in a given sprite sheet image (game sprite)
	SpriteSheet::SpriteSheet(Sprite * externalSpriteSheet, int xOffset, int yOffset, int width, int height, int xIncrement, int yIncrement, int numberOfSprites);
	~SpriteSheet();

	// extract a game sprite created by the spritesheet for usage in the game
	Sprite * SpriteSheet::getSprite(int index);

private:
	// the sprites parsed and created by the sprite sheet
	vector<Sprite *> sprites;

	// the game sprite data containing the full sprite sheet image for the game (or part of the game)
	Sprite * spriteSheet;
};

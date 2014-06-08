#pragma once

#include "Object.h"

class SpriteSheet;

// an explosion
class Explosion : public Object {
public:
	Explosion(float xPos, float yPos, float xVelocity, float yVelocity, float angleDegrees, int windowWidth, int windowHeight, SpriteSheet * spriteSheet, int spriteSheetOffset, LPDIRECT3DDEVICE9 d3dDevice);
	~Explosion() { }

	void tick(); // update the explosion's state (advance the animation sequence)
	void draw(LPDIRECT3DDEVICE9 d3dDevice); // draw the explosion

	bool checkCollision(Object & o) { return false; } // an explosion never collides with anything

	bool done(); // has the explosion reached the end of its animation sequence?

private:
	// the collection of sprites and current explosion sprite
	SpriteSheet * spriteSheet;
	Sprite * explosionSprite;

	// the offset at which the first explosion sprite is located
	int spriteSheetOffset;

	// the explosion animation sequence values
	int explosionSequence;
	int explosionSequenceInterval;
	int explosionSequenceEnd;
};

#include "Explosion.h"
#include "SpriteSheet.h"

Explosion::Explosion(float xPos,
					 float yPos,
					 float xVelocity,
					 float yVelocity,
					 float angleDegrees,
					 int windowWidth,
					 int windowHeight,
					 SpriteSheet * spriteSheet,
					 int spriteSheetOffset,
					 LPDIRECT3DDEVICE9 d3dDevice)
						: explosionSprite(NULL) {
	// set boundaries
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	// initialize sprites
	this->spriteSheet = spriteSheet;
	this->spriteSheetOffset = spriteSheetOffset;
	this->explosionSprite = spriteSheet->getSprite(spriteSheetOffset);
	
	// set initial sprite transformations and attributes
	this->orientation = orientation;

	this->position = D3DXVECTOR2(xPos, yPos);

	this->offset = D3DXVECTOR2((explosionSprite->getWidth() / 2.0f), (explosionSprite->getHeight() / 2.0f));

	this->scale = D3DXVECTOR2(1, 1);

	this->velocity = D3DXVECTOR2(xVelocity, yVelocity);

	// initialize the initial animation sequence values
	this->explosionSequence = 0;
	this->explosionSequenceInterval = 7;
	this->explosionSequenceEnd = explosionSequenceInterval * 4;
}

void Explosion::tick() {
	// get the appropriate explosion sprite based on the elapsed time
	explosionSprite = spriteSheet->getSprite(spriteSheetOffset + (explosionSequence / explosionSequenceInterval));

	// increment the explosion position (slow it down by 20% each time)
	position += (velocity * 0.8f);

	// update the offset
	offset.x = (explosionSprite->getWidth() / 2.0f) * scale.x;
	offset.y = (explosionSprite->getHeight() / 2.0f) * scale.y;

	// increment the animation sequence
	if(explosionSequence < explosionSequenceEnd) {
		explosionSequence++;
	}
}

void Explosion::draw(LPDIRECT3DDEVICE9 d3dDevice) {
	// draw the explosion
	explosionSprite->draw(&scale, &offset, 0, NULL, &position, d3dDevice);
}

bool Explosion::done() {
	// is the animation sequence finished?
	return explosionSequence >= explosionSequenceEnd;
}

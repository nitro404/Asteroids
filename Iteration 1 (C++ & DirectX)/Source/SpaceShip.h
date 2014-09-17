#pragma once

#include "Object.h"
#include "Projectile.h"
#include "Sound.h"

class SpriteSheet;

class SpaceShip : public Object {
public:
	SpaceShip(float xPos, float yPos, float angleDegrees, int windowWidth, int windowHeight, SpriteSheet * spriteSheet, int spriteSheetOffset, Sprite * projectileSprite, Sound * laserSound, LPDIRECT3DDEVICE9 d3dDevice);
	~SpaceShip();
	
	void tick(); // update the ship
	void draw(LPDIRECT3DDEVICE9 d3dDev); // draw the ship
	void reset(bool clearProjectiles); // reset the ship to its original state
	void resetToCenter(bool clearProjectiles); // reset the ship to its original state at the center of the screen, facing up

	void turnLeft(); // rotate left
	void turnRight(); // rotate right
	void moveForwards(); // accelerate
	void moveBackwards(); // decelerate

	float getRadiusX() { return offset.x * 0.9f; } // get the horizontal radius
	float getRadiusY() { return offset.y * 0.9f; } // get the vertical radius

	bool checkCollision(Object & o); // is the space ship colliding with another object?
	bool checkExtendedCollision(Object & o); // is an object too close to the ship?
	
	void fireLaser(); // fire the ship's laser

private:
	void updateVelocity(float acc); // update the ship's velocity

public:
	// projectiles fired by the ship
	vector<Projectile *> projectiles;

	// sprite selection variables
	bool isMoving;
	int isRotating;

private:
	// sprite data
	int spriteSheetOffset;
	SpriteSheet * spriteSheet;
	Sprite * spaceShipSprite;
	Sprite * projectileSprite;

	// origin transformation data
	D3DXVECTOR2 origin;
	float originOrientation;

	// animation sequence variables
	int thrusterSequence;
	int thrusterSequenceInterval;
	int thrusterSequenceEnd;

	// laser sound effect
	Sound * laserSound;

	// extended collision detection data
	float extendedCollisionRadius;
};

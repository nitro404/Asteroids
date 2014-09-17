#pragma once

#include "Object.h"

class Asteroid : public Object {
public:
	Asteroid(int windowWidth, int windowHeight, Sprite * sprite, bool bigAsteroid);
	~Asteroid() { }
	
	void tick(); // update the asteroid's state
	void draw(LPDIRECT3DDEVICE9 d3dDevice); // draw the asteroid to the screen

	void randomizePosition();
	void changeRotationDirection() { rotationStep *= -1; } // change the direction the asteroid is rotating

	bool checkCollision(Object & o); // check and see if this asteroid is colliding with another object
	bool isBigAsteroid() { return bigAsteroid; } // check and see if this is a big asteroid

private:
	Sprite * asteroidSprite; // the asteroid sprite
	bool bigAsteroid; // is this a big or small asteroid
};

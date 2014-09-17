#pragma once

#include "Object.h"

class Projectile : public Object {
public:
	Projectile(float x, float y, float orientation, int windowWidth, int windowHeight, Sprite * sprite = NULL);
	~Projectile();
	
	void tick(); // update the projectile
	void draw(LPDIRECT3DDEVICE9 d3dDevice); // draw the projectile

	bool checkCollision(Object & o); // is the projectile colliding with another object?

	bool outOfBounds(); // is the projectile out of bounds?

private:
	Sprite * projectileSprite;
};

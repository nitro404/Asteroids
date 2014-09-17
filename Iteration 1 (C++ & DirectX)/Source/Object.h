#pragma once

#include "Includes.h"
#include "Sprite.h"

class Object {
public:
	Object() { }
	virtual ~Object() { }

	virtual void draw(LPDIRECT3DDEVICE9 d3dDevice) { } // draw the object
	virtual void tick() { } // update the state
	virtual void reset() { } // reset the object

	virtual float getX() { return position.x + offset.x; } // get the horizontal center
	virtual float getY() { return position.y + offset.y; } // get the vertical center
	virtual float getRadiusX() { return offset.x; } // get the horizontal radius
	virtual float getRadiusY() { return offset.y; } // get the vertical radius

	virtual float getOrientation() { return orientation; } // get the current angle (in degrees)
	virtual float getVelocityX() { return velocity.x; } // get the x velocity
	virtual float getVelocityY() { return velocity.y; } // get the y velocity
	virtual float getVelocity() { return sqrt( pow(velocity.x, 2) + pow(velocity.y, 2) ); } // get the combined velocity

	virtual void setPosition(float xPos, float yPos) { position.x = xPos; position.y = yPos; } // change the position
	virtual void setVelocity(float xVel, float yVel) { velocity.x = xVel; velocity.y = yVel; } // change the velocity

	virtual bool checkCollision(Object & o) { return false; } // is the object colliding with another object? (abstract, false by default)

protected:
	// position, offset
	D3DXVECTOR2 position;
	D3DXVECTOR2 offset;

	// angle
	float orientation;
	float rotationStep;
	bool rotationDirection;

	// velocity
	D3DXVECTOR2 velocity;
	float velocityStep;
	float minVelocity;
	float maxVelocity;

	// scaling
	float minScale;
	float maxScale;
	D3DXVECTOR2 scale;
	float scaleSpeed;
	bool scaleDirection;

	// boundaries
	int windowWidth;
	int windowHeight;
};

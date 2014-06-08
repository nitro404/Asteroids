#include "Asteroid.h"

Asteroid::Asteroid(int windowWidth, int windowHeight, Sprite * sprite, bool bigAsteroid) {
	// set boundaries
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	// set sprite
	this->asteroidSprite = sprite;

	// set initial transformation and attributes (randomly generated)
	this->bigAsteroid = bigAsteroid;

	offset = D3DXVECTOR2(asteroidSprite->getWidth() / 2.0f, asteroidSprite->getHeight() / 2.0f);

	float xPos = (float) (rand() % windowWidth);
	float yPos = (float) (rand() % windowHeight);
	position = D3DXVECTOR2(xPos, yPos);

	scaleDirection = (rand() % 2) == 0;
	float minRandomScaleLower = 1.0f;
	float minRandomScaleUpper = 1.13f;
	float maxRandomScaleLower = 1.18f;
	float maxRandomScaleUpper = 1.23f;
	minScale = ((rand() % (int) ((minRandomScaleUpper - minRandomScaleLower) * 10000)) / 10000.0f) + minRandomScaleLower;
	maxScale = ((rand() % (int) ((maxRandomScaleUpper - maxRandomScaleLower) * 10000)) / 10000.0f) + maxRandomScaleLower;
	float scaleXY = ((rand() % (int) ((maxScale - minScale) * 10000)) / 10000) + minScale;
	scale = D3DXVECTOR2(scaleXY, scaleXY);
	float minScaleSpeed = 0.0002f;
	float maxScaleSpeed = 0.0006f;
	scaleSpeed = ((rand() % (int) ((maxScaleSpeed - minScaleSpeed) * 10000)) / 10000.0f) + minScaleSpeed;

	rotationDirection = (rand() % 2) == 0;
	float minRotationStep = 0.3153f;
	float maxRotationStep = 0.4584f;
	rotationStep = (rotationDirection ? 1 : -1) * (((rand() % (int) ((maxRotationStep - minRotationStep) * 10000)) / 10000.0f) + minRotationStep);
	orientation = (float) (rand() % 360);

	velocityStep = 0;
	minVelocity = ((rand() % (int) (0.3 * 10000)) / 10000.0f) + 0.007f;
	maxVelocity = ((rand() % (int) (2.5 * 10000)) / 10000.0f) + 0.8f;
	float velocityX = (((rand() % 2) == 0) ? 1 : -1) * ((rand() % (int) ((maxVelocity - minVelocity) * 10000)) / 10000.0f) + minVelocity;
	float velocityY = (((rand() % 2) == 0) ? 1 : -1) * ((rand() % (int) ((maxVelocity - minVelocity) * 10000)) / 10000.0f) + minVelocity;
	velocity = D3DXVECTOR2(velocityX, velocityY);
}

void Asteroid::tick() {
	if(windowWidth <= 0 || windowHeight <= 0) { return; }

	// increment the scale of the asteroid
	scale.x += (scaleDirection ? 1 : -1) * scaleSpeed;
	scale.y += (scaleDirection ? 1 : -1) * scaleSpeed;

	// boundary check the scale of the asteroid
	if(scale.x > maxScale || scale.y > maxScale) { scaleDirection = !scaleDirection; }
	if(scale.x < minScale || scale.y < minScale) { scaleDirection = !scaleDirection; }

	// increment the rotation of the asteroid
	orientation += rotationStep;
	if(orientation > 360) { orientation -= 360; }
	if(orientation < -360) { orientation += 360; }

	// increment the position of he asteroid
	position += velocity;

	// update the offset
	offset.x = (asteroidSprite->getWidth() / 2.0f);
	offset.y = (asteroidSprite->getHeight() / 2.0f);

	// boundary check the position of the asteroid and make it wrap-around if it is out of bounds
	if(position.x + offset.x > windowWidth) {
		position.x -= windowWidth;
	}
	else if(position.x + offset.x < 0) {
		position.x += windowWidth;
	}

	if(position.y + offset.x > windowHeight) {
		position.y -= windowHeight;
	}
	else if(position.y + offset.x < 0) {
		position.y += windowHeight;
	}
}

void Asteroid::draw(LPDIRECT3DDEVICE9 d3dDevice) {
	// draw the asteroid
	asteroidSprite->draw(&scale, &offset, orientation, &offset, &position, d3dDevice);

	// if debugging, draw the collision detection box of the asteroid
	#if _DEBUG
		testDrawEmptyCircle(d3dDevice, getX(), getY(), getRadiusX(), getRadiusY());
	#endif
}

void Asteroid::randomizePosition() {
	// randomize the position of the asteroid
	position.x = (float) (rand() % windowWidth);
	position.y = (float) (rand() % windowHeight);
}

bool Asteroid::checkCollision(Object & o) {
	// is the asteroid colliding with another object?
	float distance = sqrt(pow(o.getX() - getX(), 2) + pow(o.getY() - getY(), 2));
	return distance < o.getRadiusX() + getRadiusX();
}

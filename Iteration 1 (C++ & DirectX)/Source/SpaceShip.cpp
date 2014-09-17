#include "SpaceShip.h"
#include "SpriteSheet.h"

SpaceShip::SpaceShip(float xPos,
					 float yPos,
					 float angleDegrees,
					 int windowWidth,
					 int windowHeight,
					 SpriteSheet * spriteSheet,
					 int spriteSheetOffset,
					 Sprite * projectileSprite,
					 Sound * laserSound,
					 LPDIRECT3DDEVICE9 d3dDevice)
						: spriteSheet(NULL),
						  spaceShipSprite(NULL),
						  extendedCollisionRadius(200) {
	// set boundaries
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	// initialize sprite data
	this->spriteSheetOffset = spriteSheetOffset;
	this->spriteSheet = spriteSheet;
	this->projectileSprite = projectileSprite;
	this->spaceShipSprite = spriteSheet->getSprite(spriteSheetOffset + 1);

	// set initial transformations and attributes
	this->velocity = D3DXVECTOR2(0, 0);
	this->velocityStep = 0.08f;
	this->maxVelocity = 8;

	this->originOrientation = angleDegrees;
	this->orientation = originOrientation;
	this->rotationStep = 5;

	this->origin = D3DXVECTOR2(xPos, yPos);
	this->position = D3DXVECTOR2(xPos, yPos);

	this->scale = D3DXVECTOR2(1, 1);
	
	this->offset = D3DXVECTOR2(spaceShipSprite->getWidth() / 2.0f, spaceShipSprite->getHeight() / 2.0f);

	// initialize the thruster sequence animation values
	this->thrusterSequence = 0;
	this->thrusterSequenceInterval = 7;
	this->thrusterSequenceEnd = 14;

	// initialize the laser sound effect
	this->laserSound = laserSound;
}

SpaceShip::~SpaceShip() {
	for(unsigned int i=0;i<projectiles.size();i++) {
		delete projectiles.at(i);
	}
}

void SpaceShip::tick() {
	for(unsigned int i=0;i<projectiles.size();i++) {
		// increment the projectiles fired by the ship
		projectiles.at(i)->tick();

		// if any of the projectiles are out of bounds, remove them
		if(projectiles.at(i)->outOfBounds()) {
			delete projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);

			i--;
		}
	}

	// determine the current animation sprite for the ship based on whether it's rotating left, right or not at all and
	// whether it's accelerating/decelerating or idle
	int offsetIndex = 1;
		 if(isRotating < 0) { offsetIndex = 0; }
	else if(isRotating > 0) { offsetIndex = 2; }
	if(!isMoving) {
		spaceShipSprite = spriteSheet->getSprite(spriteSheetOffset + offsetIndex);
	}
	else {
		if(thrusterSequence < thrusterSequenceInterval) {
			spaceShipSprite = spriteSheet->getSprite(spriteSheetOffset + 3 + offsetIndex);
		}
		else {
			spaceShipSprite = spriteSheet->getSprite(spriteSheetOffset + 6 + offsetIndex);
		}
	}

	// increment the thruster sequence animation
	thrusterSequence++;
	if(thrusterSequence > thrusterSequenceEnd) { thrusterSequence = 0; }

	if(windowWidth <= 0 || windowHeight <= 0) { return; }

	// increment the ship's position
	position += velocity;

	// update the offset
	offset.x = (spaceShipSprite->getWidth() / 2.0f) * scale.x;
	offset.y = (spaceShipSprite->getHeight() / 2.0f) * scale.y;

	// make the ship wrap-around if it goes out of bounds
	if(position.x > windowWidth) {
		position.x -= windowWidth;
	}
	else if(position.x < 0) {
		position.x += windowWidth;
	}

	if(position.y > windowHeight) {
		position.y -=  windowHeight;
	}
	else if(position.y < 0) {
		position.y += windowHeight;
	}
}

void SpaceShip::draw(LPDIRECT3DDEVICE9 d3dDevice) {
	// draw the projectiles fired by the ship
	for(unsigned int i=0;i<projectiles.size();i++) {
		projectiles.at(i)->draw(d3dDevice);
	}

	// draw the ship
	spaceShipSprite->draw(&scale, &offset, orientation, &offset, &position, d3dDevice);

	// if debugging, draw a collision detection circle around the ship
	#if _DEBUG
		testDrawPoint(d3dDevice, getX(), getY());
		testDrawPoint(d3dDevice, getX() + (cos(D3DXToRadian(orientation - 90)) * 10), getY() + (sin(D3DXToRadian(orientation - 90)) * 10));
		testDrawEmptyCircle(d3dDevice, getX(), getY(), getRadiusX(), getRadiusY());
	#endif
}

void SpaceShip::reset(bool clearProjectiles) {
	// reset the space ship to it's original state and sprite
	position = origin;
	orientation = originOrientation;
	velocity = D3DXVECTOR2(0, 0);
	isMoving = false;
	isRotating = 0;
	spaceShipSprite = spriteSheet->getSprite(spriteSheetOffset + 1);

	// remove all of the projectiles fired by the ship (if appropriate)
	if(clearProjectiles) {
		for(unsigned int i=0;i<projectiles.size();i++) {
			delete projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);

			i--;
		}
	}
}

void SpaceShip::resetToCenter(bool clearProjectiles) {
	// reset the space ship to iti's original state and sprite at the center of the screen, facing upwards
	position.x = windowWidth / 2.0f;
	position.y = windowHeight / 2.0f;
	orientation = 0;
	velocity = D3DXVECTOR2(0, 0);
	isMoving = false;
	isRotating = 0;
	spaceShipSprite = spriteSheet->getSprite(spriteSheetOffset + 1);

	// remove all of the projectiles fired by the ship (if appropriate)
	if(clearProjectiles) {
		for(unsigned int i=0;i<projectiles.size();i++) {
			delete projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);

			i--;
		}
	}
}

bool SpaceShip::checkCollision(Object & o) {
	// is the space ship colliding with another object?
	float distance = sqrt(pow(o.getX() - getX(), 2) + pow(o.getY() - getY(), 2));
	return distance < o.getRadiusX() + getRadiusX();
}

bool SpaceShip::checkExtendedCollision(Object & o) {
	// is an object too close to the space ship?
	float distance = sqrt(pow(o.getX() - getX(), 2) + pow(o.getY() - getY(), 2));
	return distance < extendedCollisionRadius + o.getRadiusX();
}

void SpaceShip::turnLeft() {
	orientation -= rotationStep;
}

void SpaceShip::turnRight() {
	orientation += rotationStep;
}

void SpaceShip::moveForwards() {
	updateVelocity(velocityStep);
}

void SpaceShip::moveBackwards() {
	updateVelocity(-velocityStep);
}

void SpaceShip::fireLaser() {
	// fire a laser projectile from the tip of the ship
	float xPos = getX() - 2 - (sin(D3DXToRadian(-orientation)) * 14);
	float yPos = getY() - 2 - (cos(D3DXToRadian(-orientation)) * 14);
	projectiles.push_back(new Projectile(xPos, yPos, orientation - 90, windowWidth, windowHeight, projectileSprite));
	laserSound->play();
}

void SpaceShip::updateVelocity(float acc) {
	D3DXVECTOR2 v;
	double speed;
	float epsilon = 0.1f;

	// update the speed so that the ship does not drift 
	speed = sqrt(velocity.x*velocity.x+velocity.y*velocity.y);
	v.x = (float) speed * cos(D3DXToRadian(orientation - 90));
	v.y = (float) speed * sin(D3DXToRadian(orientation - 90));
	if (fabs((v.x - velocity.x)/v.x) < epsilon && fabs((v.y - velocity.y)/v.y) < epsilon) {
		float dx = v.x - velocity.x;
		float dy = v.y - velocity.y;
		dx = dx / v.x;
		dy = dy / v.y;
		dx = fabs(v.x - v.x)/v.x;
		dy = fabs(v.y - velocity.y)/v.y;

		velocity.x = v.x;
		velocity.y = v.y;
	}

	// update the velocity vectors
	v.x = acc * cos(D3DXToRadian(this->orientation - 90));
	v.y = acc * sin(D3DXToRadian(this->orientation - 90));

	v += velocity;
	if(v.x < maxVelocity && v.x > -maxVelocity &&
	   v.y < maxVelocity && v.y > -maxVelocity) {
			this->velocity = v;
	}
}

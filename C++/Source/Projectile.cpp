#include "Projectile.h"

Projectile::Projectile(float x, float y, float orientation, int windowWidth, int windowHeight, Sprite * sprite) {
	// set boundaries
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	// initialize sprite
	this->projectileSprite = sprite;

	// set initial transformations and attributes
	this->orientation = orientation;

	this->position = D3DXVECTOR2(x, y);

	this->offset = D3DXVECTOR2((sprite->getWidth() / 2.0f), (sprite->getHeight() / 2.0f));

	this->scale = D3DXVECTOR2(1, 1);

	float velocityStep = 10;
	velocity.x = velocityStep * cos(D3DXToRadian(orientation));
	velocity.y = velocityStep * sin(D3DXToRadian(orientation));
}

Projectile::~Projectile() { }

void Projectile::tick() {
	// increment the position of the projectile
	position += velocity;

	// update the offset
	offset.x = (projectileSprite->getWidth() / 2.0f) * scale.x;
	offset.y = (projectileSprite->getHeight() / 2.0f) * scale.y;
}

void Projectile::draw(LPDIRECT3DDEVICE9 d3dDevice) {
	// draw the projectile sprite
	projectileSprite->draw(&scale, &offset, orientation + 90, &offset, &position, d3dDevice);

	// if debugging, draw the collision detection circle around the projectile
	#if _DEBUG
		testDrawEmptyCircle(d3dDevice, getX(), getY(), getRadiusX(), getRadiusX());
	#endif
}

bool Projectile::checkCollision(Object & o) {
	// check and see if the projectile is colliding with another object
	float distance = sqrt(pow(o.getX() - getX(), 2) + pow(o.getY() - getY(), 2));
	return distance < o.getRadiusX() + getRadiusX();
}


bool Projectile::outOfBounds() {
	// is the projectile out of bounds?
	return	position.x + projectileSprite->getWidth() < 0 ||
			position.y + projectileSprite->getHeight() < 0 ||
			position.x - projectileSprite->getWidth() > windowWidth ||
			position.y - projectileSprite->getHeight() > windowHeight;
}

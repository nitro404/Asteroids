#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "SpriteAnimationSystem/SpriteAnimation.h"
#include "Entity/AnimatedEntity2D.h"
#include "GameObjects/SpaceShipColour.h"

class SpaceShip;

class Projectile : public AnimatedEntity2D {
public:
	Projectile(Layer * parentLayer, const SpriteAnimation * animation, const SpaceShip * projectileSource, const Vec2 & position = Vec2::ZERO, float rotation = 0.0f);
	Projectile(const Projectile & p);
	Projectile & operator = (const Projectile & p);
	virtual ~Projectile();

	virtual void setRotation(float rotation);

	const SpaceShip * getProjectileSource() const;

	bool operator == (const Projectile & p) const;
	bool operator != (const Projectile & p) const;

private:
	void updateVelocity();

public:
	static const float projectileSize;
	static const float projectileSpeed;

private:	
	const SpaceShip * m_projectileSource;
};

#endif // PROJECTILE_H

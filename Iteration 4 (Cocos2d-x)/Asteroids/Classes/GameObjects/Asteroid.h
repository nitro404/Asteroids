#ifndef ASTEROID_H
#define ASTEROID_H

#include "SpriteAnimationSystem/SpriteAnimation.h"
#include "Entity/Entity2D.h"
#include "GameObjects/AsteroidType.h"
#include "GameObjects/RotationDirection.h"

class Asteroid : public Entity2D {
public:
	Asteroid(Layer * parent, Sprite * sprite, bool largeAsteroid = false, const Vec2 & position = Vec2::ZERO, float size = 0.0f, const Vec2 & scale = Vec2::ONE, float rotation = 0.0f, RotationDirections::RotationDirection rotationDirection = RotationDirections::defaultRotationDirection, float rotationSpeed = 0.0f, const Vec2 & offset = Vec2::ZERO, const Vec2 & velocity = Vec2::ZERO);
	Asteroid(const Asteroid & a);
	Asteroid & operator = (const Asteroid & a);
	virtual ~Asteroid();

	bool isLargeAsteroid() const;
	RotationDirections::RotationDirection getRotationDirection() const;
	float getRotationSpeed() const;

	int numberOfCollisions() const;
	bool hasCollision(const Asteroid * projectile) const;
	int indexOfCollision(const Asteroid * projectile) const;
	const Asteroid * getCollision(int index) const;
	bool addCollision(const Asteroid * asteroid);
	bool removeCollision(int index);
	bool removeCollision(const Asteroid * asteroid);
	void clearCollisions();

	virtual void update(float timeElapsed);

	bool operator == (const Asteroid & a) const;
	bool operator != (const Asteroid & a) const;

public:
	static const float minRotationSpeed;
	static const float maxRotationSpeed;
	static const float minVelocity;
	static const float maxVelocity;

private:
	bool m_largeAsteroid;
	RotationDirections::RotationDirection m_rotationDirection;
	float m_rotationSpeed;

	std::vector<const Asteroid *> m_collisions;
};

#endif // ASTEROID_H

#ifndef ASTEROID_H
#define ASTEROID_H

#include "Sprite Animation System/SpriteAnimation.h"
#include "Entity/AnimatedEntity2D.h"
#include "Game Objects/AsteroidType.h"
#include "Game Objects/RotationDirection.h"

class Asteroid : public Entity2D {
public:
	Asteroid(const Sprite * sprite, bool largeAsteroid = false, const Vector2 & position = Vector2::Zero, float size = 0.0f, const Vector2 & scale = Vector2::One, float rotation = 0.0f, RotationDirections::RotationDirection rotationDirection = RotationDirections::defaultRotationDirection, float rotationSpeed = 0.0f, const Vector2 & offset = Vector2::Zero, const Vector2 & velocity = Vector2::Zero);
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

	virtual void update(unsigned int timeElapsed);

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

	QVector<const Asteroid *> m_collisions;
};

#endif // ASTEROID_H

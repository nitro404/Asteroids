#ifndef ASTEROID_SYSTEM_H
#define ASTEROID_SYSTEM_H

#include <QVector.h>
#include "Sprite Animation System/SpriteAnimationCollection.h"
#include "Game Objects/Asteroid.h"

class SpaceShipSystem;

class AsteroidSystem : public Entity {
public:
	AsteroidSystem();
	AsteroidSystem(const AsteroidSystem & a);
	AsteroidSystem & operator = (const AsteroidSystem & a);
	virtual ~AsteroidSystem();

	int numberOfAsteroids() const;
	bool hasAsteroid(const Asteroid * asteroid) const;
	int indexOfAsteroid(const Asteroid * asteroid) const;
	const Asteroid * getAsteroid(int index) const;
	bool addAsteroid(Asteroid * asteroid);
	bool removeAsteroid(int index);
	bool removeAsteroid(const Asteroid * asteroid);
	void clearAsteroids();

	bool init(const SpriteSheetCollection * spriteSheets, const SpaceShipSystem * spaceShipSystem);

	void spawnAsteroid(AsteroidTypes::AsteroidType type = AsteroidTypes::Random, const Vector2 * newPosition = NULL, const Vector2 * newVelocity = NULL);
	void spawnAsteroidCluster(const Vector2 & position, float radius);

	virtual void reset();
	virtual void update(unsigned int timeElapsed);
	virtual void draw();

	bool operator == (const AsteroidSystem & a) const;
	bool operator != (const AsteroidSystem & a) const;

public:
	static const int maxNumberOfAsteroids;
	static const int numberOfAsteroidSprites;

private:
	bool m_initialized;

	QVector<const Sprite *> m_asteroidSprites;

	QVector<Asteroid *> m_asteroids;

	const SpaceShipSystem * m_spaceShipSystem;
};

#endif // ASTEROID_SYSTEM_H

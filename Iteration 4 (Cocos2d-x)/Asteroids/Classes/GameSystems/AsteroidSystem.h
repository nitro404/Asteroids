#ifndef ASTEROID_SYSTEM_H
#define ASTEROID_SYSTEM_H

#include "SpriteAnimationSystem/SpriteAnimationCollection.h"
#include "GameObjects/Asteroid.h"

class SpaceShipSystem;

class AsteroidSystem : public Entity, public Component {
public:
	AsteroidSystem(Layer * parentLayer);
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

	virtual Layer * getParentLayer() const;
	virtual void setParentLayer(Layer * parent);

	bool init(const SpaceShipSystem * spaceShipSystem);

	void spawnAsteroid(AsteroidTypes::AsteroidType type = AsteroidTypes::Random, const Vec2 * newPosition = NULL, const Vec2 * newVelocity = NULL);
	void spawnAsteroidCluster(const Vec2 & position, float radius);

	virtual void reset();
	virtual void update(float timeElapsed);

	bool operator == (const AsteroidSystem & a) const;
	bool operator != (const AsteroidSystem & a) const;

public:
	static const char * asteroidSystemClassName;
	static const int maxNumberOfAsteroids;
	static const int numberOfAsteroidSprites;

private:
	bool m_initialized;

	std::vector<SpriteFrame *> m_asteroidSpriteFrames;

	std::vector<Asteroid *> m_asteroids;

	const SpaceShipSystem * m_spaceShipSystem;
};

#endif // ASTEROID_SYSTEM_H

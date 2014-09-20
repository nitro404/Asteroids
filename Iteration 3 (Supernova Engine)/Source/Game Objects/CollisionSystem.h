#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <QVector.h>
#include "Sprite Animation System/SpriteAnimationCollection.h"
#include "Entity/Entity.h"
#include "Game Objects/ScoreType.h"

class ProjectileSystem;
class SpaceShipSystem;
class AsteroidSystem;
class ExplosionSystem;
class ScoreSystem;

class CollisionSystem : public Entity {
public:
	CollisionSystem();
	CollisionSystem(const CollisionSystem & c);
	CollisionSystem & operator = (const CollisionSystem & c);
	virtual ~CollisionSystem();

	bool init(ProjectileSystem * projectileSystem, SpaceShipSystem * spaceShipSystem, AsteroidSystem * asteroidSystem, ExplosionSystem * explosionSystem, ScoreSystem * scoreSystem);

	virtual void update(unsigned int timeElapsed);

	bool operator == (const CollisionSystem & c) const;
	bool operator != (const CollisionSystem & c) const;

private:
	void clearAsteroidCollisions(Asteroid * a);
	void handleAsteroidCollision(Asteroid * a, Asteroid * b);

private:
	bool m_initialized;

	ProjectileSystem * m_projectileSystem;
	SpaceShipSystem * m_spaceShipSystem;
	AsteroidSystem * m_asteroidSystem;
	ExplosionSystem * m_explosionSystem;
	ScoreSystem * m_scoreSystem;
};

#endif // COLLISION_SYSTEM_H

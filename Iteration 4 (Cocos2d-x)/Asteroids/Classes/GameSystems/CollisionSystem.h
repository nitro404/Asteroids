#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "SpriteAnimationSystem/SpriteAnimationCollection.h"
#include "Entity/Entity.h"
#include "GameSystems/ScoreSystem.h"

class ProjectileSystem;
class SpaceShipSystem;
class AsteroidSystem;
class ExplosionSystem;
class ScoreSystem;

class CollisionSystem : public Entity, public Component {
public:
	CollisionSystem(Layer * parentLayer);
	CollisionSystem(const CollisionSystem & c);
	CollisionSystem & operator = (const CollisionSystem & c);
	virtual ~CollisionSystem();

	virtual Layer * getParentLayer() const;
	virtual void setParentLayer(Layer * parentLayer);

	bool init(ProjectileSystem * projectileSystem, SpaceShipSystem * spaceShipSystem, AsteroidSystem * asteroidSystem, ExplosionSystem * explosionSystem, ScoreSystem * scoreSystem);

	virtual void update(float timeElapsed);

	bool operator == (const CollisionSystem & c) const;
	bool operator != (const CollisionSystem & c) const;

private:
	void clearAsteroidCollisions(Asteroid * a);
	void handleAsteroidCollision(Asteroid * a, Asteroid * b);

public:
	static const char * collisionSystemClassName;

private:
	bool m_initialized;

	ProjectileSystem * m_projectileSystem;
	SpaceShipSystem * m_spaceShipSystem;
	AsteroidSystem * m_asteroidSystem;
	ExplosionSystem * m_explosionSystem;
	ScoreSystem * m_scoreSystem;
};

#endif // COLLISION_SYSTEM_H

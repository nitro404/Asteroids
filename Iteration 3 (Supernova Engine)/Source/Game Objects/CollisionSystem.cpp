#include "Game Objects/ProjectileSystem.h"
#include "Game Objects/SpaceShipSystem.h"
#include "Game Objects/AsteroidSystem.h"
#include "Game Objects/ExplosionSystem.h"
#include "Game Objects/ScoreSystem.h"
#include "Game Objects/CollisionSystem.h"

CollisionSystem::CollisionSystem()
	: Entity()
	, m_initialized(false)
	, m_projectileSystem(NULL)
	, m_spaceShipSystem(NULL)
	, m_asteroidSystem(NULL)
	, m_explosionSystem(NULL)
	, m_scoreSystem(NULL) {
	
}

CollisionSystem::CollisionSystem(const CollisionSystem & c)
	: Entity(c)
	, m_initialized(c.m_initialized)
	, m_projectileSystem(c.m_projectileSystem)
	, m_spaceShipSystem(c.m_spaceShipSystem)
	, m_asteroidSystem(c.m_asteroidSystem)
	, m_explosionSystem(c.m_explosionSystem)
	, m_scoreSystem(c.m_scoreSystem) {
	
}

CollisionSystem & CollisionSystem::operator = (const CollisionSystem & c) {
	Entity::operator = (c);

	m_initialized = c.m_initialized;
	m_projectileSystem = c.m_projectileSystem;
	m_spaceShipSystem = c.m_spaceShipSystem;
	m_asteroidSystem = c.m_asteroidSystem;
	m_explosionSystem = c.m_explosionSystem;
	m_scoreSystem = c.m_scoreSystem;

	return *this;
}

CollisionSystem::~CollisionSystem() {
	
}

bool CollisionSystem::init(ProjectileSystem * projectileSystem, SpaceShipSystem * spaceShipSystem, AsteroidSystem * asteroidSystem, ExplosionSystem * explosionSystem, ScoreSystem * scoreSystem) {
	if(m_initialized) { return true; }

	if(projectileSystem == NULL || spaceShipSystem == NULL || asteroidSystem == NULL || explosionSystem == NULL || scoreSystem == NULL) { return false; }

	m_projectileSystem = projectileSystem;
	m_spaceShipSystem = spaceShipSystem;
	m_asteroidSystem = asteroidSystem;
	m_explosionSystem = explosionSystem;
	m_scoreSystem = scoreSystem;

	m_initialized = true;

	return true;
}

void CollisionSystem::update(unsigned int timeElapsed) {
	if(!m_initialized) { return; }

	Asteroid * a = NULL;
	Asteroid * b = NULL;
	Projectile * p = NULL;
	SpaceShip * s = NULL;
	SpaceShip * t = NULL;

	// remove any collisions that have been handled and are no longer in collision
	for(int i=0;i<m_asteroidSystem->numberOfAsteroids();i++) {
		a = const_cast<Asteroid *>(m_asteroidSystem->getAsteroid(i));
		for(int j=i+1;j<m_asteroidSystem->numberOfAsteroids();j++) {
			if(i == j) { continue; }

			b = const_cast<Asteroid *>(m_asteroidSystem->getAsteroid(j));

			if((a->hasCollision(b) && !a->checkCollision(*b)) || (b->hasCollision(a) && !b->checkCollision(*a))) {
				a->removeCollision(b);
				b->removeCollision(a);
			}
		}
	}

	
	for(int i=0;i<m_asteroidSystem->numberOfAsteroids();i++) {
		a = const_cast<Asteroid *>(m_asteroidSystem->getAsteroid(i));

		// check asteroid > asteroid collisions
		for(int j=i+1;j<m_asteroidSystem->numberOfAsteroids();j++) {
			if(i == j) { continue; }

			b = const_cast<Asteroid *>(m_asteroidSystem->getAsteroid(j));

			if(a->checkCollision(*b)) {
				handleAsteroidCollision(a, b);
			}
		}

		// check asteroid > projectile collisions
		for(int j=0;j<m_projectileSystem->numberOfProjectiles();j++) {
			p = const_cast<Projectile *>(m_projectileSystem->getProjectile(j));

			if(p->checkCollision(*a)) {
				m_scoreSystem->addScore(p->getProjectileSource(), a->isLargeAsteroid() ? ScoreTypes::LargeAsteroid : ScoreTypes::SmallAsteroid);

				if(a->isLargeAsteroid()) {
					m_asteroidSystem->spawnAsteroidCluster(a->getPosition(), a->getSize() / 2);
				}

				m_explosionSystem->spawnExplosion(a->getPosition(), a->getVelocity());

				clearAsteroidCollisions(a);

				m_asteroidSystem->removeAsteroid(i);
				m_projectileSystem->removeProjectile(j);

				i--;
				j--;

				break;
			}
		}
	}

	for(int i=0;i<m_spaceShipSystem->numberOfSpaceShips();i++) {
		s = const_cast<SpaceShip *>(m_spaceShipSystem->getSpaceShip(i));

		// check ship > ship collisions
		for(int j=i+1;j<m_spaceShipSystem->numberOfSpaceShips();j++) {
			if(i == j) { continue; }

			t = const_cast<SpaceShip *>(m_spaceShipSystem->getSpaceShip(j));

			if(s->checkCollision(*t)) {
				m_explosionSystem->spawnExplosion(s->getPosition(), s->getVelocity());
				m_explosionSystem->spawnExplosion(t->getPosition(), t->getVelocity());

				s->reset();
				t->reset();

				break;
			}
		}

		// check ship > asteroid collisions
		for(int j=0;j<m_asteroidSystem->numberOfAsteroids();j++) {
			a = const_cast<Asteroid *>(m_asteroidSystem->getAsteroid(j));

			if(s->checkCollision(*a)) {
				m_explosionSystem->spawnExplosion(s->getPosition(), s->getVelocity());

				s->reset();

				clearAsteroidCollisions(a);

				m_asteroidSystem->removeAsteroid(j);

				j--;

				break;
			}
		}

		// check ship > projectile collisions
		for(int j=0;j<m_projectileSystem->numberOfProjectiles();j++) {
			p = const_cast<Projectile *>(m_projectileSystem->getProjectile(j));

			if(*p->getProjectileSource() == *s) { continue; }

			if(p->checkCollision(*s)) {
				m_scoreSystem->addScore(p->getProjectileSource(), ScoreTypes::SpaceShip);

				m_explosionSystem->spawnExplosion(s->getPosition(), s->getVelocity());

				s->reset();

				m_projectileSystem->removeProjectile(j);

				j--;

				break;
			}
		}
	}
}

void CollisionSystem::clearAsteroidCollisions(Asteroid * a) {
	if(!m_initialized || a == NULL) { return; }

	Asteroid * b;
	for(int i=0;i<m_asteroidSystem->numberOfAsteroids();i++) {
		b = const_cast<Asteroid *>(m_asteroidSystem->getAsteroid(i));

		if(b->hasCollision(a)) {
			b->removeCollision(a);
			a->removeCollision(b);
		}
	}
}

void CollisionSystem::handleAsteroidCollision(Asteroid * a, Asteroid * b) {
	if(!m_initialized || a == NULL || b == NULL || *a == *b || a->hasCollision(b) || b->hasCollision(a)) { return; }

	a->addCollision(b);
	b->addCollision(a);

	double v = a->getSpeed();

	double dx = abs(b->x() - a->x());
	double dy = abs(b->y() - a->y());
	double d = sqrt((dx * dx) + (dy * dy));

	if(d == 0) { return; }

	double angle_b = asin(dy / d);
	double angle_d = asin(abs(a->getVelocity().x) / v);
	double angle_a = (Math::PI / 2.0f) - angle_b - angle_d;
	double angle_c = angle_b - angle_a;

	double v1 = v * abs(sin(angle_a));
	double v2 = v * abs(cos(angle_a));

	double v1x = v1 * abs(cos(angle_c));
	double v1y = v1 * abs(sin(angle_c));
	double v2x = v2 * abs(cos(angle_b));
	double v2y = v2 * abs(sin(angle_b));

	if(a->getVelocity().x > 0.0f) {
		if(a->x() < b->x()) {
			v1x = -v1x;
		}
		else {
			v2x = -v2x;
		}
	}
	else {
		if(a->x() > b->x()) {
			v2x = -v2x;
		}
		else {
			v1x = -v1x;
		}
	}

	if(a->getVelocity().y > 0.0f) {
		if(a->y() < b->y()) {
			v1y = -v1y;
		}
		else {
			v2y = -v2y;
		}
	}
	else {
		if(a->y() > b->y()) {
			v2y = -v2y;
		}
		else {
			v1y = -v1y;
		}
	}

// TODO: check for math errors
//	if(double.IsNaN(v1x) || double.IsNaN(v1y) || double.IsNaN(v2x) || double.IsNaN(v2y)) { return; }

	// update the asteroids with their new velocities
	a->setVelocity(v1x, v1y);
	b->setVelocity(v2x, v2y);
}

bool CollisionSystem::operator == (const CollisionSystem & c) const {
	return Entity::operator == (dynamic_cast<const Entity &>(c));
}

bool CollisionSystem::operator != (const CollisionSystem & c) const {
	return !operator == (c);
}

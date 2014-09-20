#ifndef PROJECTILE_SYSTEM_H
#define PROJECTILE_SYSTEM_H

#include <QVector.h>
#include "Sprite Animation System/SpriteAnimationCollection.h"
#include "Game Objects/Projectile.h"

class ProjectileSystem : public Entity {
public:
	ProjectileSystem();
	ProjectileSystem(const ProjectileSystem & p);
	ProjectileSystem & operator = (const ProjectileSystem & p);
	virtual ~ProjectileSystem();

	int numberOfProjectiles() const;
	bool hasProjectile(const Projectile * projectile) const;
	int indexOfProjectile(const Projectile * projectile) const;
	const Projectile * getProjectile(int index) const;
	bool addProjectile(Projectile * projectile);
	bool removeProjectile(int index);
	bool removeProjectile(const Projectile * projectile);
	void clearProjectiles();

	bool init(ResourceManager * resources, SpriteAnimationCollection * animations);

	void spawnLaserBeam(const Vector2 & position, float rotation, const SpaceShip * source);

	virtual void reset();
	virtual void update(unsigned int timeElapsed);
	virtual void draw();

	bool operator == (const ProjectileSystem & p) const;
	bool operator != (const ProjectileSystem & p) const;

private:
	bool m_initialized;

	const SpriteAnimation * m_laserAnimations[SpaceShipColours::NumberOfColours];
	
	Sound * m_laserSound;

	QVector<Projectile *> m_projectiles;
};

#endif // PROJECTILE_SYSTEM_H

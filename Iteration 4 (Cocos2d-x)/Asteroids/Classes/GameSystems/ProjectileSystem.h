#ifndef PROJECTILE_SYSTEM_H
#define PROJECTILE_SYSTEM_H

#include "SpriteAnimationSystem/SpriteAnimationCollection.h"
#include "GameObjects/Projectile.h"

class ProjectileSystem : public Entity, public Component {
public:
	ProjectileSystem(Layer * parent);
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

	virtual Layer * getParent() const;
	virtual void setParent(Layer * parent);

	bool init(SpriteAnimationCollection * animations);

	void spawnLaserBeam(const Vec2 & position, float rotation, const SpaceShip * source);

	virtual void reset();
	virtual void update(float timeElapsed);

	bool operator == (const ProjectileSystem & p) const;
	bool operator != (const ProjectileSystem & p) const;

public:
	static const char * projectileSystemClassName;

private:
	bool m_initialized;

	const SpriteAnimation * m_laserAnimations[SpaceShipColours::NumberOfColours];
	
//	Sound * m_laserSound;

	std::vector<Projectile *> m_projectiles;
};

#endif // PROJECTILE_SYSTEM_H

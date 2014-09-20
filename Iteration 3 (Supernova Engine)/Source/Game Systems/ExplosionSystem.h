#ifndef EXPLOSION_SYSTEM_H
#define EXPLOSION_SYSTEM_H

#include <QVector.h>
#include "Sprite Animation System/SpriteAnimationCollection.h"
#include "Game Objects/Explosion.h"

class ExplosionSystem : public Entity {
public:
	ExplosionSystem();
	ExplosionSystem(const ExplosionSystem & e);
	ExplosionSystem & operator = (const ExplosionSystem & e);
	virtual ~ExplosionSystem();

	int numberOfExplosions() const;
	bool hasExplosion(const Explosion * explosion) const;
	int indexOfExplosion(const Explosion * explosion) const;
	const Explosion * getExplosion(int index) const;
	bool addExplosion(Explosion * explosion);
	bool removeExplosion(int index);
	bool removeExplosion(const Explosion * explosion);
	void clearExplosions();

	bool init(SpriteAnimationCollection * animations, ResourceManager * resourceManager);

	void spawnExplosion(const Vector2 & position, const Vector2 & velocity);

	virtual void reset();
	virtual void update(unsigned int timeElapsed);
	virtual void draw();

	bool operator == (const ExplosionSystem & e) const;
	bool operator != (const ExplosionSystem & e) const;

private:
	bool m_initialized;

	const SpriteAnimation * m_explosionAnimation;
	
	Sound * m_explosionSound;

	QVector<Explosion *> m_explosions;
};

#endif // EXPLOSION_SYSTEM_H

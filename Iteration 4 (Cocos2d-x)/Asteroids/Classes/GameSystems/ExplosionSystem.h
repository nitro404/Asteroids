#ifndef EXPLOSION_SYSTEM_H
#define EXPLOSION_SYSTEM_H

#include "SpriteAnimationSystem/SpriteAnimationCollection.h"
#include "GameObjects/Explosion.h"

class ExplosionSystem : public Entity, public Component {
public:
	ExplosionSystem(Layer * parent);
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

	virtual Layer * getParent() const;
	virtual void setParent(Layer * parent);

	bool init(SpriteAnimationCollection * animations);

	void spawnExplosion(const Vec2 & position, const Vec2 & velocity);

	virtual void reset();
	virtual void update(float timeElapsed);

	bool operator == (const ExplosionSystem & e) const;
	bool operator != (const ExplosionSystem & e) const;

public:
	static const char * explosionSystemClassName;

private:
	bool m_initialized;

	const SpriteAnimation * m_explosionAnimation;
	
//	Sound * m_explosionSound;

	std::vector<Explosion *> m_explosions;
};

#endif // EXPLOSION_SYSTEM_H

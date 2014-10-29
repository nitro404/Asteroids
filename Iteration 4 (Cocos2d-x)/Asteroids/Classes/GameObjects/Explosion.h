#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "SpriteAnimationSystem/SpriteAnimation.h"
#include "Entity/AnimatedEntity2D.h"

class Explosion : public AnimatedEntity2D {
public:
	Explosion(Layer * parentLayer, const SpriteAnimation * animation, const Vec2 & position = Vec2::ZERO, const Vec2 & velocity = Vec2::ZERO);
	Explosion(const Explosion & e);
	Explosion & operator = (const Explosion & e);
	virtual ~Explosion();

	bool isFinished() const;

	bool operator == (const Explosion & e) const;
	bool operator != (const Explosion & e) const;
};

#endif // EXPLOSION_H

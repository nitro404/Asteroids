#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Sprite Animation System/SpriteAnimation.h"
#include "Entity/AnimatedEntity2D.h"

class Explosion : public AnimatedEntity2D {
public:
	Explosion(const SpriteAnimation * animation, const Vector2 & position = Vector2::Zero, const Vector2 & velocity = Vector2::Zero);
	Explosion(const Explosion & e);
	Explosion & operator = (const Explosion & e);
	virtual ~Explosion();

	bool isFinished() const;

	bool operator == (const Explosion & e) const;
	bool operator != (const Explosion & e) const;
};

#endif // EXPLOSION_H

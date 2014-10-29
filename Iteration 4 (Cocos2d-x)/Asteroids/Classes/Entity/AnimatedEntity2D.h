#ifndef ANIMATED_ENTITY_2D_H
#define ANIMATED_ENTITY_2D_H

#include "Entity/Entity2D.h"
#include "SpriteAnimationSystem/SpriteAnimation.h"

class AnimatedEntity2D : public Entity2D {
public:
	AnimatedEntity2D(Layer * parentLayer, const SpriteAnimation * spriteAnimation = NULL, const Vec2 & position = Vec2::ZERO, float size = 0.0f, const Vec2 & scale = Vec2::ONE, float rotation = 0.0f, const Vec2 & offset = Vec2::ZERO, const Vec2 & velocity = Vec2::ZERO);
	AnimatedEntity2D(const AnimatedEntity2D & e);
	AnimatedEntity2D & operator = (const AnimatedEntity2D & e);
	virtual ~AnimatedEntity2D();

	const SpriteAnimation * getSpriteAnimation() const;
	bool setSpriteAnimation(const SpriteAnimation * animation);

	virtual void reset();
	virtual void update(float timeElapsed);

	bool operator == (const AnimatedEntity2D & e) const;
	bool operator != (const AnimatedEntity2D & e) const;

protected:
	SpriteAnimation * m_spriteAnimation;
};

#endif // ANIMATED_ENTITY_2D_H

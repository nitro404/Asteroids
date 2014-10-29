#include "Entity/AnimatedEntity2D.h"

AnimatedEntity2D::AnimatedEntity2D(Layer * parentLayer, const SpriteAnimation * spriteAnimation, const Vec2 & position, float size, const Vec2 & scale, float rotation, const Vec2 & offset, const Vec2 & velocity)
	: Entity2D(parentLayer, NULL, position, size, scale, rotation, offset, velocity)
	, m_spriteAnimation(spriteAnimation == NULL ? NULL : new SpriteAnimation(*spriteAnimation)) {
	if(m_spriteAnimation != NULL) {
		setSprite(m_spriteAnimation->getSprite());
		m_spriteAnimation->play();
	}
}

AnimatedEntity2D::AnimatedEntity2D(const AnimatedEntity2D & e)
	: Entity2D(e)
	, m_spriteAnimation(e.m_spriteAnimation == NULL ? NULL : new SpriteAnimation(*e.m_spriteAnimation)) {
	if(m_spriteAnimation != NULL) {
		setSprite(m_spriteAnimation->getSprite());
		m_spriteAnimation->play();
	}
}
AnimatedEntity2D & AnimatedEntity2D::operator = (const AnimatedEntity2D & e) {
	Entity::operator = (e);

	if(m_spriteAnimation != NULL) {
		m_spriteAnimation->stop();

		delete m_spriteAnimation;
		m_spriteAnimation = NULL;
	}
	
	if(e.m_spriteAnimation != NULL) {
		m_spriteAnimation = new SpriteAnimation(*e.m_spriteAnimation);
		setSprite(m_spriteAnimation->getSprite());
		m_spriteAnimation->play();
	}

	return *this;
}

AnimatedEntity2D::~AnimatedEntity2D() {
	if(m_spriteAnimation != NULL) { delete m_spriteAnimation; }
}

const SpriteAnimation * AnimatedEntity2D::getSpriteAnimation() const {
	return m_spriteAnimation;
}

bool AnimatedEntity2D::setSpriteAnimation(const SpriteAnimation * animation) {
	if(animation == NULL) { return false; }

	if(m_spriteAnimation != NULL) {
		m_spriteAnimation->stop();
		delete m_spriteAnimation;
	}

	m_spriteAnimation = new SpriteAnimation(*animation);
	setSprite(m_spriteAnimation->getSprite());
	m_spriteAnimation->play();

	return true;
}

void AnimatedEntity2D::reset() {
	Entity2D::reset();

	if(m_spriteAnimation != NULL) {
		m_spriteAnimation->stop();
	}
}

void AnimatedEntity2D::update(float timeElapsed) {
	Entity2D::update(timeElapsed);

	if(m_spriteAnimation != NULL) {
		m_spriteAnimation->update(timeElapsed);
	}
}

bool AnimatedEntity2D::operator == (const AnimatedEntity2D & e) const {
	return Entity::operator == (dynamic_cast<const Entity &>(e));
}

bool AnimatedEntity2D::operator != (const AnimatedEntity2D & e) const {
	return !operator == (e);
}

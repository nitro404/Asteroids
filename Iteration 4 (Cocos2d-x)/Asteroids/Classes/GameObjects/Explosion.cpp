#include "GameObjects/Explosion.h"

Explosion::Explosion(Layer * parentLayer, const SpriteAnimation * animation, const Vec2 & position, const Vec2 & velocity)
	: AnimatedEntity2D(parentLayer, animation, position, 0.0f, Vec2::ONE, 0.0f, Vec2::ZERO, velocity)  {
	
}

Explosion::Explosion(const Explosion & e)
	: AnimatedEntity2D(e) {
	
}

Explosion & Explosion::operator = (const Explosion & e) {
	AnimatedEntity2D::operator = (e);

	return *this;
}

Explosion::~Explosion() {

}

bool Explosion::isFinished() const {
	return m_spriteAnimation == NULL ? true : m_spriteAnimation->isFinished();
}

bool Explosion::operator == (const Explosion & e) const {
	return AnimatedEntity2D::operator == (e);
}

bool Explosion::operator != (const Explosion & e) const {
	return !operator == (e);
}

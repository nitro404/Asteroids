#include "Game Objects/Explosion.h"

Explosion::Explosion(const SpriteAnimation * animation, const Vector2 & position, const Vector2 & velocity)
	: AnimatedEntity2D(animation, position, 0.0f, Vector2::One, 0.0f, Vector2::Zero, velocity)  {
	
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
	return m_spriteAnimation->isFinished();
}

bool Explosion::operator == (const Explosion & e) const {
	return AnimatedEntity2D::operator == (e);
}

bool Explosion::operator != (const Explosion & e) const {
	return !operator == (e);
}

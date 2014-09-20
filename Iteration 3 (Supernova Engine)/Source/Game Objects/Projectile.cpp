#include "Game Objects/Projectile.h"
#include "Game Objects/SpaceShip.h"

const float Projectile::projectileSize = 4.0f;
const float Projectile::projectileSpeed = 9.0f * 60.0f;

Projectile::Projectile(const SpriteAnimation * animation, const SpaceShip * projectileSource, const Vector2 & position, float rotation)
	: AnimatedEntity2D(animation, position, projectileSize, Vector2::One, rotation, Vector2::Zero, Vector2::Zero)
	, m_projectileSource(projectileSource) {
	updateVelocity();
}

Projectile::Projectile(const Projectile & p)
	: AnimatedEntity2D(p)
	, m_projectileSource(p.m_projectileSource) {
	
}

Projectile & Projectile::operator = (const Projectile & p) {
	AnimatedEntity2D::operator = (p);

	m_projectileSource = p.m_projectileSource;

	return *this;
}

Projectile::~Projectile() {

}

void Projectile::setRotation(float rotation) {
	AnimatedEntity2D::setRotation(rotation);

	updateVelocity();
}

const SpaceShip * Projectile::getProjectileSource() const {
	return m_projectileSource;
}

void Projectile::updateVelocity() {
	m_velocity.x = cos(Math::degreesToRadians(m_rotation - 90.0f));
	m_velocity.y = sin(Math::degreesToRadians(m_rotation - 90.0f));

	m_velocity = m_velocity.normalized() * projectileSpeed;
}

bool Projectile::operator == (const Projectile & p) const {
	return AnimatedEntity2D::operator == (p) &&
		   *m_projectileSource == *p.m_projectileSource;
}

bool Projectile::operator != (const Projectile & p) const {
	return !operator == (p);
}

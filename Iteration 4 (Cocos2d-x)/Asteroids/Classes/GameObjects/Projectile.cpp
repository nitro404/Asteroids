#include "GameObjects/Projectile.h"
#include "GameObjects/SpaceShip.h"

const float Projectile::projectileSize = 4.0f;
const float Projectile::projectileSpeed = 540.0f;

Projectile::Projectile(Layer * parentLayer, const SpriteAnimation * animation, const SpaceShip * projectileSource, const Vec2 & position, float rotation)
	: AnimatedEntity2D(parentLayer, animation, position, projectileSize, Vec2::ONE, rotation, Vec2::ZERO, Vec2::ZERO)
	, m_projectileSource(projectileSource) {
	updateVelocity();
}

Projectile::Projectile(const Projectile & p)
	: AnimatedEntity2D(p)
	, m_projectileSource(p.m_projectileSource) {
	updateVelocity();
}

Projectile & Projectile::operator = (const Projectile & p) {
	AnimatedEntity2D::operator = (p);

	m_projectileSource = p.m_projectileSource;

	updateVelocity();

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

	m_velocity = m_velocity.getNormalized() * projectileSpeed;
}

bool Projectile::operator == (const Projectile & p) const {
	return AnimatedEntity2D::operator == (p) &&
		   *m_projectileSource == *p.m_projectileSource;
}

bool Projectile::operator != (const Projectile & p) const {
	return !operator == (p);
}

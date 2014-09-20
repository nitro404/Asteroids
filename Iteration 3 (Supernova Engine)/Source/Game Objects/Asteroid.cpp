#include "Game Objects/Asteroid.h"

const float Asteroid::minRotationSpeed = 0.3153f;
const float Asteroid::maxRotationSpeed = 0.4584f + 15.0f;
const float Asteroid::minVelocity = 0.08f * 30.0f;
const float Asteroid::maxVelocity = 3.3f * 30.0f;

Asteroid::Asteroid(const Sprite * sprite, bool largeAsteroid, const Vector2 & position, float size, const Vector2 & scale, float rotation, RotationDirections::RotationDirection rotationDirection, float rotationSpeed, const Vector2 & offset, const Vector2 & velocity)
	: Entity2D(sprite, position, size, scale, rotation, offset, velocity)
	, m_largeAsteroid(largeAsteroid)
	, m_rotationDirection(RotationDirections::isValid(rotationDirection) ? rotationDirection : RotationDirections::defaultRotationDirection)
	, m_rotationSpeed(rotationSpeed < 0 ? -rotationSpeed : rotationSpeed) {
	
}

Asteroid::Asteroid(const Asteroid & a)
	: Entity2D(a)
	, m_largeAsteroid(a.m_largeAsteroid)
	, m_rotationDirection(a.m_rotationDirection)
	, m_rotationSpeed(a.m_rotationSpeed) {
	
}

Asteroid & Asteroid::operator = (const Asteroid & a) {
	Entity2D::operator = (a);

	m_largeAsteroid = a.m_largeAsteroid;
	m_rotationDirection = a.m_rotationDirection;
	m_rotationSpeed = a.m_rotationSpeed;

	return *this;
}

Asteroid::~Asteroid() {

}

bool Asteroid::isLargeAsteroid() const {
	return m_largeAsteroid;
}

RotationDirections::RotationDirection Asteroid::getRotationDirection() const {
	return m_rotationDirection;
}

float Asteroid::getRotationSpeed() const {
	return m_rotationSpeed;
}

int Asteroid::numberOfCollisions() const {
	return m_collisions.size();
}

bool Asteroid::hasCollision(const Asteroid * asteroid) const {
	if(asteroid == NULL) { return false; }

	for(int i=0;i<m_collisions.size();i++) {
		if(*m_collisions[i] == *asteroid) {
			return true;
		}
	}
	return false;
}

int Asteroid::indexOfCollision(const Asteroid * asteroid) const {
	if(asteroid == NULL) { return -1; }

	for(int i=0;i<m_collisions.size();i++) {
		if(*m_collisions[i] == *asteroid) {
			return i;
		}
	}
	return -1;
}

const Asteroid * Asteroid::getCollision(int index) const {
	if(index < 0 || index >= m_collisions.size()) { return NULL; }

	return m_collisions[index];
}

bool Asteroid::addCollision(const Asteroid * asteroid) {
	if(asteroid == NULL) { return false; }

	for(int i=0;i<m_collisions.size();i++) {
		if(*m_collisions[i] == *asteroid) {
			return false;
		}
	}

	m_collisions.push_back(asteroid);

	return true;
}

bool Asteroid::removeCollision(int index) {
	if(index < 0 || index >= m_collisions.size()) { return false; }

	int lastIndex = m_collisions.size() - 1;
	m_collisions[index] = m_collisions[lastIndex];
	m_collisions.remove(lastIndex);
	
	return true;
}

bool Asteroid::removeCollision(const Asteroid * asteroid) {
	if(asteroid == NULL) { return false; }

	for(int i=0;i<m_collisions.size();i++) {
		if(*m_collisions[i] == *asteroid) {
			int lastIndex = m_collisions.size() - 1;
			m_collisions[i] = m_collisions[lastIndex];
			m_collisions.remove(lastIndex);

			return true;
		}
	}
	return false;
}

void Asteroid::clearCollisions() {
	m_collisions.clear();
}

void Asteroid::update(unsigned int timeElapsed) {
	Entity2D::update(timeElapsed);

	m_rotation += (m_rotationDirection == RotationDirections::Clockwise ? -1 : 1) * m_rotationSpeed * (timeElapsed / 1000.0f);

	if(m_position.x > SettingsManager::getInstance()->windowWidth + m_size) {
		m_position.x -= SettingsManager::getInstance()->windowWidth + m_size;
	}
	else if(m_position.x < -m_size) {
		m_position.x += SettingsManager::getInstance()->windowWidth + m_size;
	}

	if(m_position.y > SettingsManager::getInstance()->windowHeight + m_size) {
		m_position.y -= SettingsManager::getInstance()->windowHeight + m_size;
	}
	else if(m_position.y < -m_size) {
		m_position.y += SettingsManager::getInstance()->windowHeight + m_size;
	}
}

bool Asteroid::operator == (const Asteroid & a) const {
	return Entity2D::operator == (a);
}

bool Asteroid::operator != (const Asteroid & a) const {
	return !operator == (a);
}

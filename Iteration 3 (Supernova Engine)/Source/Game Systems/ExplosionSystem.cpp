#include "Game Systems/ExplosionSystem.h"

ExplosionSystem::ExplosionSystem()
	: Entity()
	, m_initialized(false)
	, m_explosionAnimation(NULL)
	, m_explosionSound(NULL) {
	
}

ExplosionSystem::ExplosionSystem(const ExplosionSystem & e)
	: Entity(e)
	, m_initialized(e.m_initialized)
	, m_explosionAnimation(e.m_explosionAnimation)
	, m_explosionSound(e.m_explosionSound) {
	for(int i=0;i<e.m_explosions.size();i++) {
		m_explosions.push_back(new Explosion(*e.m_explosions[i]));
	}
}

ExplosionSystem & ExplosionSystem::operator = (const ExplosionSystem & e) {
	Entity::operator = (e);

	for(int i=0;i<m_explosions.size();i++) {
		delete m_explosions[i];
	}
	m_explosions.clear();

	m_initialized = e.m_initialized;
	
	m_explosionAnimation = e.m_explosionAnimation;
	m_explosionSound = e.m_explosionSound;

	for(int i=0;i<e.m_explosions.size();i++) {
		m_explosions.push_back(new Explosion(*e.m_explosions[i]));
	}

	return *this;
}

ExplosionSystem::~ExplosionSystem() {
	for(int i=0;i<m_explosions.size();i++) {
		delete m_explosions[i];
	}
}

int ExplosionSystem::numberOfExplosions() const {
	return m_explosions.size();
}

bool ExplosionSystem::hasExplosion(const Explosion * explosion) const {
	if(explosion == NULL) { return false; }

	for(int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			return true;
		}
	}
	return false;
}

int ExplosionSystem::indexOfExplosion(const Explosion * explosion) const {
	if(explosion == NULL) { return -1; }

	for(int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			return i;
		}
	}
	return -1;
}

const Explosion * ExplosionSystem::getExplosion(int index) const {
	if(index < 0 || index >= m_explosions.size()) { return NULL; }

	return m_explosions[index];
}

bool ExplosionSystem::addExplosion(Explosion * explosion) {
	if(explosion == NULL) { return false; }

	for(int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			return false;
		}
	}

	m_explosions.push_back(explosion);

	return true;
}

bool ExplosionSystem::removeExplosion(int index) {
	if(index < 0 || index >= m_explosions.size()) { return false; }

	int lastIndex = m_explosions.size() - 1;
	delete m_explosions[index];
	m_explosions[index] = m_explosions[lastIndex];
	m_explosions.remove(lastIndex);
	
	return true;
}

bool ExplosionSystem::removeExplosion(const Explosion * explosion) {
	if(explosion == NULL) { return false; }

	for(int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			int lastIndex = m_explosions.size() - 1;
			delete m_explosions[i];
			m_explosions[i] = m_explosions[lastIndex];
			m_explosions.remove(lastIndex);

			return true;
		}
	}
	return false;
}

void ExplosionSystem::clearExplosions() {
	for(int i=0;i<m_explosions.size();i++) {
		delete m_explosions[i];
	}
	m_explosions.clear();
}

bool ExplosionSystem::init(SpriteAnimationCollection * animations, ResourceManager * resourceManager) {
	if(m_initialized) { return true; }

	if(animations == NULL || animations->numberOfAnimations() == 0) { return false; }

	const SpriteAnimation * animation = NULL;

	animation = animations->getAnimation("Explosion");
	if(animation == NULL) { return false; }

	m_explosionAnimation = animation;

	if(resourceManager != NULL) {
		m_explosionSound = resourceManager->getSound("Explosion");
	}

	m_initialized = true;

	return true;
}

void ExplosionSystem::spawnExplosion(const Vector2 & position, const Vector2 & velocity) {
	if(!m_initialized) { return; }

	m_explosions.push_back(new Explosion(m_explosionAnimation, position, velocity));

	if(m_explosionSound != NULL) {
		m_explosionSound->play();
	}
}

void ExplosionSystem::reset() {
	if(!m_initialized) { return; }

	clearExplosions();
}

void ExplosionSystem::update(unsigned int timeElapsed) {
	if(!m_initialized) { return; }

	for(int i=0;i<m_explosions.size();i++) {
		m_explosions[i]->update(timeElapsed);
		
		if(m_explosions[i]->isFinished() || m_explosions[i]->outOfBounds()) {
			int lastIndex = m_explosions.size() - 1;
			delete m_explosions[i];
			m_explosions[i] = m_explosions[lastIndex];
			m_explosions.remove(lastIndex);
			i--;
		}
	}
}

void ExplosionSystem::draw() {
	if(!m_initialized) { return; }

	for(int i=0;i<m_explosions.size();i++) {
		m_explosions[i]->draw();
	}
}

bool ExplosionSystem::operator == (const ExplosionSystem & e) const {
	return Entity::operator == (dynamic_cast<const Entity &>(e));
}

bool ExplosionSystem::operator != (const ExplosionSystem & e) const {
	return !operator == (e);
}

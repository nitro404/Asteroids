#include "GameSystems/ExplosionSystem.h"

const char * ExplosionSystem::explosionSystemClassName = "ExplosionSystem";

ExplosionSystem::ExplosionSystem(Layer * parentLayer)
	: Entity(parentLayer)
	, m_initialized(false)
	, m_explosionAnimation(NULL) {
//	, m_explosionSound(NULL) {
	setName(explosionSystemClassName);

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

ExplosionSystem::ExplosionSystem(const ExplosionSystem & e)
	: Entity(e)
	, m_initialized(e.m_initialized)
	, m_explosionAnimation(e.m_explosionAnimation) {
//	, m_explosionSound(e.m_explosionSound) {
	setName(explosionSystemClassName);

	for(unsigned int i=0;i<e.m_explosions.size();i++) {
		m_explosions.push_back(new Explosion(*e.m_explosions[i]));
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

ExplosionSystem & ExplosionSystem::operator = (const ExplosionSystem & e) {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(explosionSystemClassName); }

	Entity::operator = (e);

	for(unsigned int i=0;i<m_explosions.size();i++) {
		delete m_explosions[i];
	}
	m_explosions.clear();

	m_initialized = e.m_initialized;
	
	m_explosionAnimation = e.m_explosionAnimation;
//	m_explosionSound = e.m_explosionSound;

	for(unsigned int i=0;i<e.m_explosions.size();i++) {
		m_explosions.push_back(new Explosion(*e.m_explosions[i]));
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }

	return *this;
}

ExplosionSystem::~ExplosionSystem() {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(explosionSystemClassName); }

	for(unsigned int i=0;i<m_explosions.size();i++) {
		delete m_explosions[i];
	}
}

int ExplosionSystem::numberOfExplosions() const {
	return static_cast<int>(m_explosions.size());
}

bool ExplosionSystem::hasExplosion(const Explosion * explosion) const {
	if(explosion == NULL) { return false; }

	for(unsigned int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			return true;
		}
	}
	return false;
}

int ExplosionSystem::indexOfExplosion(const Explosion * explosion) const {
	if(explosion == NULL) { return -1; }

	for(unsigned int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			return i;
		}
	}
	return -1;
}

const Explosion * ExplosionSystem::getExplosion(int index) const {
	if(index < 0 || index >= static_cast<int>(m_explosions.size())) { return NULL; }

	return m_explosions[index];
}

bool ExplosionSystem::addExplosion(Explosion * explosion) {
	if(explosion == NULL) { return false; }

	for(unsigned int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			return false;
		}
	}

	m_explosions.push_back(explosion);

	return true;
}

bool ExplosionSystem::removeExplosion(int index) {
	if(index < 0 || index >= static_cast<int>(m_explosions.size())) { return false; }

	int lastIndex = m_explosions.size() - 1;
	delete m_explosions[index];
	m_explosions[index] = m_explosions[lastIndex];
	m_explosions.erase(m_explosions.begin() + lastIndex);
	
	return true;
}

bool ExplosionSystem::removeExplosion(const Explosion * explosion) {
	if(explosion == NULL) { return false; }

	for(unsigned int i=0;i<m_explosions.size();i++) {
		if(*m_explosions[i] == *explosion) {
			int lastIndex = static_cast<int>(m_explosions.size()) - 1;
			delete m_explosions[i];
			m_explosions[i] = m_explosions[lastIndex];
			m_explosions.erase(m_explosions.begin() + lastIndex);

			return true;
		}
	}
	return false;
}

void ExplosionSystem::clearExplosions() {
	for(unsigned int i=0;i<m_explosions.size();i++) {
		delete m_explosions[i];
	}
	m_explosions.clear();
}

Layer * ExplosionSystem::getParentLayer() const {
	return Entity::getParentLayer();
}

void ExplosionSystem::setParentLayer(Layer * parent) {
	if(m_parentLayer == parent) { return; }

	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(explosionSystemClassName); }

	Entity::setParentLayer(parent);

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

bool ExplosionSystem::init(SpriteAnimationCollection * animations) {
	if(m_initialized) { return true; }

	if(animations == NULL || animations->numberOfAnimations() == 0) { return false; }

	const SpriteAnimation * animation = NULL;

	animation = animations->getAnimation("Explosion");
	if(animation == NULL) { return false; }

	m_explosionAnimation = animation;

/*
	if(resourceManager != NULL) {
		m_explosionSound = resourceManager->getSound("Explosion");
	}
*/

	m_initialized = true;

	return true;
}

void ExplosionSystem::spawnExplosion(const Vec2 & position, const Vec2 & velocity) {
	if(!m_initialized) { return; }

	m_explosions.push_back(new Explosion(m_parentLayer, m_explosionAnimation, position, velocity));

/*
	if(m_explosionSound != NULL) {
		m_explosionSound->play();
	}
*/
}

void ExplosionSystem::reset() {
	if(!m_initialized) { return; }

	clearExplosions();
}

void ExplosionSystem::update(float timeElapsed) {
	if(!m_initialized) { return; }

	for(unsigned int i=0;i<m_explosions.size();i++) {
		m_explosions[i]->update(timeElapsed);
		
		if(m_explosions[i]->isFinished() || m_explosions[i]->outOfBounds()) {
			int lastIndex = static_cast<int>(m_explosions.size()) - 1;
			delete m_explosions[i];
			m_explosions[i] = m_explosions[lastIndex];
			m_explosions.erase(m_explosions.begin() + lastIndex);
			i--;
		}
	}
}

bool ExplosionSystem::operator == (const ExplosionSystem & e) const {
	return Entity::operator == (dynamic_cast<const Entity &>(e));
}

bool ExplosionSystem::operator != (const ExplosionSystem & e) const {
	return !operator == (e);
}

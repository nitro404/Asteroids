#include "GameObjects/SpaceShip.h"
#include "GameSystems/ProjectileSystem.h"

const char * ProjectileSystem::projectileSystemClassName = "ProjectileSystem";

ProjectileSystem::ProjectileSystem(Layer * parentLayer)
	: Entity(parentLayer)
	, m_initialized(false) {
//	, m_laserSound(NULL) {
	setName(projectileSystemClassName);

	for(unsigned int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_laserAnimations[i] = NULL;
	}
	
	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
	
}

ProjectileSystem::ProjectileSystem(const ProjectileSystem & p)
	: Entity(p)
	, m_initialized(p.m_initialized) {
//	, m_laserSound(p.m_laserSound) {
	setName(projectileSystemClassName);

	for(unsigned int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_laserAnimations[i] = p.m_laserAnimations[i];
	}

	for(unsigned int i=0;i<p.m_projectiles.size();i++) {
		m_projectiles.push_back(new Projectile(*p.m_projectiles[i]));
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

ProjectileSystem & ProjectileSystem::operator = (const ProjectileSystem & p) {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(projectileSystemClassName); }

	Entity::operator = (p);

	for(unsigned int i=0;i<m_projectiles.size();i++) {
		delete m_projectiles[i];
	}
	m_projectiles.clear();

	m_initialized = p.m_initialized;

	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_laserAnimations[i] = p.m_laserAnimations[i];
	}
	
//	m_laserSound = p.m_laserSound;

	for(unsigned int i=0;i<p.m_projectiles.size();i++) {
		m_projectiles.push_back(new Projectile(*p.m_projectiles[i]));
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }

	return *this;
}

ProjectileSystem::~ProjectileSystem() {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(projectileSystemClassName); }

	for(unsigned int i=0;i<m_projectiles.size();i++) {
		delete m_projectiles[i];
	}
}

int ProjectileSystem::numberOfProjectiles() const {
	return static_cast<int>(m_projectiles.size());
}

bool ProjectileSystem::hasProjectile(const Projectile * projectile) const {
	if(projectile == NULL) { return false; }

	for(unsigned int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			return true;
		}
	}
	return false;
}

int ProjectileSystem::indexOfProjectile(const Projectile * projectile) const {
	if(projectile == NULL) { return -1; }

	for(unsigned int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			return i;
		}
	}
	return -1;
}

const Projectile * ProjectileSystem::getProjectile(int index) const {
	if(index < 0 || index >= static_cast<int>(m_projectiles.size())) { return NULL; }

	return m_projectiles[index];
}

bool ProjectileSystem::addProjectile(Projectile * projectile) {
	if(projectile == NULL) { return false; }

	for(unsigned int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			return false;
		}
	}

	m_projectiles.push_back(projectile);

	return true;
}

bool ProjectileSystem::removeProjectile(int index) {
	if(index < 0 || index >= static_cast<int>(m_projectiles.size())) { return false; }

	int lastIndex = m_projectiles.size() - 1;
	delete m_projectiles[index];
	m_projectiles[index] = m_projectiles[lastIndex];
	m_projectiles.erase(m_projectiles.begin() + lastIndex);
	
	return true;
}

bool ProjectileSystem::removeProjectile(const Projectile * projectile) {
	if(projectile == NULL) { return false; }

	for(unsigned int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			int lastIndex = m_projectiles.size() - 1;
			delete m_projectiles[i];
			m_projectiles[i] = m_projectiles[lastIndex];
			m_projectiles.erase(m_projectiles.begin() + lastIndex);

			return true;
		}
	}
	return false;
}

void ProjectileSystem::clearProjectiles() {
	for(unsigned int i=0;i<m_projectiles.size();i++) {
		delete m_projectiles[i];
	}
	m_projectiles.clear();
}

Layer * ProjectileSystem::getParentLayer() const {
	return Entity::getParentLayer();
}

void ProjectileSystem::setParentLayer(Layer * parentLayer) {
	if(m_parentLayer == parentLayer) { return; }

	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(projectileSystemClassName); }

	Entity::setParentLayer(parentLayer);

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

bool ProjectileSystem::init(SpriteAnimationCollection * animations) {
	if(m_initialized) { return true; }

	if(animations == NULL || animations->numberOfAnimations() == 0) { return false; }

	std::string animationName;

	const SpriteAnimation * animation = NULL;

	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		animationName = std::string(SpaceShipColours::toString(i)).append(" Laser");

		animation = animations->getAnimation(animationName);
		if(animation == NULL) { return false; }

		m_laserAnimations[i] = animation;
	}

/*
	if(resourceManager != NULL) {
		m_laserSound = resourceManager->getSound("Laser");
	}
*/

	m_initialized = true;

	return true;
}

void ProjectileSystem::spawnLaserBeam(const Vec2 & position, float rotation, const SpaceShip * source) {
	if(!m_initialized || source == NULL) { return; }

	m_projectiles.push_back(new Projectile(m_parentLayer, m_laserAnimations[static_cast<int>(source->getColour())], source, position, rotation));

/*
	if(m_laserSound != NULL) {
		m_laserSound->play();
	}
*/
}


void ProjectileSystem::reset() {
	if(!m_initialized) { return; }

	clearProjectiles();
}

void ProjectileSystem::update(float timeElapsed) {
	if(!m_initialized) { return; }

	for(unsigned int i=0;i<m_projectiles.size();i++) {
		m_projectiles[i]->update(timeElapsed);
		
		if(m_projectiles[i]->outOfBounds()) {
			int lastIndex = m_projectiles.size() - 1;
			delete m_projectiles[i];
			m_projectiles[i] = m_projectiles[lastIndex];
			m_projectiles.erase(m_projectiles.begin() + lastIndex);
			i--;
		}
	}
}

bool ProjectileSystem::operator == (const ProjectileSystem & p) const {
	return Entity::operator == (dynamic_cast<const Entity &>(p));
}

bool ProjectileSystem::operator != (const ProjectileSystem & p) const {
	return !operator == (p);
}

#include "Game Objects/SpaceShip.h"
#include "Game Systems/ProjectileSystem.h"

ProjectileSystem::ProjectileSystem()
	: Entity()
	, m_initialized(false)
	, m_laserSound(NULL) {
	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_laserAnimations[i] = NULL;
	}
}

ProjectileSystem::ProjectileSystem(const ProjectileSystem & p)
	: Entity(p)
	, m_initialized(p.m_initialized)
	, m_laserSound(p.m_laserSound) {
	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_laserAnimations[i] = p.m_laserAnimations[i];
	}

	for(int i=0;i<p.m_projectiles.size();i++) {
		m_projectiles.push_back(new Projectile(*p.m_projectiles[i]));
	}
}

ProjectileSystem & ProjectileSystem::operator = (const ProjectileSystem & p) {
	Entity::operator = (p);

	for(int i=0;i<m_projectiles.size();i++) {
		delete m_projectiles[i];
	}
	m_projectiles.clear();

	m_initialized = p.m_initialized;

	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_laserAnimations[i] = p.m_laserAnimations[i];
	}
	
	m_laserSound = p.m_laserSound;

	for(int i=0;i<p.m_projectiles.size();i++) {
		m_projectiles.push_back(new Projectile(*p.m_projectiles[i]));
	}

	return *this;
}

ProjectileSystem::~ProjectileSystem() {
	for(int i=0;i<m_projectiles.size();i++) {
		delete m_projectiles[i];
	}
}

int ProjectileSystem::numberOfProjectiles() const {
	return m_projectiles.size();
}

bool ProjectileSystem::hasProjectile(const Projectile * projectile) const {
	if(projectile == NULL) { return false; }

	for(int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			return true;
		}
	}
	return false;
}

int ProjectileSystem::indexOfProjectile(const Projectile * projectile) const {
	if(projectile == NULL) { return -1; }

	for(int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			return i;
		}
	}
	return -1;
}

const Projectile * ProjectileSystem::getProjectile(int index) const {
	if(index < 0 || index >= m_projectiles.size()) { return NULL; }

	return m_projectiles[index];
}

bool ProjectileSystem::addProjectile(Projectile * projectile) {
	if(projectile == NULL) { return false; }

	for(int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			return false;
		}
	}

	m_projectiles.push_back(projectile);

	return true;
}

bool ProjectileSystem::removeProjectile(int index) {
	if(index < 0 || index >= m_projectiles.size()) { return false; }

	int lastIndex = m_projectiles.size() - 1;
	delete m_projectiles[index];
	m_projectiles[index] = m_projectiles[lastIndex];
	m_projectiles.remove(lastIndex);
	
	return true;
}

bool ProjectileSystem::removeProjectile(const Projectile * projectile) {
	if(projectile == NULL) { return false; }

	for(int i=0;i<m_projectiles.size();i++) {
		if(*m_projectiles[i] == *projectile) {
			int lastIndex = m_projectiles.size() - 1;
			delete m_projectiles[i];
			m_projectiles[i] = m_projectiles[lastIndex];
			m_projectiles.remove(lastIndex);

			return true;
		}
	}
	return false;
}

void ProjectileSystem::clearProjectiles() {
	for(int i=0;i<m_projectiles.size();i++) {
		delete m_projectiles[i];
	}
	m_projectiles.clear();
}

bool ProjectileSystem::init(ResourceManager * resourceManager, SpriteAnimationCollection * animations) {
	if(m_initialized) { return true; }

	if(animations == NULL || animations->numberOfAnimations() == 0) { return false; }

	QString animationName;

	const SpriteAnimation * animation = NULL;

	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		animationName = QString(SpaceShipColours::toString(i)).append(" Laser");

		animation = animations->getAnimation(animationName);
		if(animation == NULL) { return false; }

		m_laserAnimations[i] = animation;
	}

	if(resourceManager != NULL) {
		m_laserSound = resourceManager->getSound("Laser");
	}

	m_initialized = true;

	return true;
}

void ProjectileSystem::spawnLaserBeam(const Vector2 & position, float rotation, const SpaceShip * source) {
	if(!m_initialized || source == NULL) { return; }

	m_projectiles.push_back(new Projectile(m_laserAnimations[static_cast<int>(source->getColour())], source, position, rotation));

	if(m_laserSound != NULL) {
		m_laserSound->play();
	}
}

void ProjectileSystem::reset() {
	if(!m_initialized) { return; }

	clearProjectiles();
}

void ProjectileSystem::update(unsigned int timeElapsed) {
	if(!m_initialized) { return; }

	for(int i=0;i<m_projectiles.size();i++) {
		m_projectiles[i]->update(timeElapsed);
		
		if(m_projectiles[i]->outOfBounds()) {
			int lastIndex = m_projectiles.size() - 1;
			delete m_projectiles[i];
			m_projectiles[i] = m_projectiles[lastIndex];
			m_projectiles.remove(lastIndex);
			i--;
		}
	}
}

void ProjectileSystem::draw() {
	if(!m_initialized) { return; }

	for(int i=0;i<m_projectiles.size();i++) {
		m_projectiles[i]->draw();
	}
}

bool ProjectileSystem::operator == (const ProjectileSystem & p) const {
	return Entity::operator == (dynamic_cast<const Entity &>(p));
}

bool ProjectileSystem::operator != (const ProjectileSystem & p) const {
	return !operator == (p);
}

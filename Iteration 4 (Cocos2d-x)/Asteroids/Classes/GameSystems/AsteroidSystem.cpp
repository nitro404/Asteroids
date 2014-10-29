#include "GameSystems/SpaceShipSystem.h"
#include "GameSystems/AsteroidSystem.h"

const char * AsteroidSystem::asteroidSystemClassName = "AsteroidSystem";
const int AsteroidSystem::maxNumberOfAsteroids = 22;
const int AsteroidSystem::numberOfAsteroidSprites = 6;

AsteroidSystem::AsteroidSystem(Layer * parentLayer)
	: Entity(parentLayer)
	, m_initialized(false)
	, m_spaceShipSystem(NULL) {
	setName(asteroidSystemClassName);

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

AsteroidSystem::AsteroidSystem(const AsteroidSystem & a)
	: Entity(a)
	, m_initialized(a.m_initialized)
	, m_spaceShipSystem(a.m_spaceShipSystem) {
	setName(asteroidSystemClassName);
		
	for(unsigned int i=0;i<numberOfAsteroidSprites;i++) {
		m_asteroidSpriteFrames.push_back(a.m_asteroidSpriteFrames[i]);
	}

	for(unsigned int i=0;i<a.m_asteroids.size();i++) {
		m_asteroids.push_back(new Asteroid(*a.m_asteroids[i]));
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

AsteroidSystem & AsteroidSystem::operator = (const AsteroidSystem & a) {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(asteroidSystemClassName); }

	Entity::operator = (a);

	m_asteroidSpriteFrames.clear();

	for(unsigned int i=0;i<m_asteroids.size();i++) {
		delete m_asteroids[i];
	}
	m_asteroids.clear();

	m_initialized = a.m_initialized;
	m_spaceShipSystem = a.m_spaceShipSystem;

	for(unsigned int i=0;i<numberOfAsteroidSprites;i++) {
		m_asteroidSpriteFrames.push_back(a.m_asteroidSpriteFrames[i]);
	}

	for(unsigned int i=0;i<a.m_asteroids.size();i++) {
		m_asteroids.push_back(new Asteroid(*a.m_asteroids[i]));
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }

	return *this;
}

AsteroidSystem::~AsteroidSystem() {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(asteroidSystemClassName); }

	for(unsigned int i=0;i<m_asteroids.size();i++) {
		delete m_asteroids[i];
	}
}

int AsteroidSystem::numberOfAsteroids() const {
	return static_cast<int>(m_asteroids.size());
}

bool AsteroidSystem::hasAsteroid(const Asteroid * asteroid) const {
	if(asteroid == NULL) { return false; }

	for(unsigned int i=0;i<m_asteroids.size();i++) {
		if(*m_asteroids[i] == *asteroid) {
			return true;
		}
	}
	return false;
}

int AsteroidSystem::indexOfAsteroid(const Asteroid * asteroid) const {
	if(asteroid == NULL) { return -1; }

	for(unsigned int i=0;i<m_asteroids.size();i++) {
		if(*m_asteroids[i] == *asteroid) {
			return i;
		}
	}
	return -1;
}

const Asteroid * AsteroidSystem::getAsteroid(int index) const {
	if(index < 0 || index >= static_cast<int>(m_asteroids.size())) { return NULL; }

	return m_asteroids[index];
}

bool AsteroidSystem::addAsteroid(Asteroid * asteroid) {
	if(asteroid == NULL) { return false; }

	for(unsigned int i=0;i<m_asteroids.size();i++) {
		if(*m_asteroids[i] == *asteroid) {
			return false;
		}
	}

	m_asteroids.push_back(asteroid);

	return true;
}

bool AsteroidSystem::removeAsteroid(int index) {
	if(index < 0 || index >= static_cast<int>(m_asteroids.size())) { return false; }

	int lastIndex = m_asteroids.size() - 1;
	delete m_asteroids[index];
	m_asteroids[index] = m_asteroids[lastIndex];
	m_asteroids.erase(m_asteroids.begin() + lastIndex);
	
	return true;
}

bool AsteroidSystem::removeAsteroid(const Asteroid * asteroid) {
	if(asteroid == NULL) { return false; }

	for(unsigned int i=0;i<m_asteroids.size();i++) {
		if(*m_asteroids[i] == *asteroid) {
			int lastIndex = m_asteroids.size() - 1;
			delete m_asteroids[i];
			m_asteroids[i] = m_asteroids[lastIndex];
			m_asteroids.erase(m_asteroids.begin() + lastIndex);

			return true;
		}
	}
	return false;
}
	
void AsteroidSystem::clearAsteroids() {
	for(unsigned int i=0;i<m_asteroids.size();i++) {
		delete m_asteroids[i];
	}
	m_asteroids.clear();
}

Layer * AsteroidSystem::getParentLayer() const {
	return Entity::getParentLayer();
}

void AsteroidSystem::setParentLayer(Layer * parentLayer) {
	if(m_parentLayer == parentLayer) { return; }

	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(asteroidSystemClassName); }

	Entity::setParentLayer(parentLayer);

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

bool AsteroidSystem::init(const SpaceShipSystem * spaceShipSystem) {
	if(m_initialized) { return true; }

	m_spaceShipSystem = spaceShipSystem;

	std::string spriteName;

	SpriteFrame * spriteFrame = NULL;

	m_asteroidSpriteFrames.clear();

	for(int i=0;i<numberOfAsteroidSprites;i++) {
		std::stringstream spriteNameStream;
		spriteNameStream << "Asteroid " << (i + 1) << ".png";
		spriteName = spriteNameStream.str();

		spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
		if(spriteFrame == NULL) { return false; }

		m_asteroidSpriteFrames.push_back(spriteFrame);
	}

	if(m_asteroidSpriteFrames.size() < numberOfAsteroidSprites) { return false; }

	m_initialized = true;

	return true;
}

void AsteroidSystem::spawnAsteroid(AsteroidTypes::AsteroidType type, const Vec2 * newPosition, const Vec2 * newVelocity) {
	if(!m_initialized) { return; }

	int asteroidIndex = -1;
	bool largeAsteroid = false;
	AsteroidTypes::AsteroidType asteroidType = type;
	if(type == AsteroidTypes::Random) {
		if(Utilities::randomFloat(0.0f, 100.0f) > 30.0f) {
			asteroidType = AsteroidTypes::Large;
		}
		else {
			asteroidType = AsteroidTypes::Small;
		}
	}
	
	if(asteroidType == AsteroidTypes::Large) {
		asteroidIndex = Utilities::randomInteger(0, 1);
		largeAsteroid = true;
	}
	else if(asteroidType == AsteroidTypes::Small) {
		asteroidIndex = Utilities::randomInteger(2, 5);
		largeAsteroid = false;
	}

	float size = m_asteroidSpriteFrames[asteroidIndex]->getRectInPixels().size.width * 0.9f;

	Size visibleDimensions = Director::getInstance()->getVisibleSize();

	Vec2 position;
	if(newPosition != NULL) {
		position = *newPosition;
	}
	else {
		while(true) {
			position = Vec2(Utilities::randomInteger(0, visibleDimensions.width), Utilities::randomInteger(0, visibleDimensions.height));

			if(m_spaceShipSystem == NULL) { break; }

			bool validPosition = true;

			for(int i=0;i<m_spaceShipSystem->numberOfSpaceShips();i++) {
				if(m_spaceShipSystem->getSpaceShip(i)->checkMinimumSpawnRadius(position, size)) {
					validPosition = false;
				}
			}

			if(validPosition) {
				for(unsigned int i=0;i<m_asteroids.size();i++) {
					if(m_asteroids[i]->checkCollision(position, size)) {
						validPosition = false;
					}
				}
			}

			if(validPosition) { break; }
		}
	}

	float rotation = Utilities::randomFloat(0.0f, 360.0f);

	RotationDirections::RotationDirection rotationDirection = static_cast<RotationDirections::RotationDirection>(Utilities::randomInteger(0, RotationDirections::NumberOfRotationDirections));
	
	float rotationSpeed = Utilities::randomFloat(Asteroid::minRotationSpeed, Asteroid::maxRotationSpeed);

	Vec2 velocity;
	if(newVelocity != NULL) {
		velocity = *newVelocity;
	}
	else {
		float velocityValue;
		for(int i=0;i<2;i++) {
			velocityValue = Utilities::randomInteger(0, 1) == 0 ? 1.0f : -1.0f * Utilities::randomFloat(Asteroid::minVelocity, Asteroid::maxVelocity);

				 if(i == 0) { velocity.x = velocityValue; }
			else if(i == 1) { velocity.y = velocityValue; }
		}
	}

	m_asteroids.push_back(new Asteroid(m_parentLayer, Sprite::createWithSpriteFrame(m_asteroidSpriteFrames[asteroidIndex]), largeAsteroid, position, size, Vec2::ONE, rotation, rotationDirection, rotationSpeed, Vec2::ZERO, velocity));
}

void AsteroidSystem::spawnAsteroidCluster(const Vec2 & position, float radius) {
	if(!m_initialized) { return; }

	// randomly choose how many small asteroids to spawn from a bigger asteroid
	int clusterSize = 0;
	int clusterChance = Utilities::randomFloat(0.0f, 100.0f);
		 if(clusterChance <  34.0f) { clusterSize = 0; } // 34% chance no asteroids
	else if(clusterChance <  76.0f) { clusterSize = 1; } // 42% chance 1 asteroid
	else if(clusterChance <  90.0f) { clusterSize = 2; } // 14% chance 2 asteroids
	else if(clusterChance <  96.0f) { clusterSize = 3; } //  6% chance 3 asteroids
	else if(clusterChance < 100.0f) { clusterSize = 4; } //  4% chance 4 asteroids

	float angle = Utilities::randomFloat(0.0f, 360.0f);
	float angleIncrement = 360.0f / static_cast<float>(clusterSize);
	Asteroid * newAsteroid = NULL;
	float velocityValue;
	Vec2 newPosition, newVelocity;
	for(int i=0;i<clusterSize;i++) {
		newPosition = Vec2(position.x + (radius * cos(Math::degreesToRadians(angle))),
						   position.y + (radius * sin(Math::degreesToRadians(angle))));

		for(int i=0;i<2;i++) {
			velocityValue = Utilities::randomInteger(0, 1) == 0 ? 1.0f : -1.0f * Utilities::randomFloat(Asteroid::minVelocity, Asteroid::maxVelocity);

			     if(i == 0) { newVelocity.x = velocityValue * cos(Math::degreesToRadians(angle)); }
			else if(i == 1) { newVelocity.y = velocityValue * sin(Math::degreesToRadians(angle)); }
		}

		angle += angleIncrement;

		spawnAsteroid(AsteroidTypes::Small, &newPosition, &newVelocity);
	}
}

void AsteroidSystem::reset() {
	if(!m_initialized) { return; }

	clearAsteroids();
}

void AsteroidSystem::update(float timeElapsed) {
	if(!m_initialized) { return; }

	for(unsigned int i=0;i<m_asteroids.size();i++) {
		m_asteroids[i]->update(timeElapsed);
	}

// TODO: add better asteroid spawn ai
	while(m_asteroids.size() < maxNumberOfAsteroids) {
		spawnAsteroid();
	}
}

bool AsteroidSystem::operator == (const AsteroidSystem & a) const {
	return Entity::operator == (dynamic_cast<const Entity &>(a));
}

bool AsteroidSystem::operator != (const AsteroidSystem & a) const {
	return !operator == (a);
}

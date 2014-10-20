#include "GameSystems/SpaceShipSystem.h"

const char * SpaceShipSystem::spaceShipSystemClassName = "SpaceShipSystem";
const int SpaceShipSystem::maxNumberOfSpaceShips = SpaceShipColours::NumberOfColours;

SpaceShipSystem::SpaceShipSystem(Layer * parent)
	: Entity(parent)
	, m_initialized(false)
	, m_numberOfSpaceShips(0) {
	setName(spaceShipSystemClassName);

	if(m_parent != NULL) { m_parent->addComponent(this); }
}

SpaceShipSystem::SpaceShipSystem(const SpaceShipSystem & s)
	: Entity(s)
	, m_initialized(s.m_initialized)
	, m_numberOfSpaceShips(s.m_numberOfSpaceShips) {
	setName(spaceShipSystemClassName);

	for(unsigned int i=0;i<s.m_spaceShips.size();i++) {
		m_spaceShips.push_back(new SpaceShip(*s.m_spaceShips[i]));
	}

	if(m_parent != NULL) { m_parent->addComponent(this); }
}

SpaceShipSystem & SpaceShipSystem::operator = (const SpaceShipSystem & s) {
	if(m_parent != NULL) { m_parent->removeComponent(spaceShipSystemClassName); }

	Entity::operator = (s);

	for(unsigned int i=0;i<m_spaceShips.size();i++) {
		delete m_spaceShips[i];
	}
	m_spaceShips.clear();

	m_initialized = s.m_initialized;
	m_numberOfSpaceShips = s.m_numberOfSpaceShips;

	for(unsigned int i=0;i<s.m_spaceShips.size();i++) {
		m_spaceShips.push_back(new SpaceShip(*s.m_spaceShips[i]));
	}

	if(m_parent != NULL) { m_parent->addComponent(this); }

	return *this;
}

SpaceShipSystem::~SpaceShipSystem() {
	if(m_parent != NULL) { m_parent->removeComponent(spaceShipSystemClassName); }

	for(unsigned int i=0;i<m_spaceShips.size();i++) {
		delete m_spaceShips[i];
	}
}

int SpaceShipSystem::numberOfSpaceShips() const {
	return m_numberOfSpaceShips;
}

const SpaceShip * SpaceShipSystem::getSpaceShip(int index) const {
	if(index < 0 || index >= maxNumberOfSpaceShips) { return NULL; }

	return m_spaceShips[index];
}

Layer * SpaceShipSystem::getParent() const {
	return m_parent;
}

void SpaceShipSystem::setParent(Layer * parent) {
	if(m_parent != NULL) { m_parent->removeComponent(spaceShipSystemClassName); }

	Entity::setParent(parent);

	if(m_parent != NULL) { m_parent->addComponent(this); }
}

bool SpaceShipSystem::init(SpriteAnimationCollection * animations, ProjectileSystem * projectileSystem) {
	if(m_initialized) { return true; }

	if(animations == NULL || animations->numberOfAnimations() == 0) { return false; }

	static const char * spaceShipMovementDirections[] = { "Left", "Center", "Right" };

	std::string spriteName;
	std::string animationName;

	SpriteFrame * spriteFrame = NULL;
	const SpriteAnimation * animation = NULL;

	Vec2 spaceShipPosition = Vec2::ZERO;
	float spaceShipRotation = 0.0f;

	for(unsigned int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_idleSpriteFrames[i].clear();
		m_movementAnimations[i].clear();
	}

	for(unsigned int i=0;i<m_spaceShips.size();i++) {
		delete m_spaceShips[i];
	}
	m_spaceShips.clear();

	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		for(int j=0;j<3;j++) {
			spriteName = std::string(SpaceShipColours::toString(i)).append(" SpaceShip ").append(spaceShipMovementDirections[j]).append(" Idle.png");
			animationName = std::string(SpaceShipColours::toString(i)).append(" SpaceShip ").append(spaceShipMovementDirections[j]).append(" Moving");

			spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
			if(spriteFrame == NULL) { return false; }

			animation = animations->getAnimation(animationName);
			if(animation == NULL) { return false; }

			m_idleSpriteFrames[i].push_back(spriteFrame);
			m_movementAnimations[i].push_back(animation);
		}

		Size visibleDimensions = Director::getInstance()->getVisibleSize();

		float w = static_cast<float>(visibleDimensions.width);
		float h = static_cast<float>(visibleDimensions.height);
		
			 if(i == 0) { spaceShipPosition = Vec2(w * 0.2f, h * 0.2f); spaceShipRotation =  135.0f; }
		else if(i == 1) { spaceShipPosition = Vec2(w * 0.8f, h * 0.8f); spaceShipRotation =  -45.0f; }
		else if(i == 2) { spaceShipPosition = Vec2(w * 0.2f, h * 0.8f); spaceShipRotation =   45.0f; }
		else if(i == 3) { spaceShipPosition = Vec2(w * 0.8f, h * 0.2f); spaceShipRotation = -135.0f; }

		m_spaceShips.push_back(new SpaceShip(m_parent, static_cast<SpaceShipColours::SpaceShipColour>(i), m_idleSpriteFrames[i], m_movementAnimations[i], projectileSystem, spaceShipPosition, spaceShipRotation));
	}

	m_initialized = true;

	return true;
}

bool SpaceShipSystem::start(int numberOfPlayers) {
	if(!m_initialized || numberOfPlayers < 1 || numberOfPlayers > maxNumberOfSpaceShips) { return false; }

	m_numberOfSpaceShips = numberOfPlayers;

	Vec2 spaceShipPosition = Vec2::ZERO;
	float spaceShipRotation = 0.0f;

	Size visibleDimensions = Director::getInstance()->getVisibleSize();

	float w = static_cast<float>(visibleDimensions.width);
	float h = static_cast<float>(visibleDimensions.height);

	if(m_numberOfSpaceShips == 1) {
		m_spaceShips[0]->setInitialPosition(w * 0.5f, h * 0.5f);
		m_spaceShips[0]->setInitialRotation(0.0f);
	}
	else if(m_numberOfSpaceShips == 2) {
		m_spaceShips[0]->setInitialPosition(w * 0.2f, h * 0.2f);
		m_spaceShips[0]->setInitialRotation(135.0f);

		m_spaceShips[1]->setInitialPosition(w * 0.8f, h * 0.8f);
		m_spaceShips[1]->setInitialRotation(-45.0f);
	}
	else {
		m_spaceShips[0]->setInitialPosition(w * 0.2f, h * 0.2f);
		m_spaceShips[0]->setInitialRotation(135.0f);

		m_spaceShips[1]->setInitialPosition(w * 0.8f, h * 0.8f);
		m_spaceShips[1]->setInitialRotation(-45.0f);

		m_spaceShips[2]->setInitialPosition(w * 0.2f, h * 0.8f);
		m_spaceShips[2]->setInitialRotation(45.0f);

		if(m_numberOfSpaceShips == 4) {
			m_spaceShips[3]->setInitialPosition(w * 0.8f, h * 0.2f);
			m_spaceShips[3]->setInitialRotation(-135.0f);
		}
	}

	for(int i=0;i<maxNumberOfSpaceShips;i++) {
		m_spaceShips[i]->setEnabled(i < m_numberOfSpaceShips);
	}

	reset();

	return true;
}

bool SpaceShipSystem::isStarted() const {
	return m_initialized &&
		   m_numberOfSpaceShips > 0;
}

void SpaceShipSystem::reset() {
	if(!m_initialized) { return; }

	for(int i=0;i<m_numberOfSpaceShips;i++) {
		m_spaceShips[i]->reset();
	}
}

bool SpaceShipSystem::handleCommand(const char * command) {
	if(!m_initialized || command == NULL || Utilities::stringLength(command) == 0) { return false; }

// TODO: handle commands

	return false;
}

void SpaceShipSystem::update(float timeElapsed) {
	if(!m_initialized) { return; }

	for(int i=0;i<m_numberOfSpaceShips;i++) {
		m_spaceShips[i]->update(timeElapsed);
	}
}

bool SpaceShipSystem::operator == (const SpaceShipSystem & s) const {
	return Entity::operator == (dynamic_cast<const Entity &>(s));
}

bool SpaceShipSystem::operator != (const SpaceShipSystem & s) const {
	return !operator == (s);
}

#include "GameObjects/SpaceShip.h"

const float SpaceShip::spaceShipAcceleration = 0.048f * 60.0f * 60.0f;
const float SpaceShip::maximumSpaceShipSpeed = 5.8f * 60.0f;
const float SpaceShip::spaceShipRotationSpeed = 3.1f * 60.0f;
const float SpaceShip::spaceShipSize = 21.0f;
const float SpaceShip::laserRateOfFire = 0.24f;
const float SpaceShip::projectileSpawnRadius = 14.0f;
const float SpaceShip::minimumSpawnRadius = 100.0f;

SpaceShip::SpaceShip(Layer * parent, const SpaceShipColours::SpaceShipColour colour, const std::vector<SpriteFrame *> & idleSpriteFrames, const std::vector<const SpriteAnimation *> & movementAnimations, ProjectileSystem * projectileSystem, const Vec2 & position, float rotation)
	: AnimatedEntity2D(parent, NULL, position, spaceShipSize, Vec2::ONE, rotation, Vec2::ZERO, Vec2::ZERO)
	, m_enabled(false)
	, m_enginesActive(false)
	, m_moveForward(false)
	, m_moveBackward(false)
	, m_turnLeft(false)
	, m_turnRight(false)
	, m_fireLaser(false)
	, m_initialLaserBeamSpawned(false)
	, m_fireLaserTimeElapsed(0)
	, m_movementDirection(SpaceShipMovementDirections::Idle)
	, m_colour(colour)
	, m_projectileSystem(projectileSystem) {
	for(unsigned int i=0;i<idleSpriteFrames.size();i++) {
		if(idleSpriteFrames[i] == NULL) { continue; }

		m_idleSprites.push_back(Sprite::createWithSpriteFrame(idleSpriteFrames[i]));
	}

	SpriteAnimation * movementAnimation = NULL;
	for(unsigned int i=0;i<movementAnimations.size();i++) {
		if(movementAnimations[i] == NULL) { continue; }

		movementAnimation = new SpriteAnimation(*movementAnimations[i]);
		m_movementAnimations.push_back(movementAnimation);
	}
}

SpaceShip::SpaceShip(const SpaceShip & s)
	: AnimatedEntity2D(s)
	, m_enabled(s.m_enabled)
	, m_enginesActive(s.m_enginesActive)
	, m_moveForward(s.m_moveForward)
	, m_moveBackward(s.m_moveBackward)
	, m_turnLeft(s.m_turnLeft)
	, m_turnRight(s.m_turnRight)
	, m_fireLaser(s.m_fireLaser)
	, m_initialLaserBeamSpawned(s.m_initialLaserBeamSpawned)
	, m_fireLaserTimeElapsed(s.m_fireLaserTimeElapsed)
	, m_movementDirection(s.m_movementDirection)
	, m_colour(s.m_colour)
	, m_projectileSystem(s.m_projectileSystem) {
	for(unsigned int i=0;i<s.m_idleSprites.size();i++) {
		m_idleSprites.push_back(s.m_idleSprites[i]);
	}

	SpriteAnimation * movementAnimation = NULL;
	for(unsigned int i=0;i<s.m_movementAnimations.size();i++) {
		movementAnimation = new SpriteAnimation(*s.m_movementAnimations[i]);
		m_movementAnimations.push_back(movementAnimation);
	}

	if(m_enabled) {
		enable();
	}
}

SpaceShip & SpaceShip::operator = (const SpaceShip & s) {
	AnimatedEntity2D::operator = (s);

	m_idleSprites.clear();

	for(unsigned int i=0;i<m_movementAnimations.size();i++) {
		delete m_movementAnimations[i];
	}
	m_movementAnimations.clear();

	m_enabled = s.m_enabled;
	m_enginesActive = s.m_enginesActive;
	m_moveForward = s.m_moveForward;
	m_moveBackward = s.m_moveBackward;
	m_turnLeft = s.m_turnLeft;
	m_turnRight = s.m_turnRight;
	m_fireLaser = s.m_fireLaser;
	m_initialLaserBeamSpawned = s.m_initialLaserBeamSpawned;
	m_fireLaserTimeElapsed = s.m_fireLaserTimeElapsed;
	m_movementDirection = s.m_movementDirection;
	m_colour = s.m_colour;
	m_projectileSystem = s.m_projectileSystem;

	for(unsigned int i=0;i<s.m_idleSprites.size();i++) {
		m_idleSprites.push_back(s.m_idleSprites[i]);
	}

	SpriteAnimation * movementAnimation = NULL;
	for(unsigned int i=0;i<s.m_movementAnimations.size();i++) {
		movementAnimation = new SpriteAnimation(*s.m_movementAnimations[i]);
		m_movementAnimations.push_back(movementAnimation);
	}

	if(m_enabled) {
		enable();
	}

	return *this;
}

SpaceShip::~SpaceShip() {
	for(unsigned int i=0;i<m_movementAnimations.size();i++) {
		delete m_movementAnimations[i];
	}
}

int SpaceShip::getIndex() const {
	return static_cast<int>(m_colour);
}

SpaceShipColours::SpaceShipColour SpaceShip::getColour() const {
	return m_colour;
}

bool SpaceShip::setColour(SpaceShipColours::SpaceShipColour colour) {
	if(!SpaceShipColours::isValid(colour)) { return false; }

	m_colour = colour;

	return true;
}

bool SpaceShip::setColour(int colour) {
	if(!SpaceShipColours::isValid(colour)) { return false; }

	m_colour = static_cast<SpaceShipColours::SpaceShipColour>(colour);

	return true;
}

bool SpaceShip::setColour(const char * data) {
	SpaceShipColours::SpaceShipColour newColour = SpaceShipColours::parseFrom(data);

	if(!SpaceShipColours::isValid(newColour)) { return false; }

	m_colour = newColour;

	return true;
}

bool SpaceShip::setColour(const std::string & data) {
	SpaceShipColours::SpaceShipColour newColour = SpaceShipColours::parseFrom(data);

	if(!SpaceShipColours::isValid(newColour)) { return false; }

	m_colour = newColour;

	return true;
}

bool SpaceShip::setColour(const Colour & colour) {
	SpaceShipColours::SpaceShipColour newColour = SpaceShipColours::getColour(colour);

	if(!SpaceShipColours::isValid(newColour)) { return false; }

	m_colour = newColour;

	return true;
}

bool SpaceShip::isEnabled() {
	return m_enabled;
}

void SpaceShip::setEnabled(bool enable) {
	m_enabled = enable;

	if(m_enabled) {
		update(0.0f);
	}
	else {
		setSprite(NULL);
	}
}

void SpaceShip::enable() {
	setEnabled(true);
}

void SpaceShip::disable() {
	setEnabled(false);
}

void SpaceShip::moveForward(bool value) {
	m_moveForward = value;
}

void SpaceShip::moveBackward(bool value) {
	m_moveBackward = value;
}

void SpaceShip::turnLeft(bool value) {
	m_turnLeft = value;
}

void SpaceShip::turnRight(bool value) {
	m_turnRight = value;
}

void SpaceShip::fireLaser(bool value) {
	if(m_projectileSystem == NULL) { return; }

	m_fireLaser = value;
}

bool SpaceShip::checkMinimumSpawnRadius(const Entity2D & entity) const {
	return checkMinimumSpawnRadius(entity.getPosition(), entity.getSize());
}

bool SpaceShip::checkMinimumSpawnRadius(const Vec2 & position, float size) const {
	return size > 0.0f &&
		   m_size > 0.0f &&
		   sqrt(pow(position.x - m_position.x, 2) + pow(position.y - m_position.y, 2)) <= size + m_size + minimumSpawnRadius;
}

void SpaceShip::reset() {
	AnimatedEntity2D::reset();

	m_enginesActive = false;
	m_moveForward = false;
	m_moveBackward = false;
	m_turnLeft = false;
	m_turnRight = false;
	m_initialLaserBeamSpawned = false;
	m_fireLaserTimeElapsed = 0;
	m_movementDirection = SpaceShipMovementDirections::Idle;

	for(unsigned int i=0;i<m_movementAnimations.size();i++) {
		m_movementAnimations[i]->stop();
	}
}

void SpaceShip::update(float timeElapsed) {
	if(!m_enabled) { return; }

	static bool lastEngineState = m_enginesActive;

	if(!SpaceShipMovementDirections::isValid(m_movementDirection)) { return; }

	m_movementDirection = SpaceShipMovementDirections::Idle;
	m_enginesActive = false;

	if(m_moveForward && !m_moveBackward) {
		updateVelocity(spaceShipAcceleration, timeElapsed);

		m_movementDirection = SpaceShipMovementDirections::MoveForward;
		m_enginesActive = true;
	}
	else if(m_moveBackward && !m_moveForward) {
		updateVelocity(-spaceShipAcceleration, timeElapsed);

		m_movementDirection = SpaceShipMovementDirections::MoveBackward;
		m_enginesActive = true;
	}
	
	if(m_turnLeft & !m_turnRight) {
		m_rotation -= spaceShipRotationSpeed * timeElapsed;
		if(m_rotation < 0.0f) { m_rotation += 360.0f; }

		m_movementDirection = SpaceShipMovementDirections::TurnLeft;
	}
	else if(m_turnRight & !m_turnLeft) {
		m_rotation += spaceShipRotationSpeed * timeElapsed;
		if(m_rotation > 360.0f) { m_rotation -= 360.0f; }

		m_movementDirection = SpaceShipMovementDirections::TurnRight;
	}

	Size visibleDimensions = Director::getInstance()->getVisibleSize();

	if(m_position.x > visibleDimensions.width + m_size) {
		m_position.x -= visibleDimensions.width + m_size;
	}
	else if(m_position.x < -m_size) {
		m_position.x += visibleDimensions.width + m_size;
	}

	if(m_position.y > visibleDimensions.height + m_size) {
		m_position.y -= visibleDimensions.height + m_size;
	}
	else if(m_position.y < -m_size) {
		m_position.y += visibleDimensions.height + m_size;
	}

	if(m_fireLaser) {
		Vec2 laserBeamSpawnPosition(m_position.x - 2 - sin(Math::degreesToRadians(-m_rotation)) * projectileSpawnRadius,
									m_position.y - 2 - cos(Math::degreesToRadians(-m_rotation)) * projectileSpawnRadius);

		if(!m_initialLaserBeamSpawned) {
			m_projectileSystem->spawnLaserBeam(laserBeamSpawnPosition, m_rotation, this);

			m_fireLaserTimeElapsed = 0.0f;
			m_initialLaserBeamSpawned = true;
		}
		else {
			m_fireLaserTimeElapsed += timeElapsed;

			int iterations = 0;
			while(m_fireLaserTimeElapsed > laserRateOfFire) {
				m_fireLaserTimeElapsed -= laserRateOfFire;

				m_projectileSystem->spawnLaserBeam(laserBeamSpawnPosition, m_rotation, this);

				iterations++;
				if(iterations > 100) {
					m_fireLaserTimeElapsed = 0.0f;
					break;
				}
			}
		}
	}
	else {
		if(m_fireLaserTimeElapsed < laserRateOfFire) {
			m_fireLaserTimeElapsed += timeElapsed;
		}
		else {
			m_fireLaserTimeElapsed = 0.0f;
			m_initialLaserBeamSpawned = false;
		}
		
	}

	if(m_idleSprites.size() != 3 || m_movementAnimations.size() != 3) { return; }

	int spriteIndex = m_movementDirection == SpaceShipMovementDirections::TurnLeft ? 0 : (m_movementDirection == SpaceShipMovementDirections::TurnRight ? 2 : 1);

	if(m_enginesActive) {
		m_movementAnimations[spriteIndex]->update(timeElapsed);

		setSprite(m_movementAnimations[spriteIndex]->getSprite());

		m_movementAnimations[spriteIndex]->play();
	}
	else {
		setSprite(m_idleSprites[spriteIndex]);
	}

	lastEngineState = m_enginesActive;

	AnimatedEntity2D::update(timeElapsed);
}

void SpaceShip::updateVelocity(float acceleration, float timeElapsed) {
	if(acceleration == 0.0f || timeElapsed == 0.0f) { return; }

	Vec2 newVelocity = m_velocity
					   + (Vec2(acceleration * cos(Math::degreesToRadians(m_rotation - 90.0f)),
							   acceleration * sin(Math::degreesToRadians(m_rotation - 90.0f)))
						  * timeElapsed);

	float newSpeed = sqrt(pow(newVelocity.x, 2) + pow(newVelocity.y, 2));
	
	if(newSpeed > maximumSpaceShipSpeed) {
		newVelocity = newVelocity.getNormalized() * maximumSpaceShipSpeed;
	}

	m_velocity = newVelocity;
}

bool SpaceShip::operator == (const SpaceShip & s) const {
	return AnimatedEntity2D::operator == (s);
}

bool SpaceShip::operator != (const SpaceShip & s) const {
	return !operator == (s);
}

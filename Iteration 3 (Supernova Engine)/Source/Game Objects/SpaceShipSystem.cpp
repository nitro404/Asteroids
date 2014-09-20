#include "Game Objects/SpaceShipSystem.h"

const int SpaceShipSystem::maxNumberOfSpaceShips = SpaceShipColours::NumberOfColours;

SpaceShipSystem::SpaceShipSystem()
	: Entity()
	, m_initialized(false)
	, m_numberOfSpaceShips(0) {

}

SpaceShipSystem::SpaceShipSystem(const SpaceShipSystem & s)
	: Entity(s)
	, m_initialized(s.m_initialized)
	, m_numberOfSpaceShips(s.m_numberOfSpaceShips) {
	for(int i=0;i<s.m_spaceShips.size();i++) {
		m_spaceShips.push_back(new SpaceShip(*s.m_spaceShips[i]));
	}
}

SpaceShipSystem & SpaceShipSystem::operator = (const SpaceShipSystem & s) {
	Entity::operator = (s);

	for(int i=0;i<m_spaceShips.size();i++) {
		delete m_spaceShips[i];
	}
	m_spaceShips.clear();

	m_initialized = s.m_initialized;
	m_numberOfSpaceShips = s.m_numberOfSpaceShips;

	for(int i=0;i<s.m_spaceShips.size();i++) {
		m_spaceShips.push_back(new SpaceShip(*s.m_spaceShips[i]));
	}

	return *this;
}

SpaceShipSystem::~SpaceShipSystem() {
	for(int i=0;i<m_spaceShips.size();i++) {
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

bool SpaceShipSystem::init(SpriteSheetCollection * spriteSheets, SpriteAnimationCollection * animations, ProjectileSystem * projectileSystem) {
	if(m_initialized) { return true; }

	if(spriteSheets == NULL || animations == NULL || spriteSheets->numberOfSpriteSheets() == 0 || animations->numberOfAnimations() == 0) { return false; }

	static const char * spaceShipMovementDirections[] = { "Left", "Center", "Right" };

	QString spriteName;
	QString animationName;

	Sprite * sprite = NULL;
	const SpriteAnimation * animation = NULL;

	Vector2 spaceShipPosition = Vector2::Zero;
	float spaceShipRotation = 0.0f;

	SpriteSheet * spaceShipSpriteSheet = spriteSheets->getSpriteSheet("SpaceShip");
	if(spaceShipSpriteSheet == NULL) { return false; }

	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		m_idleSprites[i].clear();
		m_movementAnimations[i].clear();
	}

	for(int i=0;i<m_spaceShips.size();i++) {
		delete m_spaceShips[i];
	}
	m_spaceShips.clear();

	for(int i=0;i<SpaceShipColours::NumberOfColours;i++) {
		for(int j=0;j<3;j++) {
			spriteName = QString(SpaceShipColours::toString(i)).append(" SpaceShip ").append(spaceShipMovementDirections[j]).append(" Idle");
			animationName = QString(SpaceShipColours::toString(i)).append(" SpaceShip ").append(spaceShipMovementDirections[j]).append(" Moving");

			sprite = spaceShipSpriteSheet->getSprite(spriteName);
			if(sprite == NULL) { return false; }

			animation = animations->getAnimation(animationName);
			if(animation == NULL) { return false; }

			m_idleSprites[i].push_back(sprite);
			m_movementAnimations[i].push_back(animation);
		}

		float w = static_cast<float>(SettingsManager::getInstance()->windowWidth);
		float h = static_cast<float>(SettingsManager::getInstance()->windowHeight);
		
			 if(i == 0) { spaceShipPosition = Vector2(w * 0.2f, h * 0.2f); spaceShipRotation =  135.0f; }
		else if(i == 1) { spaceShipPosition = Vector2(w * 0.8f, h * 0.8f); spaceShipRotation =  -45.0f; }
		else if(i == 2) { spaceShipPosition = Vector2(w * 0.2f, h * 0.8f); spaceShipRotation =   45.0f; }
		else if(i == 3) { spaceShipPosition = Vector2(w * 0.8f, h * 0.2f); spaceShipRotation = -135.0f; }

		m_spaceShips.push_back(new SpaceShip(static_cast<SpaceShipColours::SpaceShipColour>(i), m_idleSprites[i], m_movementAnimations[i], projectileSystem, spaceShipPosition, spaceShipRotation));
	}

	m_initialized = true;

	return true;
}

bool SpaceShipSystem::start(int numberOfPlayers) {
	if(!m_initialized || numberOfPlayers < 1 || numberOfPlayers > maxNumberOfSpaceShips) { return false; }

	m_numberOfSpaceShips = numberOfPlayers;

	Vector2 spaceShipPosition = Vector2::Zero;
	float spaceShipRotation = 0.0f;

	float w = static_cast<float>(SettingsManager::getInstance()->windowWidth);
	float h = static_cast<float>(SettingsManager::getInstance()->windowHeight);

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

	static const QRegExp   playerRegExp("^(player|(space_?)?ship)$");

	static const QRegExp      oneRegExp("^(1|one)$");
	static const QRegExp      twoRegExp("^(2|two)$");
	static const QRegExp    threeRegExp("^(3|three)$");
	static const QRegExp     fourRegExp("^(4|four)$");

	static const QRegExp     moveRegExp("^(move)$");
	static const QRegExp     turnRegExp("^(turn|rotate)$");
	static const QRegExp   attackRegExp("^(fire|shoot)$");

	static const QRegExp  forwardRegExp("^(forwards?)$");
	static const QRegExp backwardRegExp("^(back(wards?)?)$");
	static const QRegExp     leftRegExp("^(left)$");
	static const QRegExp    rightRegExp("^(right)$");
	static const QRegExp    laserRegExp("^(laser)$");

	bool startCommand = true;

	QString commandName = Utilities::getCommand(command).toLower();
	if(commandName.isEmpty()) { return false; }
	QString arguments = Utilities::getArguments(command);

	     if(commandName[0] == '+') { startCommand = true; }
	else if(commandName[0] == '-') { startCommand = false; }
	else { return false; }

	QString remainingCommandName = Utilities::substring(commandName, 1, commandName.length());

	if(playerRegExp.exactMatch(remainingCommandName)) {
		QString playerNumberData = Utilities::getCommand(arguments).toLower();
		if(playerNumberData.isEmpty()) { return false; }
		QString playerNumberArguments = Utilities::getArguments(arguments);

		int playerNumber = -1;

			 if(  oneRegExp.exactMatch(playerNumberData)) { playerNumber = 1; }
		else if(  twoRegExp.exactMatch(playerNumberData)) { playerNumber = 2; }
		else if(threeRegExp.exactMatch(playerNumberData)) { playerNumber = 3; }
		else if( fourRegExp.exactMatch(playerNumberData)) { playerNumber = 4; }
		else { return false; }

		if(playerNumber < 1 || playerNumber > m_spaceShips.size()) { return false; }

		QString playerCommandName = Utilities::getCommand(playerNumberArguments).toLower();
		if(playerCommandName.isEmpty()) { return false; }
		QString playerArguments = Utilities::getArguments(playerNumberArguments);

		if(moveRegExp.exactMatch(playerCommandName)) {
			QString moveCommandName = Utilities::getCommand(playerArguments).toLower();
			if(moveCommandName.isEmpty()) { return false; }

			if(forwardRegExp.exactMatch(moveCommandName)) {
				m_spaceShips[playerNumber - 1]->moveForward(startCommand);
				return true;
			}
			else if(backwardRegExp.exactMatch(moveCommandName)) {
				m_spaceShips[playerNumber - 1]->moveBackward(startCommand);
				return true;
			}
		}
		else if(turnRegExp.exactMatch(playerCommandName)) {
			QString turnCommandName = Utilities::getCommand(playerArguments).toLower();
			if(turnCommandName.isEmpty()) { return false; }

			if(leftRegExp.exactMatch(turnCommandName)) {
				m_spaceShips[playerNumber - 1]->turnLeft(startCommand);
				return true;
			}
			else if(rightRegExp.exactMatch(turnCommandName)) {
				m_spaceShips[playerNumber - 1]->turnRight(startCommand);
				return true;
			}
		}
		else if(attackRegExp.exactMatch(playerCommandName)) {
			QString attackCommandName = Utilities::getCommand(playerArguments).toLower();

			if(attackCommandName.isEmpty() ||
			   laserRegExp.exactMatch(attackCommandName)) {
				m_spaceShips[playerNumber - 1]->fireLaser(startCommand);
				return true;
			}
		}
	}

	return false;
}

void SpaceShipSystem::update(unsigned int timeElapsed) {
	if(!m_initialized) { return; }

	for(int i=0;i<m_numberOfSpaceShips;i++) {
		m_spaceShips[i]->update(timeElapsed);
	}
}

void SpaceShipSystem::draw() {
	if(!m_initialized) { return; }

	for(int i=0;i<m_numberOfSpaceShips;i++) {
		m_spaceShips[i]->draw();
	}
}

bool SpaceShipSystem::operator == (const SpaceShipSystem & s) const {
	return Entity::operator == (dynamic_cast<const Entity &>(s));
}

bool SpaceShipSystem::operator != (const SpaceShipSystem & s) const {
	return !operator == (s);
}

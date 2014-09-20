#include "Game Systems/SpaceShipSystem.h"
#include "Game Systems/ScoreSystem.h"

ScoreSystem::ScoreSystem()
	: Entity()
	, m_initialized(false)
	, m_spaceShipSystem(NULL)
	, m_scoreFont(NULL) {
	for(int i=0;i<SpaceShipSystem::maxNumberOfSpaceShips;i++) {
		m_playerScores[i] = 0;
	}
}

ScoreSystem::ScoreSystem(const ScoreSystem & s)
	: Entity(s)
	, m_initialized(s.m_initialized)
	, m_spaceShipSystem(s.m_spaceShipSystem)
	, m_scoreFont(s.m_scoreFont) {
	for(int i=0;i<SpaceShipSystem::maxNumberOfSpaceShips;i++) {
		m_playerScores[i] = s.m_playerScores[i];
	}
}

ScoreSystem & ScoreSystem::operator = (const ScoreSystem & s) {
	Entity::operator = (s);

	m_initialized = s.m_initialized;
	m_spaceShipSystem = s.m_spaceShipSystem;
	m_scoreFont = s.m_scoreFont;

	for(int i=0;i<SpaceShipSystem::maxNumberOfSpaceShips;i++) {
		m_playerScores[i] = s.m_playerScores[i];
	}

	return *this;
}

ScoreSystem::~ScoreSystem() {

}

bool ScoreSystem::init(const ResourceManager * resources, SpaceShipSystem * spaceShipSystem) {
	if(m_initialized) { return true; }

	if(resources == NULL || spaceShipSystem == NULL) { return false; }

	m_spaceShipSystem = spaceShipSystem;

	m_scoreFont = resources->getFont("Score Font");
	if(m_scoreFont == NULL) { return false; }

	m_initialized = true;

	return true;
}

void ScoreSystem::addScore(const SpaceShip * spaceShip, ScoreTypes::ScoreType scoreType) {
	if(!m_initialized || spaceShip == NULL || !ScoreTypes::isValid(scoreType)) { return; }

	m_playerScores[spaceShip->getIndex()] += ScoreTypes::getScoreValue(scoreType);
}

void ScoreSystem::reset() {
	if(!m_initialized) { return; }

	for(int i=0;i<SpaceShipSystem::maxNumberOfSpaceShips;i++) {
		m_playerScores[i] = 0;
	}
}

void ScoreSystem::draw() {
	if(!m_initialized || m_spaceShipSystem->numberOfSpaceShips() == 0) { return; }

	for(int i=0;i<m_spaceShipSystem->numberOfSpaceShips();i++) {
		m_scoreFont->drawText((i + 1) * (SettingsManager::getInstance()->windowWidth / (m_spaceShipSystem->numberOfSpaceShips() + 1)), 10, SpaceShipColours::getColour(i), Utilities::toString(m_playerScores[i]));
	}
}

#include "GameSystems/SpaceShipSystem.h"
#include "GameSystems/ScoreSystem.h"

const char * ScoreSystem::scoreSystemClassName = "ScoreSystem";

ScoreSystem::ScoreSystem(Layer * parentLayer)
	: Entity(parentLayer)
	, m_initialized(false)
	, m_spaceShipSystem(NULL) {
//	, m_scoreFont(NULL) {
	setName(scoreSystemClassName);

	for(int i=0;i<SpaceShipSystem::maxNumberOfSpaceShips;i++) {
		m_playerScores[i] = 0;
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

ScoreSystem::ScoreSystem(const ScoreSystem & s)
	: Entity(s)
	, m_initialized(s.m_initialized)
	, m_spaceShipSystem(s.m_spaceShipSystem) {
//	, m_scoreFont(s.m_scoreFont) {
	setName(scoreSystemClassName);

	for(int i=0;i<SpaceShipSystem::maxNumberOfSpaceShips;i++) {
		m_playerScores[i] = s.m_playerScores[i];
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

ScoreSystem & ScoreSystem::operator = (const ScoreSystem & s) {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(scoreSystemClassName); }

	Entity::operator = (s);

	m_initialized = s.m_initialized;
	m_spaceShipSystem = s.m_spaceShipSystem;
//	m_scoreFont = s.m_scoreFont;

	for(int i=0;i<SpaceShipSystem::maxNumberOfSpaceShips;i++) {
		m_playerScores[i] = s.m_playerScores[i];
	}

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }

	return *this;
}

ScoreSystem::~ScoreSystem() {
	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(scoreSystemClassName); }
}

Layer * ScoreSystem::getParentLayer() const {
	return Entity::getParentLayer();
}

void ScoreSystem::setParentLayer(Layer * parentLayer) {
	if(m_parentLayer == parentLayer) { return; }

	if(m_parentLayer != NULL) { m_parentLayer->removeComponent(scoreSystemClassName); }

	Entity::setParentLayer(parentLayer);

	if(m_parentLayer != NULL) { m_parentLayer->addComponent(this); }
}

bool ScoreSystem::init(SpaceShipSystem * spaceShipSystem) {
	if(m_initialized) { return true; }

	if(spaceShipSystem == NULL) { return false; }

	m_spaceShipSystem = spaceShipSystem;

//	m_scoreFont = resources->getFont("Score Font");
//	if(m_scoreFont == NULL) { return false; }

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
